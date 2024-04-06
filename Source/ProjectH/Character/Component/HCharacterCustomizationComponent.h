// Copy Rigts are in Team UniqueTurtle. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectH.h"
#include "Common/CommonStruct.h"
#include "HCharacterCustomizationComponent.generated.h"

enum class EAnatomy : uint8;

struct FApparelProfile;
struct FCCDA_ApparelProfile;
struct FCustomizationProfile;

class AHCharacter;
class UPrimaryAssetLabel;
class UCCDA_Apparel;

DECLARE_EVENT(UHCharacterCustomizationComponent, FOnStartLoadAsset);
DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnPreUpdateApparel, UHCharacterCustomizationComponent*, FApparelProfile, TArray<USkeletalMeshComponent*>);
DECLARE_EVENT_FiveParams(UHCharacterCustomizationComponent, FOnPostUpdateApparel, UHCharacterCustomizationComponent*, FApparelProfile, TArray<FCCDA_ApparelProfile>, TArray<USkeletalMeshComponent*>, TArray<FCCDA_ApparelProfile>);

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTH_API UHCharacterCustomizationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHCharacterCustomizationComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	void UpdateAvailableAnatomyProfiles();

public:
	UFUNCTION()
	void ApplyApparelSpecificSettings(UHCharacterCustomizationComponent* CharacterCustomizationComponent, FApparelProfile ApparelProfile, TArray<FCCDA_ApparelProfile> AddingCCDA_Apparels, TArray<USkeletalMeshComponent*> AddingSkeletalMeshComponents, TArray<FCCDA_ApparelProfile> SkippedCCDA_ApparelProfiles);

	UFUNCTION()
	void ClearApparelSpecificSettings(UHCharacterCustomizationComponent* CharacterCustomizationComponent, FApparelProfile ApparelProfile, TArray<USkeletalMeshComponent*> RemoveingSkeletalMeshComponents);

private:
	UPROPERTY(Transient)
	AHCharacter* CachedOwner;

protected:
	UPROPERTY(BlueprintReadOnly, VIsibleAnywhere, Transient)
	FCustomizationProfile CurrentCusomizationProfile;

	UPROPERTY(Transient)
	TMap<EAnatomy, FCustomizationProfile> CachedCustomizationProfiles;

#pragma region Initialization
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Initialization")
	ECharacterCustomizationInitializationBehavior InitializationBehavior;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Initialization")
	FString ProfileToLoad;
#pragma endregion

#pragma region Load Assets
public:
	UFUNCTION(Category = "Load Assets")
	void LoadAsset();

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Load Assets")
	TArray<UPrimaryAssetLabel*> AssetPackagesToLoad;

protected:
	UPROPERTY(replicated)
	bool bIsLoading;

	UPROPERTY(replicated)
	bool bLoaded;

public:
	FOnStartLoadAsset OnStartLoadAsset;
	FOnPreUpdateApparel OnPreUpdateApparel;
	FOnPostUpdateApparel OnpostUpdateApparel;

private:
	FDelegateHandle OnStartLoadAssetHandle;
	FDelegateHandle OnBeforeUpdateApparelHandle;	
	
#pragma endregion

#pragma region Repliacte
protected:
	bool CheckReplicateIndividualChagnes() const;
	bool CheckMulticastIndividualChanges() const;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Replicate")
	bool bMulticastProfileApplication;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Replicate")
	bool bReplicateIndividualChanges;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Replicate")
	bool bMulticastIndividualChanges;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Replicate")
	bool bDebugReplication;
#pragma endregion/

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
};
