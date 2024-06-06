// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectH.h"
#include "Common/CommonStruct.h"
#include "Common/CommonTableRow.h"
#include "HCharacterCustomizationComponent.generated.h"

enum class EAnatomy : uint8;

class AHCharacter;
class UPrimaryAssetLabel;
class UCCDA_Apparel;
class ULODSyncComponent;
 
#pragma region InitializeComponent
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnPreUpdateApparel, UHCharacterCustomizationComponent*, FApparelProfile, TArray<USkeletalMeshComponent*>);
DECLARE_EVENT_FiveParams(UHCharacterCustomizationComponent, FOnPostUpdateApparel, UHCharacterCustomizationComponent*, FApparelProfile, TArray<FCCDA_ApparelProfile>, TArray<USkeletalMeshComponent*>, TArray<FCCDA_ApparelProfile>);
#pragma endregion

#pragma region ApplyCustomizationProfile
DECLARE_EVENT_TwoParams(UHCharacterCustomizationComponent, FOnPreApplyCustomizationProfile, UHCharacterCustomizationComponent*, FCustomizationProfile);
#pragma endregion

#pragma region LoadAsset
DECLARE_EVENT(UHCharacterCustomizationComponent, FPreStartLoadAsset);
#pragma endregion

#pragma region UpdateComponent
DECLARE_EVENT_FourParams(UHCharacterCustomizationComponent, FOnPreUpdateBasebody, UHCharacterCustomizationComponent*, FBasebodyProfile, USkeletalMeshComponent*, USkeletalMeshComponent*);
DECLARE_EVENT_FourParams(UHCharacterCustomizationComponent, FOnPostUpdateBasebody, UHCharacterCustomizationComponent*, FBasebodyProfile, USkeletalMeshComponent*, USkeletalMeshComponent*);
DECLARE_EVENT_TwoParams(UHCharacterCustomizationComponent, FOnPostUpdateBodyComponent, UHCharacterCustomizationComponent* , USkeletalMeshComponent*);
DECLARE_EVENT_TwoParams(UHCharacterCustomizationComponent, FOnPostUpdateHeadComponent, UHCharacterCustomizationComponent*, USkeletalMeshComponent*);
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnSetBasebodyMorphTarget, UHCharacterCustomizationComponent*, FName, float);
DECLARE_EVENT_TwoParams(UHCharacterCustomizationComponent, FOnPostUpdateBaseboyMorphTarget, UHCharacterCustomizationComponent*, TArray<FHNamedFloat>);
DECLARE_EVENT_TwoParams(UHCharacterCustomizationComponent, FOnPostUpdateBasebodyAnimInstanceAlphas, UHCharacterCustomizationComponent*, TArray<FHNamedFloat>);
DECLARE_EVENT_FourParams(UHCharacterCustomizationComponent, FOnPostUpdateSkinMaterials, UHCharacterCustomizationComponent*, FSkinProfile, TArray<UMaterialInstanceDynamic*>, TArray<UMaterialInstanceDynamic*>);
DECLARE_EVENT_TwoParams(UHCharacterCustomizationComponent, FOnPostUpdateSkinTextureSets, UHCharacterCustomizationComponent*, FName);//TMap<FName, FSlotTexture_SkinBodyAndHead>);
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnPostUpdateEyesMaterials, UHCharacterCustomizationComponent*, FEyesProfile, TArray<UMaterialInstanceDynamic*>);
DECLARE_EVENT_TwoParams(UHCharacterCustomizationComponent, FOnPostUpdateLODSyncComponent, UHCharacterCustomizationComponent*, ULODSyncComponent*); 
#pragma endregion


#pragma region ApplyParameter
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnSetSkinScalarParameter, UHCharacterCustomizationComponent*, FName, float);
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnSetSkinHDRVectorParameter, UHCharacterCustomizationComponent*, FName, FHDRColor); 
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnSetEyesScalarParameter, UHCharacterCustomizationComponent*, FName, float);
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnSetEyesHDRVectorParameter, UHCharacterCustomizationComponent*, FName, FHDRColor);
#pragma endregion

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTH_API UHCharacterCustomizationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHCharacterCustomizationComponent();

