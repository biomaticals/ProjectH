// Copyright 2024. Unique Turtle. All rights reserved.

#include "Character/Component/HCharacterCustomizationComponent.h"
#include "Character/Base/HCharacter.h"
#include "Common/CommonEnum.h"
#include "Common/CommonStruct.h"
#include "Common/CommonTableRow.h"
#include "Common/HUtilityHelpers.h"
#include "Components/LODSyncComponent.h"
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

	#pragma region BetaFeature
	bUseSkeletalMerging = false;
	#pragma endregion
}

void UHCharacterCustomizationComponent::BeginPlay()
{
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

	InitializeComponent_Internal();
	InitializeCustomizationProfile_Internal();

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
		FString Role = GetOwner() ? *HUtilityHelpers::EnumToString((uint8)GetOwner()->GetLocalRole(), TEXT("")) : FString();
		InitializeComponent_Server();
	}
	else
	{
		UT_LOG_OWNER_ROLE(HCharacterCustomizationLog, Log, Internal);
		InitializeComponent_Internal();
	}
}

void UHCharacterCustomizationComponent::InitializeComponent_Server_Implementation()
{
	UT_LOG_OWNER_ROLE(HCharacterCustomizationLog, Log, Multicast);
	InitializeComponent_Multicast();
}

void UHCharacterCustomizationComponent::InitializeComponent_Multicast_Implementation()
{
	UT_LOG_OWNER_ROLE(HCharacterCustomizationLog, Log, Internal);
	InitializeComponent_Internal();
}

void UHCharacterCustomizationComponent::InitializeComponent_Internal()
{
	// Property Reset
	CachedCustomizationProfiles.Empty();

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
		UT_LOG_OWNER_ROLE(HCharacterCustomizationLog, Log, Server);
		InitializeCustomizationProfile_Server();
	}
	else
	{
		UT_LOG_OWNER_ROLE(HCharacterCustomizationLog, Log, NetMulticast);
		InitializeCustomizationProfile_Multicast();
	}
}

void UHCharacterCustomizationComponent::InitializeCustomizationProfile_Server_Implementation()
{
	UT_LOG_OWNER_ROLE(HCharacterCustomizationLog, Log, NetMulticast);
	InitializeCustomizationProfile_Multicast();
}

void UHCharacterCustomizationComponent::InitializeCustomizationProfile_Multicast_Implementation()
{
	InitializeCustomizationProfile_Internal();
}

