// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "Common/CommonEnum.h"
#include "Common/HUtilityHelpers.h"
#include "CoreMinimal.h"
#include "GameplayTags.h"
#include "CommonStruct.generated.h"

#pragma region Common
USTRUCT(BlueprintType)
struct FHNamedInt
{
	GENERATED_USTRUCT_BODY()
public:
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

public:
	FHDRColor()
		: H(0.f)
		, S(0.f)
		, V(0.f)
		, A(0.f)
		, Intensity(0.f)
	{

	};

	const FLinearColor ToLinearColor() const
	{
		return FLinearColor(H, S, V * Intensity, A);
	}

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
class UCDA_Hairstyle;
class UCDA_Groom;
class UCDA_Apparel;
class UCDA_Attachment;

USTRUCT(BlueprintType)
struct FCDA_GroomProfile
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCDA_Groom* DataAsset;
};

USTRUCT(BlueprintType)
struct FCDA_HairstyleProfile
{
	GENERATED_USTRUCT_BODY()

public:
	FORCEINLINE bool operator==(const FCDA_HairstyleProfile& Other) const
	{
		return DataAsset == Other.DataAsset && ScalarParameters.Num() == Other.ScalarParameters.Num()&& HDRVectorParameters.Num() && Other.HDRVectorParameters.Num();
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCDA_Hairstyle* DataAsset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FHNamedFloat> ScalarParameters;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FNamedHDRColor> HDRVectorParameters;
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

public:
	FString ToString() const
	{
		return Name + "_" + HUtilityHelpers::EnumToString((uint8)Anatomy, TEXT("Script/ProjectH.EAnatomy"));
	}

	bool IsValid() const
	{
		return Name != "" && Anatomy != EAnatomy::None;
	}

public:
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
	TArray<FNamedHDRColor> HDRVectorParameters;
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
	FSkinProfile Skin;

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
struct FHairstyleProfile
{
	GENERATED_USTRUCT_BODY()
	FHairstyleProfile()
	{

	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FCDA_HairstyleProfile> DataAssets;

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
	TArray<FCDA_GroomProfile> DataAssets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FHNamedFloat> GlobalScalarParameters;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FNamedHDRColor> GlobalHDRVectorParameters;
};

USTRUCT(BlueprintType)
struct FCDA_ApparelProfile
{
	GENERATED_USTRUCT_BODY()
	FCDA_ApparelProfile()
		: MaterialVariantIndex(0)
	{

	}

	FORCEINLINE bool operator==(const FCDA_ApparelProfile& Other) const
	{
		return DataAsset == Other.DataAsset && MaterialVariantIndex == Other.MaterialVariantIndex;
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCDA_Apparel* DataAsset;

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
	TArray<FCDA_ApparelProfile> DataAssets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FHNamedFloat> GlobalScalarParameters;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FNamedHDRColor> GlobalHDRVectorParameters;
};

USTRUCT(BlueprintType)
struct FCDA_EquipmentProfile
{
	GENERATED_USTRUCT_BODY()
	FCDA_EquipmentProfile()		
	{

	}

	FORCEINLINE bool operator==(const FCDA_EquipmentProfile& Other) const
	{
		return DataAsset == Other.DataAsset && MaterialVariantIndex == Other.MaterialVariantIndex &&
		ParentSocket == Other.ParentSocket && RelativeTransform.Equals(Other.RelativeTransform);
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCDA_Apparel* DataAsset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaterialVariantIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ParentSocket;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform RelativeTransform;
};

USTRUCT(BlueprintType)
struct FEquipmentProfile
{
	GENERATED_USTRUCT_BODY()
	FEquipmentProfile()
	{

	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FCDA_EquipmentProfile> DataAssets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FHNamedFloat> GlobalScalarParameters;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FNamedHDRColor> GlobalHDRVectorParameters;
};

USTRUCT(BlueprintType)
struct FCDA_AttachmentProfile
{
	GENERATED_USTRUCT_BODY()
	FCDA_AttachmentProfile()
	{

	};

public:
	FORCEINLINE bool operator==(const FCDA_AttachmentProfile& Other) const
	{
		return DataAsset == Other.DataAsset && ParentSocket == Other.ParentSocket && RelativeTransform.Equals(Other.RelativeTransform);
	}
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCDA_Attachment* DataAsset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ParentSocket;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform RelativeTransform;
};

USTRUCT(BlueprintType)
struct FAttachmentProfile
{
	GENERATED_USTRUCT_BODY()
	FAttachmentProfile()
		
	{

	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FCDA_AttachmentProfile> DataAssets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FHNamedFloat> GlobalScalarParameters;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FNamedHDRColor> GlobalHDRVectorParameters;
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
	FHairstyleProfile Hairstyle;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FGroomProfile Groom;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FApparelProfile Apparel;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FEquipmentProfile Equipment;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FAttachmentProfile Attachment;
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
	USkeletalMesh* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UAnimInstance> AnimInstanceClass_Override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FSlotMaterial_SkinHead> SkinMaterialSets_Override;

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

	bool operator==(const FSlotTexture_SkinBodyAndHead& Other) const
	{
		return true;
	}

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
	USkeletalMesh* Mesh;
	
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
#pragma endregion

#pragma region SaveGame
USTRUCT(BlueprintType)
struct FHSaveGameObjectData
{
	GENERATED_USTRUCT_BODY()

	FHSaveGameObjectData()
	{
		bProcessed = false;
	}

	const bool operator== (const FHSaveGameObjectData& Other) const
	{
		return ID.Equals(Other.ID);
	}

	const bool operator!= (const FHSaveGameObjectData& Other) const
	{
		return !ID.Equals(Other.ID);
	}

	const bool IsValid() const
	{
		return ID.IsEmpty() == false && ObjectClass != nullptr;
	}

protected:
	UPROPERTY(VisibleAnywhere)
	FString ID;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UObject> ObjectClass;

	UPROPERTY(VisibleAnywhere)
	FTransform Transform;

	UPROPERTY(VisibleAnywhere)
	TArray<uint8> ByteData;

	UPROPERTY()
	TSoftObjectPtr<UObject> ParentSaveGameObject;

	UPROPERTY(Transient)
	bool bProcessed;

	friend class UHSaveGameSubSystem;
};

USTRUCT(BlueprintType)
struct FHSaveGameData
{
	GENERATED_USTRUCT_BODY()

	FHSaveGameData() 	
	{

	};

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<FHSaveGameObjectData> ObjectData;

	friend class UHSaveGameSubSystem;
};
#pragma endregion 
	