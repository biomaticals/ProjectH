// Copy Rigts are in Team UniqueTurtle. 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Common/CommonEnum.h"
#include "CommonStruct.generated.h"

#pragma region Common
USTRUCT(BlueprintType)
struct FHNamedInt
{
	GENERATED_USTRUCT_BODY()
	FHNamedInt()
	: Value(0)
	{

	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Value;
};

USTRUCT(BlueprintType)
struct FHNamedFloat
{
	GENERATED_USTRUCT_BODY()

public:
	FHNamedFloat()
		: Value(0.f)
	{

	};

	FHNamedFloat(FName InName, float Value)
		: Name(NAME_None)
		, Value(0.f)
	{

	};

	FORCEINLINE bool operator==(const FHNamedFloat& Other) const
	{
		return Name == Other.Name && Value == Other.Value;
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value;
};

USTRUCT(BlueprintType)
struct FHDRColor
{
	GENERATED_USTRUCT_BODY()
	FHDRColor()
		: H(0.f)
		, S(0.f)
		, V(0.f)
		, A(0.f)
		, Intensity(0.f)
	{

	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float H;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float S;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float V;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float A;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Intensity;
};

USTRUCT(BlueprintType)
struct FNamedHDRColor
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FHDRColor Value;
};
#pragma endregion

#pragma region Character Customizing
class UCCDA_Hairstyle;
class UCCDA_Apparel;
class UCCDA_Attachment;

USTRUCT(BlueprintType)
struct FCCDA_HairstyleProfile
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCCDA_Hairstyle* DataAsset;
};

USTRUCT(BlueprintType)
struct FMaterialVariants
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText DisplayName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLinearColor Thumbnail;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UMaterialInstance*> Materials;
};

USTRUCT(BlueprintType)
struct FCustomizationProfileMetaData
{
	GENERATED_USTRUCT_BODY()
	FCustomizationProfileMetaData()
	{

	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EAnatomy Anatomy;
};

USTRUCT(BlueprintType)
struct FHeadProfile
{
	GENERATED_USTRUCT_BODY()
	FHeadProfile()
	: Index(0)
	{

	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Index;
};

USTRUCT(BlueprintType)
struct FSkinProfile
{
	GENERATED_USTRUCT_BODY()
	FSkinProfile()
	: MaterialIndex(0)
	{

	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaterialIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FName> TextureSets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FHNamedFloat> ScalarParameters;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FHNamedFloat> HDRVectorParameters;
};

USTRUCT(BlueprintType)
struct FEyesProfile
{
	GENERATED_USTRUCT_BODY()
	FEyesProfile()
	: MaterialIndex(0)
	{

	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaterialIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FHNamedFloat> ScalarParameters;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FNamedHDRColor> HDRScalarParameters;
};

USTRUCT(BlueprintType)
struct FBasebodyProfile
{
	GENERATED_USTRUCT_BODY()
	FBasebodyProfile()
	{

	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FHeadProfile Head;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)	
	FSkinProfile SKin;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FEyesProfile Eyes;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FHNamedFloat> MorphTargets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FHNamedInt> MorphTargetGroups;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FHNamedFloat> AnimInstanceAlphas;
};

USTRUCT(BlueprintType)
struct FHairStyleProfile
{
	GENERATED_USTRUCT_BODY()
	FHairStyleProfile()
	{

	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FCCDA_HairstyleProfile> DataAssets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FHNamedFloat> GlobalScalarParameters;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FNamedHDRColor> GlobalHDRVectorParameters;
};

USTRUCT(BlueprintType)
struct FGroomProfile
{
	GENERATED_USTRUCT_BODY()
	FGroomProfile()
	{

	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FCCDA_HairstyleProfile> DataAssets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FHNamedFloat> GlobalScalarParameters;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FNamedHDRColor> GlobalHDRVectorParameters;
};

USTRUCT(BlueprintType)
struct FCCDA_ApparelProfile
{
	GENERATED_USTRUCT_BODY()
	FCCDA_ApparelProfile()
		: MaterialVariantIndex(0)
	{

	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCCDA_Apparel* DataAsset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaterialVariantIndex;
};

USTRUCT(BlueprintType)
struct FApparelProfile
{
	GENERATED_USTRUCT_BODY()
	FApparelProfile()
	{

	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FCCDA_ApparelProfile> DataAssets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FHNamedFloat> GlobalScalarParameters;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FNamedHDRColor> GlobalHDRVectorParameters;
};

USTRUCT(BlueprintType)
struct FCCDA_EquipmentProfile
{
	GENERATED_USTRUCT_BODY()
	FCCDA_EquipmentProfile()
		
