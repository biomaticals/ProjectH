// Copyright 2024. Unique Turtle. All rights reserved.

#include "Character/Component/HCharacterCustomizationComponent.h"
#include "Character/Base/HCharacter.h"
#include "Common/CommonEnum.h"
#include "Common/CommonStruct.h"
#include "DataAsset/CharacterCustomizationDataAsset.h"
#include "Engine/AssetManager.h"
#include "Engine/PrimaryAssetLabel.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "ProjectH.h"
#include "System/HGameSingleton.h"
#include "System/Manager/DataTableManager.h"
#include "System/Manager/HAssetManager.h"

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
}

void UHCharacterCustomizationComponent::BeginPlay()
{
	InitializeComponent_Replicable();

	LoadPrimaryAsset();

	Super::BeginPlay();
}

void UHCharacterCustomizationComponent::InitializeComponent()
{
	// Network
	SetIsReplicated(true);

	if (GetOwner() && GetOwner()->IsA(AHCharacter::StaticClass()))
		CachedOwner = GetOwner() ? Cast<AHCharacter>(GetOwner()) : nullptr;

	ensureMsgf(CachedOwner, TEXT("HCharacterComponent's owner is not a AHCharacter. It will not be functional."));

	#if WITH_EDITOR
	if (GetWorld() && GetWorld()->GetNetMode() == NM_Standalone)
	{
		InitializeComponent_Internal();
		InitializeCustomizationProfile_Internal();
	}
	#endif

	Super::InitializeComponent();
}

void UHCharacterCustomizationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHCharacterCustomizationComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

#pragma region InitializeComponent
void UHCharacterCustomizationComponent::InitializeComponent_Replicable()
{
	if (CHECK_REPLIACTE_COMPONENT())
	{
		UT_LOG_OWNER_ROLE(HCharacterCustomizationLog, Log, Server);
		FString Role = GetOwner() ? *EnumToString((uint8)(GetOwner()->GetLocalRole()), TEXT("/Script/Engine.ENetRole")) : TEXT("Invalid");
		InitializeComponent_Server();
	}
	else
	{
		InitializeComponent_Internal();
	}
}

void UHCharacterCustomizationComponent::InitializeComponent_Server_Implementation()
{
	InitializeComponent_Multicast();
}

void UHCharacterCustomizationComponent::InitializeComponent_Multicast_Implementation()
{
	InitializeComponent_Internal();
}

void UHCharacterCustomizationComponent::InitializeComponent_Internal()
{
	// Property Reset
	CachedCustomizationProfiles.Empty();
	SavedCustomizationProfile.Empty();

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

	DATATABLE_MANAGER()->UpdateAvailableAnatomyProfiles();
	DATATABLE_MANAGER()->UpdatePresetCustomizationProfiles();

}
#pragma endregion

#pragma region InitializeCustomziationProfile
void UHCharacterCustomizationComponent::InitializeCustomizationProfile_Replicable()
{
	if (CHECK_REPLIACTE_COMPONENT())
	{
		InitializeCustomizationProfile_Server();
	}
	else
	{
		InitializeCustomizationProfile_Multicast();
	}
}

void UHCharacterCustomizationComponent::InitializeCustomizationProfile_Server_Implementation()
{
	InitializeCustomizationProfile_Multicast();
}

void UHCharacterCustomizationComponent::InitializeCustomizationProfile_Multicast_Implementation()
{
	InitializeCustomizationProfile_Internal();
}

void UHCharacterCustomizationComponent::InitializeCustomizationProfile_Internal()
{
	UT_LOG(HCharacterCustomizationLog, Log, TEXT("Initialize Customization Profile Behavior : %s"), *EnumToString((int32)InitializationBehavior, TEXT("/Script/ProjectH.ECharacterCustomizationInitializationBehavior")));

	switch (InitializationBehavior)
	{
	case ECharacterCustomizationInitializationBehavior::UseCurrentProfile:
	case ECharacterCustomizationInitializationBehavior::OpenCharacterEditorWithCurrentProfile:
		ApplyCustomizationProfile_Replicable(CurrentCusomizationProfile);
		break;

	case ECharacterCustomizationInitializationBehavior::UseProfileToLoad:
	case ECharacterCustomizationInitializationBehavior::OpenCharacterEditorWithProfileToLoad:
		//ApplyCustomizationProfile_Replicable(CustomizationProfile);
		break;
	}

}
#pragma endregion

#pragma region ApplyCustomizationProfile
void UHCharacterCustomizationComponent::ApplyCustomizationProfile_Replicable(FCustomizationProfile InCustomizationProfile)
{
	if(GetWorld() == NULL)
		return;

	if (CHECK_REPLIACTE_COMPONENT())
	{
		if (GetWorld()->GetNetMode() < ENetMode::NM_Client)
		{
			ApplyCustomizationProfile_Server(InCustomizationProfile);
		}
		else
		{
			ApplyCustomizationProfile_Internal(InCustomizationProfile);
			ApplyCustomizationProfile_Server(InCustomizationProfile);
		}
	}
	else
	{
		ApplyCustomizationProfile_Internal(InCustomizationProfile);
	}
}

void UHCharacterCustomizationComponent::ApplyCustomizationProfile_Server_Implementation(FCustomizationProfile InCustomizationProfile)
{	
	ApplyCustomizationProfile_Internal(InCustomizationProfile);
	if(bMulticastProfileApplication)
		ApplyCustomizationProfile_Multicast(InCustomizationProfile);
	else
		ApplyCustomizationProfile_Client(InCustomizationProfile);
}

void UHCharacterCustomizationComponent::ApplyCustomizationProfile_Multicast_Implementation(FCustomizationProfile InCustomizationProfile)
{
	ApplyCustomizationProfile_Internal(InCustomizationProfile);
}

void UHCharacterCustomizationComponent::ApplyCustomizationProfile_Client_Implementation(FCustomizationProfile InCustomizationProfile)
{
	ApplyCustomizationProfile_Internal(InCustomizationProfile);
}

void UHCharacterCustomizationComponent::ApplyCustomizationProfile_Internal(FCustomizationProfile InCustomizationProfile)
{

}
#pragma endregion

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

void UHCharacterCustomizationComponent::LoadPrimaryAsset()
{
	UT_LOG(HCharacterLog, Log, TEXT("Start Load Asset"));

	if (OnStartLoadAsset.IsBound())
		OnStartLoadAsset.Broadcast();

	if (AssetPackagesToLoad.IsEmpty())
	{
		UT_LOG(HCharacterLog, Warning, TEXT("No AssetPackesToLoad"));
		return;
	}
	
	UHAssetManager& AssetManager = UHAssetManager::Get();
	
	for (UPrimaryAssetLabel* AssetPackageToLoad : AssetPackagesToLoad)
	{
		FPrimaryAssetId AssetId = AssetPackageToLoad->GetPrimaryAssetId();
		AssetManager.LoadPrimaryAsset(AssetId);
	}
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