// Copy Rigts are in Team UniqueTurtle. 


#include "Character/Component/HCharacterCustomizingComponent.h"
#include "Engine/AssetManager.h"
#include "Engine/PrimaryAssetLabel.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectH.h"
#include "Net/UnrealNetwork.h"

UHCharacterCustomizingComponent::UHCharacterCustomizingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	bIsLoading = false;
	bLoaded = false;
}

void UHCharacterCustomizingComponent::BeginPlay()
{
	Super::BeginPlay();


}

void UHCharacterCustomizingComponent::InitializeComponent()
{
	Super::InitializeComponent();

	check(!bLoaded);
	check(!bIsLoading);

	SetIsReplicated(true);

	bIsLoading = true;

	LoadAsset();


}

void UHCharacterCustomizingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHCharacterCustomizingComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHCharacterCustomizingComponent, bIsLoading);
	DOREPLIFETIME(UHCharacterCustomizingComponent, bLoaded);
}

void UHCharacterCustomizingComponent::LoadAsset()
{
	bIsLoading = true;

	UT_LOG(HCharacterLog, Log, TEXT("Start Load Asset"));

	if (OnStartLoadAsset.IsBound())
		OnStartLoadAsset.Broadcast();

	if (AssetPackagesToLoad.IsEmpty())
	{
		UT_LOG(HCharacterLog, Fatal, TEXT("No AssetPackeToLoad : %s"));
		return;
	}
	
	UAssetManager& AssetManager = UAssetManager::Get();
	IAssetRegistry& AssetRegistry = AssetManager.GetAssetRegistry();
	
	bLoaded = true;
	bIsLoading = false;
}