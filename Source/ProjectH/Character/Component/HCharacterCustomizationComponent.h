// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectH.h"
#include "Common/CommonStruct.h"
#include "Common/CommonTableRow.h"
#include "DataAsset/CharacterCustomizationDataAsset.h"
#include "HCharacterCustomizationComponent.generated.h"

enum class EAnatomy : uint8;

class AHCharacter;
class ULODSyncComponent;
class UPrimaryAssetLabel;
 
 #pragma region InitializeComponent
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnSkippedCDA, UHCharacterCustomizationComponent*, UCharacterCustomizationDataAsset*, int); 
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnSkippedCDASkeleta, UHCharacterCustomizationComponent*, UCDA_SkeletalMesh*, int);
DECLARE_EVENT_FourParams(UHCharacterCustomizationComponent, FOnPostAddedCDA, UHCharacterCustomizationComponent*, UCharacterCustomizationDataAsset*, UMeshComponent*, int);
DECLARE_EVENT_FourParams(UHCharacterCustomizationComponent, FOnPostAddedCDASkeletal, UHCharacterCustomizationComponent*, UCDA_SkeletalMesh*, USkeletalMeshComponent*, int);
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnSkippedCDAApparelProfile, UHCharacterCustomizationComponent*, FCDA_ApparelProfile, int)
DECLARE_EVENT_FourParams(UHCharacterCustomizationComponent, FOnPostAddedCDAApparelProfile, UHCharacterCustomizationComponent*, FCDA_ApparelProfile, USkeletalMeshComponent*, int);
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnSkippedCDAEquipmentProfile, UHCharacterCustomizationComponent*, FCDA_EquipmentProfile, int)
DECLARE_EVENT_FourParams(UHCharacterCustomizationComponent, FOnPostAddedCDAEquipmentProfile, UHCharacterCustomizationComponent*, FCDA_EquipmentProfile, USkeletalMeshComponent*, int);
 #pragma endregion

#pragma region LoadAsset
DECLARE_EVENT(UHCharacterCustomizationComponent, FPreStartLoadAsset);
#pragma endregion

#pragma region UpdateBasebody
DECLARE_EVENT_FourParams(UHCharacterCustomizationComponent, FOnPreUpdateBasebody, UHCharacterCustomizationComponent*, FBasebodyProfile, USkeletalMeshComponent*, USkeletalMeshComponent*);
DECLARE_EVENT_FourParams(UHCharacterCustomizationComponent, FOnPostUpdateBasebody, UHCharacterCustomizationComponent*, FBasebodyProfile, USkeletalMeshComponent*, USkeletalMeshComponent*);
DECLARE_EVENT_TwoParams(UHCharacterCustomizationComponent, FOnPostUpdateBodyComponent, UHCharacterCustomizationComponent* , USkeletalMeshComponent*);
DECLARE_EVENT_TwoParams(UHCharacterCustomizationComponent, FOnPostUpdateHeadComponent, UHCharacterCustomizationComponent*, USkeletalMeshComponent*);
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnSetBasebodyMorphTarget, UHCharacterCustomizationComponent*, FName, float);
DECLARE_EVENT_TwoParams(UHCharacterCustomizationComponent, FOnPostUpdateBaseboyMorphTarget, UHCharacterCustomizationComponent*, TArray<FHNamedFloat>);
DECLARE_EVENT_TwoParams(UHCharacterCustomizationComponent, FOnPostUpdateBasebodyAnimInstanceAlphas, UHCharacterCustomizationComponent*, TArray<FHNamedFloat>);
DECLARE_EVENT_FourParams(UHCharacterCustomizationComponent, FOnPostUpdateSkinMaterials, UHCharacterCustomizationComponent*, FSkinProfile, TArray<UMaterialInstanceDynamic*>, TArray<UMaterialInstanceDynamic*>);
DECLARE_EVENT_TwoParams(UHCharacterCustomizationComponent, FOnPostUpdateSkinTextureSets, UHCharacterCustomizationComponent*, TArray<FSlotTexture_SkinBodyAndHead>);
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnPostUpdateEyesMaterials, UHCharacterCustomizationComponent*, FEyesProfile, TArray<UMaterialInstanceDynamic*>);
DECLARE_EVENT_TwoParams(UHCharacterCustomizationComponent, FOnPostUpdateLODSyncComponent, UHCharacterCustomizationComponent*, ULODSyncComponent*); 
#pragma endregion

