#pragma once
#include "Models/Llama/llama_causal_lm.h"
#include "Models/Llama/llama_utils.h"
#include "CoreMinimal.h"


LlamaCausalLMImpl::LlamaCausalLMImpl(const LlamaConfig& config)
    : config(config),
    model(LlamaModel(config))
{
    lm_head = torch::nn::Linear(torch::nn::LinearOptions(config.hidden_size, config.vocab_size).bias(false));

    register_module("model", model);
    register_module("lm_head", lm_head);
    lm_head->to(config.dtype);
}


std::tuple<torch::Tensor, c10::optional<torch::Tensor>,  std::vector<std::tuple<at::Tensor, at::Tensor>>, std::vector<torch::Tensor>, std::vector<c10::optional<torch::Tensor>>>
LlamaCausalLMImpl::forward(
    const c10::optional<torch::Tensor> input_ids,
    c10::optional<torch::Tensor> attention_mask,
    c10::optional<torch::Tensor> position_ids,
    c10::optional<torch::Tensor> inputs_embeds,
    c10::optional<torch::Tensor> labels,
    const std::vector<std::tuple<torch::Tensor, torch::Tensor>>& past_key_values,
    bool output_attentions,
    bool output_hidden_states,
    bool use_cache)
{
    auto outputs = model->forward(
        input_ids,
        attention_mask,
        position_ids,
        inputs_embeds,
        past_key_values,
        output_attentions,
        output_hidden_states,
        use_cache);

    auto hidden_states = std::get<0>(outputs);

    auto lm_logits = lm_head->forward(hidden_states);

    // make float32
    lm_logits = lm_logits.to(torch::kFloat32);

    c10::optional<torch::Tensor> loss;

    if (labels.has_value()) {
        int n_dims = lm_logits.dim(); 
        torch::Tensor shift_logits = lm_logits.slice(n_dims - 2, 0, -1).contiguous();
        torch::Tensor shift_labels = labels.value().slice(1, 1, -1).contiguous();
        
        shift_logits = shift_logits.view({-1, config.vocab_size});
        shift_labels = shift_labels.view(-1);

        loss = torch::nn::functional::cross_entropy(shift_logits, shift_labels);
    }

    return std::make_tuple(lm_logits, loss, std::get<1>(outputs), std::get<2>(outputs), std::get<3>(outputs));
}



torch::Tensor LlamaCausalLMImpl::generate(
    torch::Tensor& input_ids,
    const int32_t num_new_tokens
)
{
    // generate up to num_new_tokens or max_position_embeddings

    // get shape of input_ids
    auto input_shape = input_ids.sizes();

    // get batch_size and seq_length
    int64_t batch_size = input_shape[0];
    int64_t seq_length = input_shape[1];

    // get max_position_embeddings
    int64_t max_position_embeddings = config.max_position_embeddings;

    // calculate num_tokens_to_generate
    int64_t num_tokens_to_generate = std::min<int64_t>(num_new_tokens, max_position_embeddings - seq_length);

    // iterate over num_tokens_to_generate

    // setup container to hold cache
    std::vector<std::tuple<torch::Tensor, torch::Tensor>> past_key_values;

    for (int64_t i = 0; i < num_tokens_to_generate; i++) {
        
        auto outputs = forward(
            input_ids,
            {},
            {},
            {},
            {},
            past_key_values,
            false,
            false,
            true);

        past_key_values = std::get<2>(outputs);

        auto hidden_states = std::get<0>(outputs);
        
        
        

        // get the preds for next token by slicing the last token 
        auto next_token = hidden_states.index({torch::indexing::Slice(), -1, torch::indexing::Slice()}).argmax();
        
        next_token = next_token.to(torch::kInt64).unsqueeze(0).unsqueeze(0);
        

        // append next_token to input_ids
        input_ids = torch::cat({input_ids, next_token}, 1);

    }

    return input_ids;

    
}