public:
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	TMap<FName, FSlotTexture_SkinBodyAndHead> GetCurrentSkinTextureSets();

	UFUNCTION(BlueprintCallable)
	FSlotMaterial_Eyes GetCurrentEyesMaterialSet();

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "CustomizationProfile")
	FAnatomyProfile FallbackAnatomyProfile;
	 
	/** SaveGame ~ */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, SaveGame, Category = "CustomizationProfile")
	TMap<FString, FCustomizationProfile> SavedCustomizationProfileSlotList;
	/** ~ SaveGame */
	
	/** Transient ~ */
	UPROPERTY(BlueprintReadOnly, VIsibleAnywhere, Transient, Category = "CustomizationProfile")
	FCustomizationProfile CurrentCusomizationProfile;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "CustomizationProfile")
	FAnatomyProfile CurrentAnatomyProfile;

	UPROPERTY(Transient)
	TMap<EAnatomy, FCustomizationProfile> CachedCustomizationProfiles;

	UPROPERTY(Transient)
	TArray<UMaterialInstanceDynamic*> BodyMIDs;
	
	UPROPERTY(Transient)
	TArray<UMaterialInstanceDynamic*> HeadMIDs;

	UPROPERTY(Transient)
	TArray<UMaterialInstanceDynamic*> EyesMIDs;

	UPROPERTY(Transient)
	TArray<FName> ActiveSkinTextureSetsParameterNames_Body;

	UPROPERTY(Transient)
	TArray<FName> ActiveSkinTextureSetsParameterNames_Head;
	/** ~ Transient */

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "BetaFeature")
	bool bUseSkeletalMerging;

private:
	UPROPERTY(Transient)
	AHCharacter* CachedOwner;

#pragma region InitializeComponent
protected:
	void InitializeComponent_Replicable();

	UFUNCTION(Reliable, Server)
	void InitializeComponent_Server();

	UFUNCTION(Reliable, NetMulticast)
	void InitializeComponent_Multicast();

private:
	void InitializeComponent_Internal();

public:
	FOnPreUpdateApparel OnPreUpdateApparel;
	FOnPostUpdateApparel OnpostUpdateApparel;

#pragma endregion

#pragma region InitializeCustomziationProfile
protected:
	void InitializeCustomizationProfile_Replicable();

	UFUNCTION(Reliable, Server)
	void InitializeCustomizationProfile_Server();

	UFUNCTION(Reliable, NetMulticast)
	void InitializeCustomizationProfile_Multicast();

private:
	void InitializeCustomizationProfile_Internal();

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	ECharacterCustomizationInitializationBehavior InitializationBehavior;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "InitializationBehavior == ECharacterCustomizationInitializationBehavior::UseProfile || InitializationBehavior == ECharacterCustomizationInitializationBehavior::OpenCharacterEditorWithCurrentProfile"))
	FCustomizationProfile CustomizationProfile;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "InitializationBehavior == ECharacterCustomizationInitializationBehavior::UseSavedProfile || InitializationBehavior == ECharacterCustomizationInitializationBehavior::OpenCharacterEditorWithProfileToLoad"))
	FString ProfileNameFromSaves;

#pragma endregion

#pragma region ApplyCustomizationProfile
public:
	UFUNCTION(BlueprintCallable)
	void ApplyCustomizationProfile_Replicable(FCustomizationProfile InCustomizationProfile);

protected:
	UFUNCTION(Reliable, Server)
	void ApplyCustomizationProfile_Server(FCustomizationProfile InCustomizationProfile);

	UFUNCTION(Reliable, NetMulticast)
	void ApplyCustomizationProfile_Multicast(FCustomizationProfile InCustomizationProfile);

	UFUNCTION(Reliable, Client)
	void ApplyCustomizationProfile_Client(FCustomizationProfile InCustomizationProfile);

private:
	void ApplyCustomizationProfile_Internal(FCustomizationProfile InCustomizationProfile);

public:
	FOnPreApplyCustomizationProfile OnPreApplyCustomizationProfile;
#pragma endregion

#pragma region ApparelSpecificSettings
protected:
	UFUNCTION()
	void ApplyApparelSpecificSettings(UHCharacterCustomizationComponent* CharacterCustomizationComponent, FApparelProfile ApparelProfile, TArray<FCCDA_ApparelProfile> AddingCCDA_Apparels, TArray<USkeletalMeshComponent*> AddingSkeletalMeshComponents, TArray<FCCDA_ApparelProfile> SkippedCCDA_ApparelProfiles);

	UFUNCTION()
	void ClearApparelSpecificSettings(UHCharacterCustomizationComponent* CharacterCustomizationComponent, FApparelProfile ApparelProfile, TArray<USkeletalMeshComponent*> RemoveingSkeletalMeshComponents);
#pragma endregion

#pragma region LoadAssets
public:
	UFUNCTION(Category = "Load Assets")
	void LoadPrimaryAsset();

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Load Assets")
	TArray<UPrimaryAssetLabel*> AssetPackagesToLoad;

public:
	FPreStartLoadAsset OnStartLoadAsset;

private:
	FDelegateHandle OnStartLoadAssetHandle;
	FDelegateHandle OnBeforeUpdateApparelHandle;	
	
#pragma endregion

#pragma region RepliacteSettings
protected:
	bool CheckReplicateIndividualChagnes() const;
	bool CheckMulticastIndividualChanges() const;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Repliacte Settings")
	bool bMulticastProfileApplication;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Repliacte Settings")
	bool bReplicateIndividualChanges;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Repliacte Settings")
	bool bMulticastIndividualChanges;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Repliacte Settings")
	bool bDebugReplication;