#pragma region UpdateApparel
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnPreUpdateApparel, UHCharacterCustomizationComponent*, FApparelProfile, TArray<USkeletalMeshComponent*>);
DECLARE_EVENT_FiveParams(UHCharacterCustomizationComponent, FOnPostUpdateApparel, UHCharacterCustomizationComponent*, FApparelProfile CurrentApparelProfile, TArray<FCDA_ApparelProfile> AddedApaarelProfiles, TArray<USkeletalMeshComponent*> ApparelMeshComponents, TArray<FCDA_ApparelProfile> SkippedApparelProfiles);
DECLARE_EVENT_TwoParams(UHCharacterCustomizationComponent, FOnPostUpdateAdvancedCDAOptions, UHCharacterCustomizationComponent*, TArray<TSubclassOf<UCharacterCustomizationDataAsset>>);
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnPostUpdateApparelBasebodyMasks, UHCharacterCustomizationComponent*, TArray<FName> AvailableSkinMasks, TArray<FName> SelectedSkinMasks);
#pragma endregion

#pragma region UpdateEquipment
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnPreUpdateEquipment, UHCharacterCustomizationComponent*, FEquipmentProfile, TArray<USkeletalMeshComponent*>);
DECLARE_EVENT_FiveParams(UHCharacterCustomizationComponent, FOnPostUpdateEquipment, UHCharacterCustomizationComponent*, FEquipmentProfile, TArray<FCDA_EquipmentProfile> AddedCDAEquipProfiles, TArray<USkeletalMeshComponent*> EquipmentMeshComponents, TArray<FCDA_EquipmentProfile> SkippedCDAEquipmentProfiles);
#pragma endregion

#pragma region ApplyCustomizationProfile
DECLARE_EVENT_TwoParams(UHCharacterCustomizationComponent, FOnPreApplyCustomizationProfile, UHCharacterCustomizationComponent*, FCustomizationProfile);
#pragma endregion

#pragma region ApplyParameter
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnSetSkinScalarParameter, UHCharacterCustomizationComponent*, FName, float);
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnSetSkinHDRVectorParameter, UHCharacterCustomizationComponent*, FName, FHDRColor); 
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnSetEyesScalarParameter, UHCharacterCustomizationComponent*, FName, float);
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnSetEyesHDRVectorParameter, UHCharacterCustomizationComponent*, FName, FHDRColor);
#pragma endregion

/**
 * HCharacterCustomizationComponent
 * 
 * 캐릭터의 몸, 의상, 장비, 커스터마이징등 SkeletalMeshComponent들을 관리한다.
 * 
 * HCharacter와 연결
 * 
 * CDA ; CustomizationDataAsset
 */
UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTH_API UHCharacterCustomizationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHCharacterCustomizationComponent(const FObjectInitializer& ObjectInitializer);

public:
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	TArray<TSubclassOf<UCharacterCustomizationDataAsset>> GetHiddenCDAs();
	
	UFUNCTION(BlueprintCallable)
	TMap<FName, FSlotTexture_SkinBodyAndHead> GetCurrentSkinTextureSets();

	UFUNCTION(BlueprintCallable)
	FSlotMaterial_Eyes GetCurrentEyesMaterialSet();

	UFUNCTION(BlueprintCallable)
	bool IsCDAVisible(const UCharacterCustomizationDataAsset* CDA) const;
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "CustomizationProfile")
	FAnatomyProfile FallbackAnatomyProfile;
	 
	/** SaveGame ~ */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, SaveGame, Category = "CustomizationProfile")
	TMap<FString, FCustomizationProfile> SavedCustomizationProfileSlotList;
	/** ~ SaveGame */
	
	/** Transient ~ */
	UPROPERTY(BlueprintReadOnly, VIsibleAnywhere, Transient, Category = "CustomizationProfile")
	FCustomizationProfile CurrentCustomizationProfile;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "CustomizationProfile")
	FAnatomyProfile CurrentAnatomyProfile;

	UPROPERTY(Transient)
	TMap<EAnatomy, FCustomizationProfile> CachedCustomizationProfiles;

	UPROPERTY(Transient)
	TArray<UMaterialInstanceDynamic*> BasebodyBodySkinMIDs;
	
	UPROPERTY(Transient)
	TArray<UMaterialInstanceDynamic*> BasebodyHeadSkinMIDs;

	UPROPERTY(Transient)
	TArray<UMaterialInstanceDynamic*> EyesMIDs;
	
	UPROPERTY(Transient)
	TArray<UMaterialInstanceDynamic*> HairstyleMIDs;
	
	UPROPERTY(Transient)
	TArray<UMaterialInstanceDynamic*> ApparelMIDs;
	
	UPROPERTY(Transient)
	TArray<UMaterialInstanceDynamic*> AttachmentsMIDs;	

	UPROPERTY(Transient)
	TArray<UMaterialInstanceDynamic*> EquipmentMIDs;

	UPROPERTY(Transient)
	TArray<UMaterialInstanceDynamic*> GroomMIDs;	
	
	UPROPERTY(Transient)
	TArray<FName> ActiveAdditionalMorphTargets_Hairstyle;

	UPROPERTY(Transient)
	TArray<FName> ActiveAdditionalMorpTargets_Apparel;

	UPROPERTY(Transient)
	TArray<FName> ActiveAdditionalMorpTargets_Equipment;

	UPROPERTY(Transient)
	TArray<FName> ActiveSkinTextureSetsParameterNames_Body;

	UPROPERTY(Transient)
	TArray<FName> ActiveSkinTextureSetsParameterNames_Head;

	UPROPERTY(Transient)
	TArray<TSubclassOf<UCharacterCustomizationDataAsset>> HiddenCDAs;
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

