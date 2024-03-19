// Copy Rigts are in Team UniqueTurtle. 


#include "Character/Component/HCharacterCustomizationComponent.h"
#include "Common/CommonStruct.h"
#include "DataAsset/CharacterCustomizationDataAsset.h"
#include "Engine/AssetManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "ProjectH.h"

UHCharacterCustomizationComponent::UHCharacterCustomizationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	
	
	bIsLoading = false;
	bLoaded = false;
}

void UHCharacterCustomizationComponent::BeginPlay()
{
	Super::BeginPlay();


}

void UHCharacterCustomizationComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetIsReplicated(true);
	

	// Remove Event
	if (OnStartLoadAsset.IsBoundToObject(this))
	{
		OnStartLoadAsset.Remove(OnStartLoadAssetHandle);
	}
	
	if (OnPreUpdateApparel.IsBoundToObject(this))
	{
		OnPreUpdateApparel.Remove(OnBeforeUpdateApparelHandle);
	}

	// Add Event
	OnPreUpdateApparel.AddUObject(this, &UHCharacterCustomizationComponent::ClearApparelSpecificSettings);
	OnpostUpdateApparel.AddUObject(this, &UHCharacterCustomizationComponent::ApplyApparelSpecificSettings);

	check(!bLoaded);
	check(!bIsLoading);

	bIsLoading = true;

	LoadAsset();
}

void UHCharacterCustomizationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHCharacterCustomizationComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHCharacterCustomizationComponent, bIsLoading);
	DOREPLIFETIME(UHCharacterCustomizationComponent, bLoaded);
}

void UHCharacterCustomizationComponent::LoadAsset()
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

void UHCharacterCustomizationComponent::ApplyApparelSpecificSettings(UHCharacterCustomizationComponent* CharacterCustomizationComponent, FApparelProfile ApparelProfile, TArray<FCCDA_ApparelProfile> AddingCCDA_Apparels, TArray<USkeletalMeshComponent*> AddingSkeletalMeshComponents, TArray<FCCDA_ApparelProfile> SkippedCCDA_ApparelProfiles)
{
	for (FCCDA_ApparelProfile AddingCCDA_Apparel : AddingCCDA_Apparels)
	{
		AddingCCDA_Apparel.DataAsset->IsA(UCCDA_Apparel_Feet)
	}
}

void UHCharacterCustomizationComponent::ClearApparelSpecificSettings(UHCharacterCustomizationComponent* CharacterCustomizationComponent, FApparelProfile ApparelProfile, TArray<USkeletalMeshComponent*> RemoveingSkeletalMeshComponents)
{

}