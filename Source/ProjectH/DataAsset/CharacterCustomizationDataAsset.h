// Copy Rigts are in Team UniqueTurtle. 

#pragma once

#include "CoreMinimal.h"
#include "HDataAsset.h"
#include "CharacterCustomizationDataAsset.generated.h"

enum class EAnatomy;
enum class ECCDACollection;
struct FMaterialVariants;

class UGroomAsset;
class UGroomBindingAsset;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UCharacterCustomizationDataAsset : public UHDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<EAnatomy> Anatomies;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<ECCDACollection> Collections;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TSubclassOf<UCharacterCustomizationDataAsset>> HiddenCCDAClasses;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
	TArray<FMaterialVariants> MaterialVariants;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UCCDA_SkeletalMesh : public UCharacterCustomizationDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
	TMap<FName, float> AdditionalMorphTargets;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UCCDA_Apparel: public UCCDA_SkeletalMesh
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
	UTexture2D* BasebodyMast;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
	bool UseAlternativeSkinTexture;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UCCDA_Apparel_Feet : public UCCDA_Apparel
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float RootOffset;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float FootRoation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float BallRotation;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UCCDA_Hairstyle : public UCCDA_SkeletalMesh
{
	GENERATED_BODY()
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UCCDA_Groom : public UCharacterCustomizationDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UGroomAsset* GroomAsset;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UGroomBindingAsset*> BindingAssets;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UCCDA_Equipment : public UCCDA_SkeletalMesh
{
	GENERATED_BODY()

public:
	UCCDA_Equipment()
	{

	};
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UCCDA_StaticMesh : public UCharacterCustomizationDataAsset
{
	GENERATED_BODY()

public:
	UCCDA_StaticMesh()
	{
		
	};

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UStaticMeshComponent* StaticMesh;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UCCDA_Attachment : public UCCDA_StaticMesh
{
	GENERATED_BODY()

public:
	UCCDA_Attachment()
	{

	};
};