protected:
	void InitializeCustomizationProfile_Replicable();

	UFUNCTION(Reliable, Server)
	void InitializeCustomizationProfile_Server();

	UFUNCTION(Reliable, NetMulticast)
	void InitializeCustomizationProfile_Multicast();

private:
	void InitializeCustomizationProfile_Internal();

private:
	USkeletalMeshComponent* AddCDASkeletalComponent(UCDA_SkeletalMesh* CDASkeletalMesh, int MaterialVariantIndex,
										TArray<USkeletalMeshComponent*> SkeletalMeshComponents, TArray<UMaterialInstanceDynamic*> GlobalMIDs, TArray<FName> ActiveAdditionalMorphTargets,								   
										TArray<FHNamedFloat> ScalarParameters, TArray<FNamedHDRColor> HDRVectorParameters, FName SocketName, FTransform RelativeTransform, int CDAProfilesIndex);

	bool CleanCDAs(TArray<UPrimitiveComponent*> PrimitiveComponents, TArray<UMaterialInstanceDynamic*> GlobalMIDs, TArray<FName> ActiveAdditionalMorphTargets, int CDACount, FString DebugName);
private:
		void CreateMIDFromMaterialVariant(UPrimitiveComponent* PrimitiveComponent, TArray<FMaterialVariants> MaterialVariants, int MaterialVariantIndex, TArray<UMaterialInstanceDynamic*> GlobalMIDs, TArray<FHNamedFloat> ScalarParameters, TArray<FNamedHDRColor> HDRVectorParameters);
		void CreateMIDFromSlotAndMaterial(UMeshComponent* MeshComponent, FName MaterialSlotName, UMaterialInterface* SourceMaterial, TArray<UMaterialInstanceDynamic*>& MIDs);

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	ECharacterCustomizationInitializationBehavior InitializationBehavior;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "InitializationBehavior == ECharacterCustomizationInitializationBehavior::UseProfile || InitializationBehavior == ECharacterCustomizationInitializationBehavior::OpenCharacterEditorWithCurrentProfile"))
	FCustomizationProfile CustomizationProfile;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "InitializationBehavior == ECharacterCustomizationInitializationBehavior::UseSavedProfile || InitializationBehavior == ECharacterCustomizationInitializationBehavior::OpenCharacterEditorWithProfileToLoad"))
	FString ProfileNameFromSaves;

public:
	FOnSkippedCDA OnSkippedCDA;
	FOnPostAddedCDA OnPostAddedCDA;
	FOnSkippedCDASkeleta OnSkippedCDASkeletal;
	FOnPostAddedCDASkeletal OnPostAddedCDASkeletal;
	FOnSkippedCDAApparelProfile OnSkippedCDAAparelProfile;
	FOnPostAddedCDAApparelProfile OnPostAddedCDAApparelProfile;
	FOnSkippedCDAEquipmentProfile OnSkippedCDAEquipmentProfile;
	FOnPostAddedCDAEquipmentProfile OnPostAddedCDAEquipmentProfile;

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
	void ApplyApparelSpecificSettings(UHCharacterCustomizationComponent* CharacterCustomizationComponent, FApparelProfile ApparelProfile, TArray<FCDA_ApparelProfile> AddingCCDA_Apparels, TArray<USkeletalMeshComponent*> AddingSkeletalMeshComponents, TArray<FCDA_ApparelProfile> SkippedCCDA_ApparelProfiles);

	UFUNCTION()
	void ClearApparelSpecificSettings(UHCharacterCustomizationComponent* CharacterCustomizationComponent, FApparelProfile ApparelProfile, TArray<USkeletalMeshComponent*> RemoveingSkeletalMeshComponents);
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

#pragma region UpdateBasebody
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

#pragma region UpdateApparel
public:
	void UpdateApparel();
	void UpdateApparelBasebodyMasks();
	void UpdateAdvancedCDAOptions();

public:
	FOnPreUpdateApparel OnPreUpdateApparel;
	FOnPostUpdateApparel OnPostUpdateApparel;
	FOnPostUpdateApparelBasebodyMasks OnPostUpdateApparelBasebodyMasks;
	FOnPostUpdateAdvancedCDAOptions OnUpdateAdvancedCDAOptions;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FName> SkinMasks;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ShowAlternativeTexturesParameterName;
private:
	UTexture* DefaultTexture;
#pragma endregion

#pragma region UpdateEquipment
public:
	void UpdateEquipment();

public:
	FOnPreUpdateEquipment OnPreUpdateEquipment;
	FOnPostUpdateEquipment OnPostUpdateEquipment;
#pragma endregion
};
