// Copy Rigts are in Team UniqueTurtle. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HCharacterCustomizationComponent.generated.h"

class UPrimaryAssetLabel;

DECLARE_EVENT(UHCharacterCustomizationComponent, FOnStartLoadAsset);
//DECLARE_EVENT_ThreeParams(UHCharacterCustomizationComponent, FOnBeforeUpdateApparel, UHCharacterCustomizationComponent, FApparelProfile, TArray<USkeletalMeshComponent>);

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

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UDataTable* AnatomyDataTable;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UDataTable* PresetDataTable;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool Replicate;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool MulticastProfileApplication;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool ReplicateIndividualChanges;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool DebugReplication;

#pragma region Load
public:
	UFUNCTION(Category = Load)
	void LoadAsset();

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Load)
	TArray<UPrimaryAssetLabel*> AssetPackagesToLoad;

protected:
	UPROPERTY(replicated)
	bool bIsLoading;

	UPROPERTY(replicated)
	bool bLoaded;

private:
	FOnStartLoadAsset OnStartLoadAsset;
#pragma endregion
};