	{

	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCCDA_Apparel* DataAsset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaterialVariantIndex;
};

USTRUCT(BlueprintType)
struct FEquipmentProfile
{
	GENERATED_USTRUCT_BODY()
	FEquipmentProfile()
	{

	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FCCDA_EquipmentProfile> DataAssets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FHNamedFloat> GlobalScalarParameters;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FNamedHDRColor> GlobalHDRVectorParameters;
};

USTRUCT(BlueprintType)
struct FAttachmentProfile
{
	GENERATED_USTRUCT_BODY()
	FAttachmentProfile()
	{

	};

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCCDA_Attachment* DataAssets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ParentSocket;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform RelativeTransfom;
};

USTRUCT(BlueprintType)
struct FCustomizationProfile
{
	GENERATED_USTRUCT_BODY()
	FCustomizationProfile()
	{

	};

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FCustomizationProfileMetaData MetaData;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBasebodyProfile Basebody;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FHairStyleProfile Hairstyle;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FGroomProfile Groom;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FApparelProfile Apparel;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FEquipmentProfile Equipment;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FAttachmentProfile Attachments;
};

USTRUCT(BlueprintType)
struct FSlotTexture_SkinHead
{
	GENERATED_USTRUCT_BODY()
	FSlotTexture_SkinHead()
	{

	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName, UTexture*> Head;
};

USTRUCT(BlueprintType)
struct FSlotMaterial_SkinHead
{
	GENERATED_USTRUCT_BODY()
	FSlotMaterial_SkinHead()
	{
		
	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName, UMaterialInstance*> Head;
};

USTRUCT(BlueprintType)
struct FSlotMaterial_Eyes
{
	GENERATED_USTRUCT_BODY()
	FSlotMaterial_Eyes()
	{

	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName, UMaterialInstance*> Eyes;
};

USTRUCT(BlueprintType)
struct FAnatomyProfileFaceVariants
{
	GENERATED_USTRUCT_BODY()
	FAnatomyProfileFaceVariants()
	{

	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName GroupName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FName> IDs;
};

USTRUCT(BlueprintType)
struct FAnatomyHeadProfile
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimInstance* AnimInstanceClass_Override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FSlotMaterial_SkinHead SkinMaterialSets_Override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName, FSlotTexture_SkinHead> SkinTextureSets_Override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FSlotMaterial_Eyes> EyesMaterialSets_Override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FAnatomyProfileFaceVariants FaceVariants;
};

USTRUCT(BlueprintType)
struct FSlotTexture_SkinBodyAndHead
{
	GENERATED_USTRUCT_BODY()
	FSlotTexture_SkinBodyAndHead()
	{

	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName, UTexture*> Body;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName, UTexture*> Head;
};

USTRUCT(BlueprintType)
struct FSlotMaterial_SkinBodyAndHead
{
	GENERATED_USTRUCT_BODY()
	FSlotMaterial_SkinBodyAndHead()
	{

	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName, UMaterialInstance*> Body;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName, UMaterialInstance*> Head;
};

USTRUCT(BlueprintType)
struct FAnatomyBaseBodyProfile
{
	GENERATED_USTRUCT_BODY()

	FAnatomyBaseBodyProfile()
	{

	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USkeletalMeshComponent* Mesh;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UAnimInstance> AnimInstanceClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FSlotMaterial_SkinBodyAndHead> SkinMaterialSets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName, FSlotTexture_SkinBodyAndHead> SkinTextureSets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FSlotMaterial_Eyes> EyesMaterialSets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FAnatomyProfileFaceVariants FaceVariants;
	
};

USTRUCT(BlueprintType)
struct FAnatomyProfile : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FAnatomyBaseBodyProfile Body;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FAnatomyHeadProfile Head;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FCustomizationProfile Customzation;
};
#pragma endregion
