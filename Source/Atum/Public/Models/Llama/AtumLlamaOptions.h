#pragma once


#include "Models/Llama/llama_config.h"
#include "Layers/AtumLayerBaseOptions.h"
#include "Tensors/AtumTensorScalarType.h"
#include "AtumLlamaOptions.generated.h"

#define LOCTEXT_NAMESPACE "AtumLlamaOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Llama Options")
struct ATUM_API FAtumLlamaOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int VocabSize = 32000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int HiddenSize = 4096;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int IntermediateSize = 11008;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int NumHiddenLayers = 32;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int NumAttentionHeads = 32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int NumKeyValueHeads = 32;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString HiddenAct = "silu";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int MaxPositionEmbeddings = 2048;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	double InitializerRange = 0.02;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	double RmsNormEps = 1e-5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool UseCache = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int PadTokenId = -1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int BosTokenId = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int EosTokenId = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int PretrainingTp = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool TieWordEmbeddings = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	double RopeTheta = 10000.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool AttentionBias = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool OutputHiddenStates = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool OutputAttentions = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EAtumTensorScalarType ScalarType = EAtumTensorScalarType::Float;


	UE_NODISCARD_CTOR
	FAtumLlamaOptions() noexcept;
	
	[[nodiscard]]
	explicit operator  LlamaConfig() const noexcept
	{
		LlamaConfig config =  LlamaConfig();
		config.vocab_size = VocabSize;
		config.hidden_size = HiddenSize;
		config.intermediate_size = IntermediateSize;
		config.num_hidden_layers = NumHiddenLayers;
		config.num_attention_heads = NumAttentionHeads;
		config.num_key_value_heads = NumKeyValueHeads;
		config.hidden_act = TCHAR_TO_UTF8(*HiddenAct);
		config.max_position_embeddings = MaxPositionEmbeddings;
		config.initializer_range = InitializerRange;
		config.rms_norm_eps = RmsNormEps;
		config.use_cache = UseCache;
		if (PadTokenId != -1)
			config.pad_token_id = PadTokenId;
		
		config.bos_token_id = BosTokenId;
		config.eos_token_id = EosTokenId;
		config.pretraining_tp = PretrainingTp;
		config.tie_word_embeddings = TieWordEmbeddings;
		config.rope_theta = RopeTheta;
		config.attention_bias = AttentionBias;
		config.output_hidden_states = OutputHiddenStates;
		config.output_attentions = OutputAttentions;
		config.dtype = AtumEnums::Cast(ScalarType);
		return config;
		
	}


	void SetFrom(const  LlamaConfig& Options) noexcept;
	
	
	
};


#undef LOCTEXT_NAMESPACE
