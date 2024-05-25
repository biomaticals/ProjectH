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
 
DECLARE_EVENT(UHCharacterCustomizationComponent, FPreStartLoadAsset);
DECLARE_EVENT_TwoParams(UHCharacterCustomizationComponent, FOnPreApplyCustomizationProfile, UHCharacterCustomizationComponent*, FCustomizationProfile);
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnPreUpdateApparel, UHCharacterCustomizationComponent*, FApparelProfile, TArray<USkeletalMeshComponent*>);
DECLARE_EVENT_FiveParams(UHCharacterCustomizationComponent, FOnPostUpdateApparel, UHCharacterCustomizationComponent*, FApparelProfile, TArray<FCCDA_ApparelProfile>, TArray<USkeletalMeshComponent*>, TArray<FCCDA_ApparelProfile>);
DECLARE_EVENT_FourParams(UHCharacterCustomizationComponent, FOnPreUpdateBasebody, UHCharacterCustomizationComponent*, FBasebodyProfile, USkeletalMeshComponent*, USkeletalMeshComponent*);
DECLARE_EVENT_FourParams(UHCharacterCustomizationComponent, FOnPostUpdateBasebody, UHCharacterCustomizationComponent*, FBasebodyProfile, USkeletalMeshComponent*, USkeletalMeshComponent*);

DECLARE_EVENT_TwoParams(UHCharacterCustomizationComponent, FOnPostUpdateBodyComponent, UHCharacterCustomizationComponent* , USkeletalMeshComponent*);
DECLARE_EVENT_TwoParams(UHCharacterCustomizationComponent, FOnPostUpdateLODSync, UHCharacterCustomizationComponent*, USkeletalMeshComponent*);

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

#pragma region Load Assets
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

#pragma region Repliacte Settings
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

#pragma region Anim Instance Alpha
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

#pragma region Update
public:
	void UpdateBaseBody();

public:
	FOnPreUpdateBasebody OnPreUpdateBasebody;
	FOnPostUpdateBasebody OnPostUpdateBasebody;

protected:
	void UpdateBodyComponent();

public:
	FOnPostUpdateBodyComponent OnPostUpdateBodyComponent;

private:
	void UpdateLODSyncComponent();


#pragma endregion
};
