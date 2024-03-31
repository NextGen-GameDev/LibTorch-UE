#include "Models/Llama/AtumLlamaOptions.h"

#define LOCTEXT_NAMESPACE "AtumLlamaOptions"

FAtumLlamaOptions::FAtumLlamaOptions() noexcept
{
}

void FAtumLlamaOptions::SetFrom(const LlamaConfig& Options) noexcept
{
	VocabSize = Options.vocab_size;
	HiddenSize = Options.hidden_size;
	IntermediateSize = Options.intermediate_size;
	NumHiddenLayers = Options.num_hidden_layers;
	NumAttentionHeads = Options.num_attention_heads;
	NumKeyValueHeads = Options.num_key_value_heads;
	HiddenAct = Options.hidden_act.c_str();
	MaxPositionEmbeddings = Options.max_position_embeddings;
	InitializerRange = Options.initializer_range;
	RmsNormEps = Options.rms_norm_eps;
	UseCache = Options.use_cache;
	PadTokenId = Options.pad_token_id.value_or(-1);
	BosTokenId = Options.bos_token_id;
	EosTokenId = Options.eos_token_id;
	PretrainingTp = Options.pretraining_tp;
	TieWordEmbeddings = Options.tie_word_embeddings;
	RopeTheta = Options.rope_theta;
	AttentionBias = Options.attention_bias;
	ScalarType = AtumEnums::Cast(Options.dtype);
}

#undef LOCTEXT_NAMESPACE