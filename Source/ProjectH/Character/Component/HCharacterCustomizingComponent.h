// Copy Rigts are in Team UniqueTurtle. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HCharacterCustomizingComponent.generated.h"

class UPrimaryAssetLabel;

DECLARE_EVENT(UHCharacterCustomizingComponent, FOnStartLoadAsset);

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTH_API UHCharacterCustomizingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHCharacterCustomizingComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


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
