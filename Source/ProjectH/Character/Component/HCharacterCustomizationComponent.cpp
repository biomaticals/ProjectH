// Copy Rigts are in Team UniqueTurtle. 

#include "Character/Component/HCharacterCustomizationComponent.h"
#include "Character/Base/HCharacter.h"
#include "Common/CommonEnum.h"
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
	bWantsInitializeComponent = true;
	
	CachedOwner = nullptr;

	#pragma region Replicate
	bMulticastProfileApplication = false;
	bReplicateIndividualChanges = true;
	bMulticastIndividualChanges = true;
	bDebugReplication = false;
	#pragma endregion

	#pragma region Load
	bIsLoading = false;
	bLoaded = false;
	#pragma endregion
}

void UHCharacterCustomizationComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHCharacterCustomizationComponent::InitializeComponent()
{
	Super::InitializeComponent();

	UT_LOG(HCharacterCustomizationLog, Log, TEXT("InitializeComponent Start"));

	// Network
	SetIsReplicated(true);

	// Property Reset
	CachedCustomizationProfiles.Empty();

	UT_LOG(HCharacterCustomizationLog, Log, TEXT("Initialization Behavior : %s"), *EnumToString((int32)InitializationBehavior, TEXT("/Script/ProjectH.ECharacterCustomizationInitializationBehavior")));

	UT_LOG(HCharacterCustomizationLog, Log, TEXT("ProfileToLoad : %s"), *ProfileToLoad);

	/**
	 * To do 
	 * automization to find profile from data table.
	 * change profile type as FGameplayTag
	 */

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

	if(GetOwner() && GetOwner()->IsA(AHCharacter::StaticClass()))
	CachedOwner = GetOwner() ? Cast<AHCharacter>(GetOwner()) : nullptr;
	
	ensureMsgf(!CachedOwner, TEXT("HCharacterComponent's owner is not a AHCharacter. It will not be functional."));



	// Load Assets... Realize when hitch occurs
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

void UHCharacterCustomizationComponent::UpdateAvailableAnatomyProfiles()
{
	UT_LOG(HCharacterCustomizationLog, Log, TEXT("Update AvailableAnatomyProfiles"));

	AvailableAnatomyProfiles.Empty();

	UT_LOG(HCharacterCustomizationLog, Log, TEXT("Get Data Table : %s\n"), *AnatomyDataTable->GetName());


	for (EAnatomy Anatomy : TEnumRange<EAnatomy>())
	{
		FName AnatomyRowName = FName(*EnumToString((int)Anatomy, TEXT("/Script/ProjectH.EAnatomy")));
		//AnatomyDataTable->FindRow<FAnatomyProfile>(AnatomyRowName, *FString::Printf("Find"));//, AnatomyRowName, *AnatomyDataTable->GetName()));
	}
}

void UHCharacterCustomizationComponent::ApplyApparelSpecificSettings(UHCharacterCustomizationComponent* CharacterCustomizationComponent, FApparelProfile ApparelProfile, TArray<FCCDA_ApparelProfile> AddingCCDA_Apparels, TArray<USkeletalMeshComponent*> AddingSkeletalMeshComponents, TArray<FCCDA_ApparelProfile> SkippedCCDA_ApparelProfiles)
{
	for (FCCDA_ApparelProfile AddingCCDA_Apparel : AddingCCDA_Apparels)
	{
		if (AddingCCDA_Apparel.DataAsset->IsA(UCCDA_Apparel_Feet::StaticClass()))
		{
			UCCDA_Apparel_Feet* CCDA_Apparel_Feet = Cast<UCCDA_Apparel_Feet>(AddingCCDA_Apparel.DataAsset);
			CCDA_Apparel_Feet->RootOffset;
		}
	}
}

void UHCharacterCustomizationComponent::ClearApparelSpecificSettings(UHCharacterCustomizationComponent* CharacterCustomizationComponent, FApparelProfile ApparelProfile, TArray<USkeletalMeshComponent*> RemoveingSkeletalMeshComponents)
{

}

void UHCharacterCustomizationComponent::LoadAsset()
{
	bIsLoading = true;

	UT_LOG(HCharacterLog, Log, TEXT("Start Load Asset"));

	if (OnStartLoadAsset.IsBound())
		OnStartLoadAsset.Broadcast();

	if (AssetPackagesToLoad.IsEmpty())
	{
		UT_LOG(HCharacterLog, Warning, TEXT("No AssetPackesToLoad"));
		return;
	}
	
	UAssetManager& AssetManager = UAssetManager::Get();
	IAssetRegistry& AssetRegistry = AssetManager.GetAssetRegistry();
	
	bLoaded = true;
	bIsLoading = false;
}

bool UHCharacterCustomizationComponent::CheckReplicateIndividualChagnes() const
{
	return bReplicateIndividualChanges && CHECK_REPLIACTE_COMPONENT();
}

bool UHCharacterCustomizationComponent::CheckMulticastIndividualChanges() const
{
	return bMulticastIndividualChanges && CHECK_REPLIACTE_COMPONENT();
}

#pragma region Anim Instance Alpha
void UHCharacterCustomizationComponent::SetBasebodyAnimInstanceAlpha_Replicable(FName Name, float Value)
{
	if (CheckReplicateIndividualChagnes())
	{
		if(GetOwner()->GetLocalRole() == ENetRole::ROLE_Authority)
			SetBasebodyAnimInstanceAlpha_Multicast(Name, Value);
		else
			SetBasebodyAnimInstanceAlpha_Server(Name, Value);
	}
	else
	{
		SetBasebodyAnimInstanceAlpha(Name, Value);
	}
}

void UHCharacterCustomizationComponent::SetBasebodyAnimInstanceAlpha_Server_Implementation(FName Name, float Value)
{
	if (CheckMulticastIndividualChanges())
	{
		SetBasebodyAnimInstanceAlpha_Multicast(Name, Value);
	}
}

void UHCharacterCustomizationComponent::SetBasebodyAnimInstanceAlpha_Multicast_Implementation(FName Name, float Value)
{
	SetBasebodyAnimInstanceAlpha(Name, Value);
}

void UHCharacterCustomizationComponent::SetBasebodyAnimInstanceAlpha(FName Name, float Value)
{
	CurrentCusomizationProfile.Basebody.AnimInstanceAlphas.AddUnique(FHNamedFloat(Name, Value));
	
}
#pragma endregion