#pragma endregion

#pragma region AnimInstanceAlpha
public:
	UFUNCTION(BlueprintCallable)
	void SetBasebodyAnimInstanceAlpha_Replicable(FName Name, float Value);

protected:
	UFUNCTION(Reliable, Server)
	void SetBasebodyAnimInstanceAlpha_Server(FName Name, float Value);

	UFUNCTION(Reliable, NetMulticast)
	void SetBasebodyAnimInstanceAlpha_Multicast(FName Name, float Value);

	UFUNCTION()
	void SetBasebodyAnimInstanceAlpha(FName Name, float Value);
#pragma endregion

#pragma region ApplyParameter
public:
	UFUNCTION(BlueprintCallable)
	void SetSkinScalarParameter_Replicable(FName Name, float Value);

protected:
	UFUNCTION(Reliable, Server)
	void SetSkinScalarParameter_Server(FName Name, float Value);

	UFUNCTION(Reliable, NetMulticast)
	void SetSkinScalarParameter_Multicast(FName Name, float Value);

	UFUNCTION()
	void SetSkinScalarParameter(FName Name, float Value);

public:
	FOnSetSkinScalarParameter OnSetSkinScalarParameter;

public:
	UFUNCTION(BlueprintCallable)
	void SetSkinHDRVectorParameter_Replicable(FName Name, FHDRColor HDRColor);

protected:
	UFUNCTION(Reliable, Server)
	void SetSkinHDRVectorParameter_Server(FName Name, FHDRColor HDRColor);

	UFUNCTION(Reliable, NetMulticast)
	void SetSkinHDRVectorParameter_Multicast(FName Name, FHDRColor HDRColor);

	UFUNCTION()
	void SetSkinHDRVectorParameter(FName Name, FHDRColor HDRColor);

public:
	FOnSetSkinHDRVectorParameter OnSetSkinHDRVectorParameter;
	
public:
	UFUNCTION(BlueprintCallable)
	void SetEyesScalarParameter_Replicable(FName Name, float Value);

protected:
	UFUNCTION(Reliable, Server)
	void SetEyesScalarParameter_Server(FName Name, float Value);

	UFUNCTION(Reliable, NetMulticast)
	void SetEyesScalarParameter_Multicast(FName Name, float Value);

	UFUNCTION()
	void SetEyesScalarParameter(FName Name, float Value);

public:
	FOnSetEyesScalarParameter OnSetEyesScalarParameter;

public:
	UFUNCTION(BlueprintCallable)
	void SetEyesHDRVectorParameter_Replicable(FName Name, FHDRColor HDRColor);

protected:
	UFUNCTION(Reliable, Server)
	void SetEyesHDRVectorParameter_Server(FName Name, FHDRColor HDRColor);

	UFUNCTION(Reliable, NetMulticast)
	void SetEyesHDRVectorParameter_Multicast(FName Name, FHDRColor HDRColor);

	UFUNCTION()
	void SetEyesHDRVectorParameter(FName Name, FHDRColor HDRColor);

public:
	FOnSetEyesHDRVectorParameter OnSetEyesHDRVectorParameter;
	
#pragma endregion
#pragma region UpdateComponent
public:
	void UpdateBasebody();

public:
	FOnPreUpdateBasebody OnPreUpdateBasebody;
	FOnPostUpdateBasebody OnPostUpdateBasebody;

protected:
	void UpdateBodyComponent();
	void UpdateHeadComponent();
	void UpdateBasebodyMorphTargets();
	void UpdateBasebodyAnimInstanceAlphas();
	void UpdateSkinMaterials();
	void UpdateSkinTextureSets(); 
	void UpdateEyesMaterials();
	void UpdateLODSyncComponent();
public:
	FOnPostUpdateBodyComponent OnPostUpdateBodyComponent;
	FOnPostUpdateHeadComponent OnPostUpdateHeadComponent;
	FOnSetBasebodyMorphTarget OnSetBasebodyMorphTarget;
	FOnPostUpdateBaseboyMorphTarget OnPostUpdateBasebodyMorphTarget;
	FOnPostUpdateBasebodyAnimInstanceAlphas OnPostUpdateBasebodyAnimInstanceAlphas;
	FOnPostUpdateSkinTextureSets OnPostUpdateSkinTextureSets;
	FOnPostUpdateSkinMaterials OnPostUpdateSkinMaterialSets;
	FOnPostUpdateEyesMaterials OnPostUpdateEyesMaterialSets;
	FOnPostUpdateLODSyncComponent OnPostUpdateLODSyncComponent;
	
#pragma endregion

#pragma region Helper
private:
	void CreateMIDFromSlotAndMaterial(UMeshComponent* MeshComponent , FName MaterialSlotName, UMaterialInterface* SourceMaterial, TArray<UMaterialInstanceDynamic*>& MIDs);
#pragma endregion
};
