// Copy Rigts are in Team UniqueTurtle. 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CommonStruct.generated.h"

#pragma region Character Customizing
USTRUCT(BlueprintType)
struct FApparelProfile
{
	GENERATED_USTRUCT_BODY()
};

USTRUCT(BlueprintType)
struct FCustomizationProfile
{
	GENERATED_USTRUCT_BODY()
};

USTRUCT(BlueprintType)
struct FAnatomyHeadProfile
{
	GENERATED_USTRUCT_BODY()
};

USTRUCT(BlueprintType)
struct FAnatomyFaceVariants
{
	GENERATED_USTRUCT_BODY()
	FAnatomyFaceVariants()
	{

	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName GroupName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FName> IDs;
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
struct FAnatomyBodyProfile
{
	GENERATED_USTRUCT_BODY()

	FAnatomyBodyProfile()
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
	FAnatomyFaceVariants FaceVariants;
	
};

USTRUCT(BlueprintType)
struct FAnatomyProfile : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FAnatomyBodyProfile Body;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FAnatomyHeadProfile Head;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FCustomizationProfile Customzation;
};
#pragma endregion
