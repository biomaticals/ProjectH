// Copy Rigts are in Team UniqueTurtle. 

#pragma once

#include "CoreMinimal.h"
#include "HDataAsset.h"
#include "CharacterCustomizationDataAsset.generated.h"

enum class EAnatomy;

struct FMaterialVariants;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UCharacterCustomizationDataAsset : public UHDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<EAnatomy> Anatomies;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Mesh")
	TArray<FMaterialVariants> MaterialVariants;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UCCDA_SkeletalMesh : public UCharacterCustomizationDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Mesh")
	TMap<FName, float> AdditionalMorphTargets;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UCCDA_Apparel: public UCCDA_SkeletalMesh
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Mesh")
	UTexture2D* BasebodyMast;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Mesh")
	bool UseAlternativeSkinTexture;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UCCDA_Apparel_Feet : public UCCDA_Apparel
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float RootOffset;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float  FootRoation;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float  BallRotation;
};