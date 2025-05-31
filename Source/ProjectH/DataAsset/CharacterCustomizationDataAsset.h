// Copyright 2025. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "HDataAsset.h"
#include "CharacterCustomizationDataAsset.generated.h"

enum class EAnatomy : uint8;
enum class ECCDACollection : uint8;
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
class PROJECTH_API UCDA_SkeletalMesh : public UCharacterCustomizationDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
	TMap<FName, float> AdditionalMorphTargets;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UCDA_Apparel: public UCDA_SkeletalMesh
{
	GENERATED_BODY()
public:
	FORCEINLINE FName ToMaterialParameterName() const
	{
		return GetClass()->GetFName();
	}

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
	UTexture2D* BasebodyMask;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
	bool UseAlternativeSkinTexture;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UCDA_Apparel_Feet : public UCDA_Apparel
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
class PROJECTH_API UCDA_Hairstyle : public UCDA_SkeletalMesh
{
	GENERATED_BODY()
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UCDA_Groom : public UCharacterCustomizationDataAsset
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
class PROJECTH_API UCDA_Equipment : public UCDA_SkeletalMesh
{
	GENERATED_BODY()

public:
	UCDA_Equipment()
	{

	};
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UCDA_StaticMesh : public UCharacterCustomizationDataAsset
{
	GENERATED_BODY()

public:
	UCDA_StaticMesh()
	{
		
	};

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UStaticMesh* StaticMesh;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UCDA_Attachment : public UCDA_StaticMesh
{
	GENERATED_BODY()

public:
	UCDA_Attachment()
	{

	};
};