void UHCharacterCustomizationComponent::InitializeCustomizationProfile_Internal()
{
	//UT_LOG(HCharacterCustomizationLog, Log, TEXT("Initialize Customization Profile Behavior : %s"), *EnumToString((int32)InitializationBehavior, TEXT("/Script/ProjectH.ECharacterCustomizationInitializationBehavior")));

	switch (InitializationBehavior)
	{
	case ECharacterCustomizationInitializationBehavior::UseCurrentProfile:
	case ECharacterCustomizationInitializationBehavior::OpenCharacterEditorWithCurrentProfile:
		ApplyCustomizationProfile_Replicable(CustomizationProfile);
		break;

	case ECharacterCustomizationInitializationBehavior::UseProfileToLoad:
	case ECharacterCustomizationInitializationBehavior::OpenCharacterEditorWithProfileToLoad:
		FCustomizationProfile* SavedCustomizationProfile = SavedCustomizationProfileSlotList.Find(ProfileNameFromSaves);
		if(SavedCustomizationProfile)
		{
			ApplyCustomizationProfile_Replicable(*SavedCustomizationProfile);
		}
		else
		{
			ApplyCustomizationProfile_Replicable(CustomizationProfile);
		}
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
			UT_LOG_OWNER_ROLE(HCharacterCustomizationLog, Log, Server);
			ApplyCustomizationProfile_Server(InCustomizationProfile);
		}
		else
		{
			UT_LOG_OWNER_ROLE(HCharacterCustomizationLog, Log, Internal);
			ApplyCustomizationProfile_Internal(InCustomizationProfile);

			UT_LOG_OWNER_ROLE(HCharacterCustomizationLog, Log, Server);
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
	UT_LOG_OWNER_ROLE(HCharacterCustomizationLog, Log, Internal);
	ApplyCustomizationProfile_Internal(InCustomizationProfile);

	if (bMulticastProfileApplication)
	{
		UT_LOG_OWNER_ROLE(HCharacterCustomizationLog, Log, NetMulticast);
		ApplyCustomizationProfile_Multicast(InCustomizationProfile);
	}	
	else
	{
		UT_LOG_OWNER_ROLE(HCharacterCustomizationLog, Log, Client);
		ApplyCustomizationProfile_Client(InCustomizationProfile);
	}
}

void UHCharacterCustomizationComponent::ApplyCustomizationProfile_Multicast_Implementation(FCustomizationProfile InCustomizationProfile)
{
	UT_LOG_OWNER_ROLE(HCharacterCustomizationLog, Log, Internal);
	ApplyCustomizationProfile_Internal(InCustomizationProfile);
}

void UHCharacterCustomizationComponent::ApplyCustomizationProfile_Client_Implementation(FCustomizationProfile InCustomizationProfile)
{
	UT_LOG_OWNER_ROLE(HCharacterCustomizationLog, Log, Internal);
	ApplyCustomizationProfile_Internal(InCustomizationProfile);
}

void UHCharacterCustomizationComponent::ApplyCustomizationProfile_Internal(FCustomizationProfile InCustomizationProfile)
{
	if(CachedOwner == NULL)
		return;

	if (InCustomizationProfile.MetaData.IsValid() == false)
	{
		UT_LOG(HCharacterCustomizationLog, Error, TEXT("InCustomizationProfile is not valid."));
		return;
	}

	if(OnPreApplyCustomizationProfile.IsBound())
		OnPreApplyCustomizationProfile.Broadcast(this, InCustomizationProfile);

	UT_LOG(HCharacterCustomizationLog, Log, TEXT("ApplyCustomizationProfile %s to %s."), *InCustomizationProfile.MetaData.ToString(), CachedOwner->GetFName());

	CurrentCusomizationProfile = InCustomizationProfile;

	TMap<EAnatomy, FAnatomyProfile> AvailableAnatomyProfiles = DATATABLE_MANAGER()->GetAvailableAnatomyProfiles();
	if (AvailableAnatomyProfiles.IsEmpty())
	{
		UT_LOG(HCharacterCustomizationLog, Error, TEXT("No AvailableAnatomyProfiles"));
		return;
	}
	
	CurrentAnatomyProfile = *AvailableAnatomyProfiles.Find(CurrentCusomizationProfile.MetaData.Anatomy);
	if (CurrentAnatomyProfile.IsValid() == false)
	{	
		UT_LOG(HCharacterCustomizationLog, Error, TEXT("CurrentCustomizationProfile's Anatomy is not available."));
		return;
	}

	UpdateBasebody();	
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
	UT_LOG(HCharacterCustomizationLog, Log, TEXT("Start Load Asset"));

	if (OnStartLoadAsset.IsBound())
		OnStartLoadAsset.Broadcast();

	if (AssetPackagesToLoad.IsEmpty())
	{
		UT_LOG(HCharacterCustomizationLog, Warning, TEXT("No AssetPackesToLoad"));
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
	if(CachedOwner == NULL)
		return;

	if (CheckReplicateIndividualChagnes())
	{
		if(CachedOwner->GetLocalRole() == ENetRole::ROLE_Authority)
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

void UHCharacterCustomizationComponent::UpdateBasebody()
{
	if(CachedOwner == NULL)
		return;

	if(DATATABLE_MANAGER() == NULL)
		return;

	USkeletalMeshComponent* BodyComponent = CachedOwner->GetMesh();
	if(BodyComponent == NULL)
		return;
	
	USkeletalMeshComponent* HeadComponent =CachedOwner->GetHeadMeshComponent();
	if(HeadComponent == NULL)
		return;

	if (OnPreUpdateBasebody.IsBound())
	{
		OnPreUpdateBasebody.Broadcast(this, CurrentCusomizationProfile.Basebody, BodyComponent, HeadComponent);
	}

	if(BodyComponent->GetAnimationMode() == EAnimationMode::AnimationBlueprint)
		BodyComponent->SetAnimInstanceClass(CurrentAnatomyProfile.Body.AnimInstanceClass);

	if (CurrentAnatomyProfile.Heads.IsValidIndex(CustomizationProfile.Basebody.Head.Index) &&
		CurrentAnatomyProfile.Heads[CustomizationProfile.Basebody.Head.Index].AnimInstanceClass_Override)
	{
		HeadComponent->SetLeaderPoseComponent(nullptr, true);
		HeadComponent->SetAnimInstanceClass(CurrentAnatomyProfile.Heads[CustomizationProfile.Basebody.Head.Index].AnimInstanceClass_Override);
	}
	else
	{
		HeadComponent->SetLeaderPoseComponent(BodyComponent, true);
		HeadComponent->SetAnimInstanceClass(nullptr);
	}

	UpdateBodyComponent();
	UpdateHeadComponent();

	if (BodyComponent->GetAnimationMode() == EAnimationMode::AnimationBlueprint)
	{
		UpdateBasebodyMorphTargets();//CurrentAnatomyProfile.Customization.Basebody.MorphTargets
	}


	UpdateBasebodyAnimInstanceAlphas();

	const int NumBodyMaterials = BodyComponent->GetNumMaterials();
	for (int i = 0; i < NumBodyMaterials; i++)
	{
		BodyComponent->SetMaterial(i, nullptr);
	}

	const int NumHeadMaterials = HeadComponent->GetNumMaterials();
	for (int i = 0; i < NumHeadMaterials; i++)
	{
		HeadComponent->SetMaterial(i, nullptr);
	}

	UpdateSkinMaterials();
	UpdateEyesMaterials();

	if (OnPostUpdateBasebody.IsBound())
	{
		OnPostUpdateBasebody.Broadcast(this, CurrentCusomizationProfile.Basebody, BodyComponent, HeadComponent);
	}
}

void UHCharacterCustomizationComponent::UpdateBodyComponent()
{
	if(CachedOwner == NULL)
		return;

	USkeletalMeshComponent* BodyComponent = CachedOwner->GetMesh();
	if (BodyComponent == NULL)
		return;

	BodyComponent->SetSkinnedAssetAndUpdate(CurrentAnatomyProfile.Body.Mesh);

	UpdateLODSyncComponent();

	if(OnPostUpdateBodyComponent.IsBound())
		OnPostUpdateBodyComponent.Broadcast(this, BodyComponent);
}

void UHCharacterCustomizationComponent::UpdateHeadComponent()
{
	if(CachedOwner == NULL)
		return;

	USkeletalMeshComponent* HeadComponent = CachedOwner->GetHeadMeshComponent();
	if (HeadComponent == NULL)
		return;

	if (CurrentAnatomyProfile.Heads.IsValidIndex(CustomizationProfile.Basebody.Head.Index))
	{
		HeadComponent->SetSkinnedAssetAndUpdate(CurrentAnatomyProfile.Heads[CustomizationProfile.Basebody.Head.Index].Mesh);
	}
	else
	{
		UT_LOG(HCharacterCustomizationLog, Error, TEXT("CurrentAnatomyProfile's Heads doesn't have valid element on %d index"), CustomizationProfile.Basebody.Head.Index);
	}

	UpdateLODSyncComponent();

	if(OnPostUpdateHeadComponent.IsBound())
		OnPostUpdateHeadComponent.Broadcast(this, HeadComponent);
}

void UHCharacterCustomizationComponent::UpdateBasebodyMorphTargets()
{
	if(CachedOwner == NULL)
		return;

	USkeletalMeshComponent* BodyComponent = CachedOwner->GetMesh();
	if(BodyComponent == NULL)
		return;

	for (const auto Elem : CurrentCusomizationProfile.Basebody.MorphTargets)
	{
		BodyComponent->SetMorphTarget(Elem.Name, Elem.Value, true);
		if(OnSetBasebodyMorphTarget.IsBound())
			OnSetBasebodyMorphTarget.Broadcast(this, Elem.Name, Elem.Value);
	}

	if(OnPostUpdateBasebodyMorphTarget.IsBound())
		OnPostUpdateBasebodyMorphTarget.Broadcast(this, CurrentCusomizationProfile.Basebody.MorphTargets);
}

void UHCharacterCustomizationComponent::UpdateBasebodyAnimInstanceAlphas()
{
	if (CachedOwner == NULL)
		return;

	USkeletalMeshComponent* BodyComponent = CachedOwner->GetMesh();
	if(BodyComponent == NULL)
		return;

	
	UAnimInstance* AnimInstance = BodyComponent->GetAnimInstance();
	if(AnimInstance == NULL)
		return;

	for (const auto& Elem : CurrentCusomizationProfile.Basebody.AnimInstanceAlphas)
	{
		FProperty* Property = AnimInstance->GetClass()->FindPropertyByName(Elem.Name);
		Property->SetValue_InContainer(AnimInstance, &Elem.Value);
	}
}

void UHCharacterCustomizationComponent::UpdateSkinMaterials()
{
	if(CachedOwner == NULL)
		return;

	USkeletalMeshComponent* BodyComponent = CachedOwner->GetMesh();
	if(BodyComponent == NULL)
		return;

	BodyMIDs.Empty();
	HeadMIDs.Empty();

	TArray<FSlotMaterial_SkinBodyAndHead> LSkinMaterialSets = CurrentAnatomyProfile.Body.SkinMaterialSets;
	
	if(CurrentAnatomyProfile.Heads.IsValidIndex(CurrentCusomizationProfile.Basebody.Head.Index) == false)
		return;

	TArray<FSlotMaterial_SkinHead> CurrentAnatomySkinMaterialSets = CurrentAnatomyProfile.Heads[CurrentCusomizationProfile.Basebody.Head.Index].SkinMaterialSets_Override;

	int OverrideNum = CurrentAnatomySkinMaterialSets.Num();
	if(LSkinMaterialSets.Num() < OverrideNum)
		OverrideNum = LSkinMaterialSets.Num();

	for (int i = 0; i < OverrideNum; i++)
	{
		if (CurrentAnatomySkinMaterialSets.IsValidIndex(i) == false)
			continue;

		FSlotMaterial_SkinBodyAndHead Override;
		Override.Body = LSkinMaterialSets[i].Body;
		Override.Head = CurrentAnatomySkinMaterialSets[i].Head;

		LSkinMaterialSets[i] = Override;
	}

	if(LSkinMaterialSets.IsValidIndex(CurrentCusomizationProfile.Basebody.Skin.MaterialIndex) == false)
		return;

	FSlotMaterial_SkinBodyAndHead SelectedSkinMaterial = LSkinMaterialSets[CurrentCusomizationProfile.Basebody.Skin.MaterialIndex];
	for (auto& Elem : SelectedSkinMaterial.Body)
	{
		BodyComponent->Create
	}
}

void UHCharacterCustomizationComponent::UpdateEyesMaterials()
{

}

void UHCharacterCustomizationComponent::UpdateLODSyncComponent()
{
	if(CachedOwner == NULL)
		return;

	ULODSyncComponent* LODSyncComponent = CachedOwner->GetLODSyncComponent();
	if(LODSyncComponent == NULL)
		return;

	LODSyncComponent->ComponentsToSync.Empty();
	LODSyncComponent->CustomLODMapping.Empty();

	TArray<USkeletalMeshComponent*> NewLODDriverMeshComponents;
	NewLODDriverMeshComponents.AddUnique(CachedOwner->GetMesh());
	NewLODDriverMeshComponents.AddUnique(CachedOwner->GetHeadMeshComponent());
	
	for (USkeletalMeshComponent* NewLODDriverMeshComponent : NewLODDriverMeshComponents)
	{
		FComponentSync NewComponentSync(NewLODDriverMeshComponent->GetFName(), ESyncOption::Drive);
		LODSyncComponent->ComponentsToSync.Add(NewComponentSync);
	}

	TArray<USkeletalMeshComponent*> NewLODPassiveMeshComponents;
	NewLODPassiveMeshComponents.Append(CachedOwner->GetHairstyleMeshComponents());
	NewLODPassiveMeshComponents.Append(CachedOwner->GetAttachmentMeshComponents());
	NewLODPassiveMeshComponents.Append(CachedOwner->GetEquipmentMeshComponents());
	NewLODPassiveMeshComponents.Append(CachedOwner->GetGroomComponents());		
	if(bUseSkeletalMerging)
		NewLODPassiveMeshComponents.Append(CachedOwner->GetApparelMeshComponents());
	
	for (USkeletalMeshComponent* NewLODPassiveMeshComponent : NewLODPassiveMeshComponents)
	{
		FComponentSync NewComponentSync(NewLODPassiveMeshComponent->GetFName(), ESyncOption::Passive);
		LODSyncComponent->ComponentsToSync.Add(NewComponentSync);
	}
	
	TArray<USkeletalMeshComponent*> New4LODMeshComponents;
	New4LODMeshComponents.AddUnique(CachedOwner->GetMesh());
	New4LODMeshComponents.Append(CachedOwner->GetAttachmentMeshComponents());
	New4LODMeshComponents.Append(CachedOwner->GetEquipmentMeshComponents());
	if(bUseSkeletalMerging)
		New4LODMeshComponents.Append(CachedOwner->GetApparelMeshComponents());
	
	for (USkeletalMeshComponent* New4LODMeshComponent : New4LODMeshComponents)
	{
		FLODMappingData CustomLODMappingData;
		CustomLODMappingData.Mapping = {0, 0, 1, 1, 2, 2, 3, 3};
		LODSyncComponent->CustomLODMapping.Add(New4LODMeshComponent->GetFName(), CustomLODMappingData);
	}

	if (OnPostUpdateLODSyncComponent.IsBound())
	{
		OnPostUpdateLODSyncComponent.Broadcast(this, LODSyncComponent);
	}
}

#pragma endregion

#pragma region Helper
void UHCharacterCustomizationComponent::CreateMIDFromSlotAndMaterial(UMeshComponent* MeshComponent, FName MaterialSlotName, UMaterialInterface* SourceMaterial, TArray<UMaterialInstanceDynamic*> MIDs)
{
	if(MeshComponent == NULL)
		return;

	if(MeshComponent->IsMaterialSlotNameValid(MaterialSlotName) == false)
		return;

	int MaterialIndex = MeshComponent->GetMaterialIndex(MaterialSlotName);

	UMaterialInterface* Material = MeshComponent->GetMaterial(MaterialIndex);
	FName MIDName = *((SourceMaterial ? SourceMaterial->GetName() : Material->GetName()) + FString("_INST"));

	UMaterialInstanceDynamic* MID = MeshComponent->CreateDynamicMaterialInstance(MaterialIndex, SourceMaterial, MIDName);
	if(MID)
		MIDs.Add(MID);

}