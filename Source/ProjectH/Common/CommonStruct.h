// Copy Rigts are in Team UniqueTurtle. 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Common/CommonEnum.h"
#include "CommonStruct.generated.h"

class UCCDA_Apparel;

#pragma region Character Customizing
USTRUCT(BlueprintType)
struct FCCDA_ApparelProfile
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCCDA_Apparel* DataAsset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaterialVariantIndex;
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
struct FApparelProfile
{
	GENERATED_USTRUCT_BODY()
};

USTRUCT(BlueprintType)
struct FHairStyleProfile
{
	GENERATED_USTRUCT_BODY()
};


USTRUCT(BlueprintType)
struct FCustomizationProfileMetaData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EAnatomy Anatomy;
};

USTRUCT(BlueprintType)
struct FCustomizationProfile
{

	GENERATED_USTRUCT_BODY()
};

USTRUCT(BlueprintType)
struct FSlotTexture_SkinHead
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName, UTexture*> Head;
};

USTRUCT(BlueprintType)
struct FSlotMaterial_SkinHead
{
	GENERATED_USTRUCT_BODY()

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
