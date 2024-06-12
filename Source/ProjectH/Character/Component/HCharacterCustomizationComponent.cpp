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

UHCharacterCustomizationComponent::UHCharacterCustomizationComponent(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
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

	#pragma region UpdateApparel
	SkinMasks = {"Hat Mask", "UpperBody Mask", "Hands Mask", "LowerBody Mask", "Socks Mask", "Feet Mask", "Accessory Mask", "Glasses Mask"};
	ShowAlternativeTexturesParameterName = "ShowAlternativeTextures";
	DefaultTexture = LoadObject<UTexture>(NULL, TEXT("/Engine/EngineResources/WhiteSquareTexture.WhiteSquareTexture"), NULL, LOAD_None, NULL);
	#pragma  endregion
}

void UHCharacterCustomizationComponent::BeginPlay()
{
	LoadPrimaryAsset();

	Super::BeginPlay();
}

TArray<TSubclassOf<UCharacterCustomizationDataAsset>> UHCharacterCustomizationComponent::GetHiddenCDAs()
{
	TArray<TSubclassOf<UCharacterCustomizationDataAsset>> LHiddenCDAs{};

	for (const FCDA_ApparelProfile Asset : CurrentCustomizationProfile.Apparel.DataAssets)
	{
		if(Asset.DataAsset->HiddenCCDAClasses.Num())
			LHiddenCDAs.Append(Asset.DataAsset->HiddenCCDAClasses);
	}

	for (const FCDA_EquipmentProfile Asset : CurrentCustomizationProfile.Equipment.DataAssets)
	{
		if (Asset.DataAsset->HiddenCCDAClasses.Num())
			LHiddenCDAs.Append(Asset.DataAsset->HiddenCCDAClasses);
	}

	for (const FCDA_HairstyleProfile Asset : CurrentCustomizationProfile.Hairstyle.DataAssets)
	{
		if (Asset.DataAsset->HiddenCCDAClasses.Num())
			LHiddenCDAs.Append(Asset.DataAsset->HiddenCCDAClasses);
	}

	for (const FCDA_GroomProfile Asset : CurrentCustomizationProfile.Groom.DataAssets)
	{
		if (Asset.DataAsset->HiddenCCDAClasses.Num())
			LHiddenCDAs.Append(Asset.DataAsset->HiddenCCDAClasses);
	}

	for (const FCDA_AttachmentProfile Asset : CurrentCustomizationProfile.Attachment.DataAssets)
	{
		if (Asset.DataAsset->HiddenCCDAClasses.Num())
			LHiddenCDAs.Append(Asset.DataAsset->HiddenCCDAClasses);
	}

	return LHiddenCDAs;
}

TMap<FName, FSlotTexture_SkinBodyAndHead> UHCharacterCustomizationComponent::GetCurrentSkinTextureSets()
{
	TMap<FName, FSlotTexture_SkinBodyAndHead> LSkinTextureSets = CurrentAnatomyProfile.Body.SkinTextureSets;

	if (CurrentAnatomyProfile.Heads.IsValidIndex(CurrentCustomizationProfile.Basebody.Head.Index) == false)
		return LSkinTextureSets;

	for (const auto& Elem : CurrentAnatomyProfile.Heads[CurrentCustomizationProfile.Basebody.Head.Index].SkinTextureSets_Override)
	{
		if (FSlotTexture_SkinBodyAndHead* Found = LSkinTextureSets.Find(Elem.Key))
		{
			FSlotTexture_SkinBodyAndHead NewValue;
			NewValue.Body = LSkinTextureSets.Find(Elem.Key)->Body;
			NewValue.Head = (CurrentAnatomyProfile.Heads[CurrentCustomizationProfile.Basebody.Head.Index].SkinTextureSets_Override.Find(Elem.Key))->Head;

			LSkinTextureSets.Add(Elem.Key, NewValue);
		}
	}

	TMap<FName, FSlotTexture_SkinBodyAndHead> LFilteredSkinTextureSets;
	for (const auto& Elem : LSkinTextureSets)
	{
		if (CurrentCustomizationProfile.Basebody.Skin.TextureSets.Contains(Elem.Key))
		{
			TPair<FName, FSlotTexture_SkinBodyAndHead> NewTextureSet;
			NewTextureSet.Key = Elem.Key;
			NewTextureSet.Value = Elem.Value;
			LFilteredSkinTextureSets.Add(NewTextureSet);
		}
	}

	return LFilteredSkinTextureSets;
}

FSlotMaterial_Eyes UHCharacterCustomizationComponent::GetCurrentEyesMaterialSet()
{
	TArray<FSlotMaterial_Eyes> LEyesMaterialSets = CurrentAnatomyProfile.Body.EyesMaterialSets;

	if (CurrentAnatomyProfile.Heads.IsValidIndex(CurrentCustomizationProfile.Basebody.Head.Index) == false)
		return FSlotMaterial_Eyes();

	int OverrideNum = LEyesMaterialSets.Num();
	TArray<FSlotMaterial_Eyes> EyesMaterialSets = CurrentAnatomyProfile.Heads[CurrentCustomizationProfile.Basebody.Head.Index].EyesMaterialSets_Override;
	if(EyesMaterialSets.Num() < OverrideNum)
		OverrideNum = EyesMaterialSets.Num();

	for (int i = 0 ; i < OverrideNum ; i++)
	{
		if (EyesMaterialSets.IsValidIndex(i))
		{
			LEyesMaterialSets[i] = EyesMaterialSets[i];
		}
	}

	if (LEyesMaterialSets.IsValidIndex(CurrentCustomizationProfile.Basebody.Eyes.MaterialIndex))
		return LEyesMaterialSets[CurrentCustomizationProfile.Basebody.Eyes.MaterialIndex];

	return FSlotMaterial_Eyes();
}

bool UHCharacterCustomizationComponent::IsCDAVisible(const UCharacterCustomizationDataAsset* CDA) const
{
	return !HiddenCDAs.Contains(CDA->GetClass());
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
	OnPostUpdateApparel.AddUObject(this, &UHCharacterCustomizationComponent::ApplyApparelSpecificSettings);

	DATATABLE_MANAGER()->UpdateAvailableAnatomyProfiles();
	DATATABLE_MANAGER()->UpdatePresetCustomizationProfiles();

}

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

USkeletalMeshComponent* UHCharacterCustomizationComponent::AddCDASkeletalComponent(UCDA_SkeletalMesh* CDASkeletalMesh, int MaterialVariantIndex, TArray<USkeletalMeshComponent*> SkeletalMeshComponents, TArray<UMaterialInstanceDynamic*> GlobalMIDs, TArray<FName> ActiveAdditionalMorphTargets,
	TArray<FHNamedFloat> ScalarParameters, TArray<FNamedHDRColor> HDRVectorParameters, FName SocketName, FTransform RelativeTransform, int CDAProfilesIndex)
{
	if(CachedOwner == NULL)
		return nullptr;

	USkeletalMeshComponent* BodyComponent = CachedOwner->GetMesh();
	if(BodyComponent == NULL)
		return nullptr;

	if (CDASkeletalMesh == NULL || CDASkeletalMesh->IsValidLowLevel() == false)
	{
		if(OnSkippedCDA.IsBound())
			OnSkippedCDA.Broadcast(this, CDASkeletalMesh, MaterialVariantIndex);

		if(OnSkippedCDASkeletal.IsBound())
			OnSkippedCDASkeletal.Broadcast(this, CDASkeletalMesh, MaterialVariantIndex);
	}

	USkeletalMeshComponent* NewSkeletalMeshComponent = Cast<USkeletalMeshComponent>(CachedOwner->AddComponentByClass(USkeletalMeshComponent::StaticClass(), true, RelativeTransform, false));
	SkeletalMeshComponents.AddUnique(NewSkeletalMeshComponent);

	NewSkeletalMeshComponent->RegisterComponent();
	CachedOwner->AddInstanceComponent(NewSkeletalMeshComponent);

	NewSkeletalMeshComponent->AttachToComponent(BodyComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	NewSkeletalMeshComponent->SetRelativeTransform(RelativeTransform);

	if (CDASkeletalMesh->SkeletalMesh)
	{
		NewSkeletalMeshComponent->SetSkinnedAssetAndUpdate(CDASkeletalMesh->SkeletalMesh, true);
	}

	TSubclassOf<UAnimInstance> PPAnimBP = CDASkeletalMesh->SkeletalMesh->GetPostProcessAnimBlueprint();
	if (PPAnimBP->IsValidLowLevel())
	{
		NewSkeletalMeshComponent->SetTickGroup(TG_PostPhysics);
		NewSkeletalMeshComponent->SetLeaderPoseComponent(NULL, true, false);
		NewSkeletalMeshComponent->SetAnimInstanceClass(PPAnimBP);
	}
	else
	{
		USkeletalMeshComponent* BodyMeshComponent = CachedOwner->GetMesh();
		NewSkeletalMeshComponent->SetLeaderPoseComponent(BodyMeshComponent, true, false);
	}

	CreateMIDFromMaterialVariant(NewSkeletalMeshComponent, CDASkeletalMesh->MaterialVariants, MaterialVariantIndex, GlobalMIDs, ScalarParameters, HDRVectorParameters);

	for (const auto& Elem : CDASkeletalMesh->AdditionalMorphTargets)
	{
		ActiveAdditionalMorphTargets.AddUnique(Elem.Key);
		BodyComponent->SetMorphTarget(Elem.Key, Elem.Value, true);
	}
	
	if (OnPostAddedCDA.IsBound())
	{
		OnPostAddedCDA.Broadcast(this, CDASkeletalMesh, NewSkeletalMeshComponent, CDAProfilesIndex);
	}
	
	if(OnPostAddedCDASkeletal.IsBound())
	{
		OnPostAddedCDASkeletal.Broadcast(this, CDASkeletalMesh, NewSkeletalMeshComponent, CDAProfilesIndex);
	}

	return NewSkeletalMeshComponent;
}

UStaticMeshComponent* UHCharacterCustomizationComponent::AddCDAStaticMeshComponent(UCDA_StaticMesh* CDAStaticMesh, int MaterialVariantIndex,
	TArray<UStaticMeshComponent*> StaticMeshComponents, TArray<UMaterialInstanceDynamic*> GlobalMIDs,
	TArray<FHNamedFloat> ScalarParameters, TArray<FNamedHDRColor> HDRVectorParameters, FName SocketName, FTransform RelativeTransform, int CDAProfilesIndex)
{
	if (CachedOwner == NULL)
		return nullptr;

	USkeletalMeshComponent* BodyComponent = CachedOwner->GetMesh();
	if (BodyComponent == NULL)
		return nullptr;

	if (CDAStaticMesh == NULL || CDAStaticMesh->IsValidLowLevel() == false)
	{
		if (OnSkippedCDA.IsBound())
			OnSkippedCDA.Broadcast(this, CDAStaticMesh, MaterialVariantIndex);

		if (OnSkippedCDAStaticMesh.IsBound())
			OnSkippedCDAStaticMesh.Broadcast(this, CDAStaticMesh, MaterialVariantIndex);
	}

	UStaticMeshComponent* NewStaticMeshComponent = Cast<UStaticMeshComponent>(CachedOwner->AddComponentByClass(UStaticMeshComponent::StaticClass(), true, RelativeTransform, false));
	StaticMeshComponents.AddUnique(NewStaticMeshComponent);

	NewStaticMeshComponent->RegisterComponent();
	CachedOwner->AddInstanceComponent(NewStaticMeshComponent);

	NewStaticMeshComponent->AttachToComponent(BodyComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	NewStaticMeshComponent->SetRelativeTransform(RelativeTransform);

	if (CDAStaticMesh->StaticMesh)
	{
		NewStaticMeshComponent->SetStaticMesh(CDAStaticMesh->StaticMesh);
		
		CreateMIDFromMaterialVariant(NewStaticMeshComponent, CDAStaticMesh->MaterialVariants, MaterialVariantIndex, GlobalMIDs, ScalarParameters, HDRVectorParameters);
	}



	if (OnPostAddedCDA.IsBound())
	{
		OnPostAddedCDA.Broadcast(this, CDAStaticMesh, NewStaticMeshComponent, CDAProfilesIndex);
	}

	if (OnPostAddedCDAStaticMesh.IsBound())
	{
		OnPostAddedCDAStaticMesh.Broadcast(this, CDAStaticMesh, NewStaticMeshComponent, CDAProfilesIndex);
	}

	return NewStaticMeshComponent;
}


bool UHCharacterCustomizationComponent::CleanCDAs(TArray<UPrimitiveComponent*> PrimitiveComponents, TArray<UMaterialInstanceDynamic*> GlobalMIDs, TArray<FName> ActiveAdditionalMorphTargets, int CDACount, FString DebugName)
{
	if(CachedOwner == NULL)
		return false;

	USkeletalMeshComponent* BodyComponent = CachedOwner->GetMesh();
	if(BodyComponent == NULL)
		return false;

	for (FName MorphTarget : ActiveAdditionalMorphTargets)
	{
		BodyComponent->SetMorphTarget(MorphTarget, 0.f, true);
	}
	
	ActiveAdditionalMorphTargets.Empty();

	if (CDACount > 0)
	{
		UpdateAdvancedCDAOptions();
	}
	else
	{
		UT_LOG(HCharacterCustomizationLog, Error, TEXT("%s is absent in CustomizationProfile."));
		return false;
	}

	return true;
}

void UHCharacterCustomizationComponent::CreateMIDFromMaterialVariant(UPrimitiveComponent* PrimitiveComponent, TArray<FMaterialVariants> MaterialVariants, int MaterialVariantIndex, TArray<UMaterialInstanceDynamic*> GlobalMIDs, TArray<FHNamedFloat> ScalarParameters, TArray<FNamedHDRColor> HDRVectorParameters)
{
	if(PrimitiveComponent == NULL)
		return;

	if (MaterialVariantIndex >= 0)
	{
		if(MaterialVariants.IsValidIndex(MaterialVariantIndex) == false)
			return;

		FMaterialVariants NewMaterialVariant = MaterialVariants[MaterialVariantIndex];
		for (int i = 0 ; i < NewMaterialVariant.Materials.Num() ; i ++)
		{
			UMaterialInstanceDynamic* NewMID = PrimitiveComponent->CreateDynamicMaterialInstance(i, NewMaterialVariant.Materials[i]);
			GlobalMIDs.AddUnique(NewMID);
		}
	}
	else
	{
		int MaterialsNum = PrimitiveComponent->GetNumMaterials();
		for (int i = 0; i < MaterialsNum; i++)
		{
			UMaterialInstanceDynamic* NewMID = PrimitiveComponent->CreateDynamicMaterialInstance(i, nullptr);
			GlobalMIDs.AddUnique(NewMID);
		}
	}

	for (UMaterialInstanceDynamic* GlobalMID : GlobalMIDs)
	{
		for (FHNamedFloat ScalarParameter : ScalarParameters)
		{
			GlobalMID->SetScalarParameterValue(ScalarParameter.Name, ScalarParameter.Value);
		}

		for (FNamedHDRColor HDRVectorParameter : HDRVectorParameters)
		{
			GlobalMID->SetVectorParameterValue(HDRVectorParameter.Name, HDRVectorParameter.Value.ToLinearColor());
		}
	}
}

void UHCharacterCustomizationComponent::CreateMIDFromSlotAndMaterial(UMeshComponent* MeshComponent, FName MaterialSlotName, UMaterialInterface* SourceMaterial, TArray<UMaterialInstanceDynamic*>& MIDs)
{
	if (MeshComponent == NULL)
		return;

	if (MeshComponent->IsMaterialSlotNameValid(MaterialSlotName) == false)
		return;

	int MaterialIndex = MeshComponent->GetMaterialIndex(MaterialSlotName);

	UMaterialInterface* Material = MeshComponent->GetMaterial(MaterialIndex);
	FName MIDName = *((SourceMaterial ? SourceMaterial->GetName() : Material->GetName()) + FString("_INST"));

	UMaterialInstanceDynamic* MID = MeshComponent->CreateDynamicMaterialInstance(MaterialIndex, SourceMaterial, MIDName);
	if (MID)
		MIDs.Add(MID);
}
#pragma endregion

#pragma region LoadAsset
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
#pragma endregion

#pragma region RepliacteSettings
bool UHCharacterCustomizationComponent::CheckReplicateIndividualChagnes() const
{
	return bReplicateIndividualChanges && CHECK_REPLIACTE_COMPONENT();
}

bool UHCharacterCustomizationComponent::CheckMulticastIndividualChanges() const
{
	return bMulticastIndividualChanges && CHECK_REPLIACTE_COMPONENT();
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

	CurrentCustomizationProfile = InCustomizationProfile;

	TMap<EAnatomy, FAnatomyProfile> AvailableAnatomyProfiles = DATATABLE_MANAGER()->GetAvailableAnatomyProfiles();
	if (AvailableAnatomyProfiles.IsEmpty())
	{
		UT_LOG(HCharacterCustomizationLog, Error, TEXT("No AvailableAnatomyProfiles"));
		return;
	}
	
	CurrentAnatomyProfile = *AvailableAnatomyProfiles.Find(CurrentCustomizationProfile.MetaData.Anatomy);
	if (CurrentAnatomyProfile.IsValid() == false)
	{	
		UT_LOG(HCharacterCustomizationLog, Error, TEXT("CurrentCustomizationProfile's Anatomy is not available."));
		return;
	}

	UpdateBasebody();
	UpdateApparel();
	UpdateEquipment();
	UpdateHairstyle();
	UpdateAttachment();
	UpdateMorphTargetsOnAllMeshes();
}
#pragma endregion

void UHCharacterCustomizationComponent::ApplyApparelSpecificSettings(UHCharacterCustomizationComponent* CharacterCustomizationComponent, FApparelProfile ApparelProfile, TArray<FCDA_ApparelProfile> AddingCCDA_Apparels, TArray<USkeletalMeshComponent*> AddingSkeletalMeshComponents, TArray<FCDA_ApparelProfile> SkippedCCDA_ApparelProfiles)
{
	for (FCDA_ApparelProfile AddingCCDA_Apparel : AddingCCDA_Apparels)
	{
		if (AddingCCDA_Apparel.DataAsset->IsA(UCDA_Apparel_Feet::StaticClass()))
		{
			UCDA_Apparel_Feet* CCDA_Apparel_Feet = Cast<UCDA_Apparel_Feet>(AddingCCDA_Apparel.DataAsset);
			CCDA_Apparel_Feet->RootOffset;
		}
	}
}

void UHCharacterCustomizationComponent::ClearApparelSpecificSettings(UHCharacterCustomizationComponent* CharacterCustomizationComponent, FApparelProfile ApparelProfile, TArray<USkeletalMeshComponent*> RemoveingSkeletalMeshComponents)
{

}

#pragma region AnimInstanceAlpha
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
	else
	{
		SetBasebodyAnimInstanceAlpha(Name, Value);
	}
}

void UHCharacterCustomizationComponent::SetBasebodyAnimInstanceAlpha_Multicast_Implementation(FName Name, float Value)
{
	SetBasebodyAnimInstanceAlpha(Name, Value);
}

void UHCharacterCustomizationComponent::SetBasebodyAnimInstanceAlpha(FName Name, float Value)
{
	CurrentCustomizationProfile.Basebody.AnimInstanceAlphas.AddUnique(FHNamedFloat(Name, Value));
}
#pragma endregion

#pragma region ApplyParameter
void UHCharacterCustomizationComponent::SetSkinScalarParameter_Replicable(FName Name, float Value)
{
	if (CachedOwner == NULL)
		return;

	if (CheckReplicateIndividualChagnes())
	{
		if (CachedOwner->GetLocalRole() == ENetRole::ROLE_Authority)
			SetSkinScalarParameter_Multicast(Name, Value);
		else
			SetSkinScalarParameter_Server(Name, Value);
	}
	else
	{
		SetSkinScalarParameter(Name, Value);
	}
}

void UHCharacterCustomizationComponent::SetSkinScalarParameter_Server_Implementation(FName Name, float Value)
{
	if (CheckMulticastIndividualChanges())
	{
		SetSkinScalarParameter_Multicast(Name, Value);
	}
	else
	{
		SetSkinScalarParameter(Name, Value);
	}
}

void UHCharacterCustomizationComponent::SetSkinScalarParameter_Multicast_Implementation(FName Name, float Value)
{
	SetSkinScalarParameter(Name, Value);
}

void UHCharacterCustomizationComponent::SetSkinScalarParameter(FName Name, float Value)
{
	CurrentCustomizationProfile.Basebody.Skin.ScalarParameters.Add(FHNamedFloat(Name, Value));
	
	TArray<UMaterialInstanceDynamic*> MIDs = BasebodyHeadSkinMIDs;
	MIDs.Append(BasebodyBodySkinMIDs);

	for (UMaterialInstanceDynamic* MID : MIDs)
	{
		MID->SetScalarParameterValue(Name, Value);
	}

	if(OnSetSkinScalarParameter.IsBound())
		OnSetSkinScalarParameter.Broadcast(this, Name, Value);
}

void UHCharacterCustomizationComponent::SetSkinHDRVectorParameter_Replicable(FName Name, FHDRColor HDRColor)
{
	if (CachedOwner == NULL)
		return;

	if (CheckReplicateIndividualChagnes())
	{
		if (CachedOwner->GetLocalRole() == ENetRole::ROLE_Authority)
			SetSkinHDRVectorParameter_Multicast(Name, HDRColor);
		else
			SetSkinHDRVectorParameter_Server(Name, HDRColor);
	}
	else
	{
		SetSkinHDRVectorParameter(Name, HDRColor);
	}
}

void UHCharacterCustomizationComponent::SetSkinHDRVectorParameter_Server_Implementation(FName Name, FHDRColor HDRColor)
{
	if (CheckMulticastIndividualChanges())
	{
		SetSkinHDRVectorParameter_Multicast(Name, HDRColor);
	}
	else
	{
		SetSkinHDRVectorParameter(Name, HDRColor);
	}
}

void UHCharacterCustomizationComponent::SetSkinHDRVectorParameter_Multicast_Implementation(FName Name, FHDRColor HDRColor)
{
	SetSkinHDRVectorParameter(Name, HDRColor);
}

void UHCharacterCustomizationComponent::SetSkinHDRVectorParameter(FName Name, FHDRColor HDRColor)
{
	CurrentCustomizationProfile.Basebody.Skin.HDRVectorParameters.Add(FNamedHDRColor(Name, HDRColor));

	TArray<UMaterialInstanceDynamic*> MIDs = BasebodyHeadSkinMIDs;
	MIDs.Append(BasebodyBodySkinMIDs);
	
	const FLinearColor LinearColor = HDRColor.ToLinearColor();

	for (UMaterialInstanceDynamic* MID : MIDs)
	{
		MID->SetVectorParameterValue(Name, LinearColor);
	}

	if (OnSetSkinHDRVectorParameter.IsBound())
		OnSetSkinHDRVectorParameter.Broadcast(this, Name, HDRColor);
}

void UHCharacterCustomizationComponent::SetEyesScalarParameter_Replicable(FName Name, float Value)
{
	if (CachedOwner == NULL)
		return;

	if (CheckReplicateIndividualChagnes())
	{
		if (CachedOwner->GetLocalRole() == ENetRole::ROLE_Authority)
			SetEyesScalarParameter_Server(Name, Value);
		else
			SetEyesScalarParameter_Multicast(Name, Value);
	}
	else
	{
		SetEyesScalarParameter(Name, Value);
	}
}

void UHCharacterCustomizationComponent::SetEyesScalarParameter_Server_Implementation(FName Name, float Value)
{
	if (CheckMulticastIndividualChanges())
	{
		SetEyesScalarParameter_Multicast(Name, Value);
	}
	else
	{
		SetEyesScalarParameter(Name, Value);
	}
}

void UHCharacterCustomizationComponent::SetEyesScalarParameter_Multicast_Implementation(FName Name, float Value)
{
	SetEyesScalarParameter(Name, Value);
}

void UHCharacterCustomizationComponent::SetEyesScalarParameter(FName Name, float Value)
{
	CurrentCustomizationProfile.Basebody.Eyes.ScalarParameters.Add(FHNamedFloat(Name, Value));

	for (UMaterialInstanceDynamic* MID : EyesMIDs)
	{
		if(MID)
			MID->SetScalarParameterValue(Name, Value);
	}

	if(OnSetEyesScalarParameter.IsBound())
		OnSetEyesScalarParameter.Broadcast(this, Name, Value);
}

void UHCharacterCustomizationComponent::SetEyesHDRVectorParameter_Replicable(FName Name, FHDRColor HDRColor)
{
	if (CachedOwner == NULL)
		return;

	if (CheckReplicateIndividualChagnes())
	{
		if (CachedOwner->GetLocalRole() == ENetRole::ROLE_Authority)
			SetEyesHDRVectorParameter_Server(Name, HDRColor);
		else
			SetEyesHDRVectorParameter_Multicast(Name, HDRColor);
	}
	else
	{
		SetEyesHDRVectorParameter(Name, HDRColor);
	}
}

void UHCharacterCustomizationComponent::SetEyesHDRVectorParameter_Server_Implementation(FName Name, FHDRColor HDRColor)
{
	if (CheckMulticastIndividualChanges())
	{
		SetEyesHDRVectorParameter_Multicast(Name, HDRColor);
	}
	else
	{
		SetEyesHDRVectorParameter(Name, HDRColor);
	}
}

void UHCharacterCustomizationComponent::SetEyesHDRVectorParameter_Multicast_Implementation(FName Name, FHDRColor HDRColor)
{
	SetEyesHDRVectorParameter(Name, HDRColor);
}

void UHCharacterCustomizationComponent::SetEyesHDRVectorParameter(FName Name, FHDRColor HDRColor)
{
	CurrentCustomizationProfile.Basebody.Eyes.HDRScalarParameters.Add(FNamedHDRColor(Name, HDRColor));

	for (UMaterialInstanceDynamic* MID : EyesMIDs)
	{
		if(MID)
			MID->SetVectorParameterValue(Name, HDRColor.ToLinearColor());
	}
	if (OnSetEyesHDRVectorParameter.IsBound())
		OnSetEyesHDRVectorParameter.Broadcast(this, Name, HDRColor);
}
#pragma endregion

#pragma region UpdateComponent
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
		OnPreUpdateBasebody.Broadcast(this, CurrentCustomizationProfile.Basebody, BodyComponent, HeadComponent);
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
		UpdateBasebodyMorphTargets();
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
		OnPostUpdateBasebody.Broadcast(this, CurrentCustomizationProfile.Basebody, BodyComponent, HeadComponent);
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

	for (const auto Elem : CurrentCustomizationProfile.Basebody.MorphTargets)
	{
		BodyComponent->SetMorphTarget(Elem.Name, Elem.Value, true);
		if(OnSetBasebodyMorphTarget.IsBound())
			OnSetBasebodyMorphTarget.Broadcast(this, Elem.Name, Elem.Value);
	}

	if(OnPostUpdateBasebodyMorphTarget.IsBound())
		OnPostUpdateBasebodyMorphTarget.Broadcast(this, CurrentCustomizationProfile.Basebody.MorphTargets);
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

	for (const auto& Elem : CurrentCustomizationProfile.Basebody.AnimInstanceAlphas)
	{
		FProperty* Property = AnimInstance->GetClass()->FindPropertyByName(Elem.Name);
		Property->SetValue_InContainer(AnimInstance, &Elem.Value);
	}

	if(OnPostUpdateBasebodyAnimInstanceAlphas.IsBound())
		OnPostUpdateBasebodyAnimInstanceAlphas.Broadcast(this, CurrentCustomizationProfile.Basebody.AnimInstanceAlphas);
}

void UHCharacterCustomizationComponent::UpdateSkinMaterials()
{
	if(CachedOwner == NULL)
		return;

	USkeletalMeshComponent* BodyComponent = CachedOwner->GetMesh();
	if(BodyComponent == NULL)
		return;

	USkeletalMeshComponent* HeadComponent = CachedOwner->GetHeadMeshComponent();
	if(HeadComponent == NULL)
		return;

	/** Step 1. Create MID */

	BasebodyBodySkinMIDs.Empty();
	BasebodyHeadSkinMIDs.Empty();

	TArray<FSlotMaterial_SkinBodyAndHead> LSkinMaterialSets = CurrentAnatomyProfile.Body.SkinMaterialSets;
	
	if(CurrentAnatomyProfile.Heads.IsValidIndex(CurrentCustomizationProfile.Basebody.Head.Index) == false)
		return;

	TArray<FSlotMaterial_SkinHead> CurrentAnatomySkinMaterialSets = CurrentAnatomyProfile.Heads[CurrentCustomizationProfile.Basebody.Head.Index].SkinMaterialSets_Override;

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

	if(LSkinMaterialSets.IsValidIndex(CurrentCustomizationProfile.Basebody.Skin.MaterialIndex) == false)
		return;

	FSlotMaterial_SkinBodyAndHead SelectedSkinMaterial = LSkinMaterialSets[CurrentCustomizationProfile.Basebody.Skin.MaterialIndex];
	for (const auto& Elem : SelectedSkinMaterial.Body)
	{
		CreateMIDFromSlotAndMaterial(BodyComponent, Elem.Key, Elem.Value, BasebodyBodySkinMIDs);
	}

	for (const auto& Elem : SelectedSkinMaterial.Head)
	{
		CreateMIDFromSlotAndMaterial(HeadComponent, Elem.Key, Elem.Value, BasebodyHeadSkinMIDs);
	}

	/** Step 2. Apply Parameters */
	const FSkinProfile CurrentSkinProfile = CurrentCustomizationProfile.Basebody.Skin;
	for (const auto& Elem : CurrentSkinProfile.ScalarParameters)
	{
		SetSkinScalarParameter(Elem.Name, Elem.Value);
	}

	for (const auto& Elem : CurrentSkinProfile.HDRVectorParameters)
	{
		SetSkinHDRVectorParameter(Elem.Name, Elem.Value);
	}

	UpdateSkinTextureSets();

	if(OnPostUpdateSkinMaterialSets.IsBound())
		OnPostUpdateSkinMaterialSets.Broadcast(this, CurrentSkinProfile, BasebodyBodySkinMIDs, BasebodyHeadSkinMIDs);
}

void UHCharacterCustomizationComponent::UpdateSkinTextureSets()
{
	if(DATATABLE_MANAGER() == NULL)
		return;

	const UDataTable* DefaultSkinTextureDataTable = DATATABLE_MANAGER()->GetDefaultSkinTexturesDataTable();
	for (FName ParameterName : ActiveSkinTextureSetsParameterNames_Body)
	{
		for (FName RowName : DefaultSkinTextureDataTable->GetRowNames())
		{
			FSkinTextureSetDefaultTexture* Found = DefaultSkinTextureDataTable->FindRow<FSkinTextureSetDefaultTexture>(RowName, GetName());
			if(Found)
			{
				for (UMaterialInstanceDynamic* BodyMID : BasebodyBodySkinMIDs)
				{
					BodyMID->SetTextureParameterValue(ParameterName, Found->Texture);
				}
			}
		}
	}
	ActiveSkinTextureSetsParameterNames_Body.Empty();

	for (FName ParameterName : ActiveSkinTextureSetsParameterNames_Head)
	{
		for (FName RowName : DefaultSkinTextureDataTable->GetRowNames())
		{
			FSkinTextureSetDefaultTexture* Found = DefaultSkinTextureDataTable->FindRow<FSkinTextureSetDefaultTexture>(RowName, GetName());
			if (Found)
			{
				for (UMaterialInstanceDynamic* HeadMID : BasebodyHeadSkinMIDs)
				{
					HeadMID->SetTextureParameterValue(ParameterName, Found->Texture);
				}
			}
		}
	}
	ActiveSkinTextureSetsParameterNames_Head.Empty();

	TMap<FName, FSlotTexture_SkinBodyAndHead> CurrentSkinTextureSets = GetCurrentSkinTextureSets();
	for (const auto& Elem : CurrentSkinTextureSets)
	{
		for (const auto& Body : Elem.Value.Body)
		{
			ActiveSkinTextureSetsParameterNames_Body.Add(Body.Key);
			
			for (UMaterialInstanceDynamic* BodyMID : BasebodyBodySkinMIDs)
			{
				BodyMID->SetTextureParameterValue(Body.Key, Body.Value);
			}
		}

		for (const auto& Head : Elem.Value.Head)
		{
			ActiveSkinTextureSetsParameterNames_Head.Add(Head.Key);

			for (UMaterialInstanceDynamic* HeadMID : BasebodyHeadSkinMIDs)
			{
				HeadMID->SetTextureParameterValue(Head.Key, Head.Value);
			}
		}
	}

	TArray<FSlotTexture_SkinBodyAndHead> Out;
	CurrentSkinTextureSets.GenerateValueArray(Out);

	if(OnPostUpdateSkinTextureSets.IsBound())
		OnPostUpdateSkinTextureSets.Broadcast(this, Out);
}

void UHCharacterCustomizationComponent::UpdateEyesMaterials()
{
	if (CachedOwner == NULL)
		return;

	USkeletalMeshComponent* HeadComponent = CachedOwner->GetHeadMeshComponent();
	if (HeadComponent == NULL)
		return;

	EyesMIDs.Empty();

	FSlotMaterial_Eyes CurrentEyeTextureSet = GetCurrentEyesMaterialSet();
	for (const auto& Elem : CurrentEyeTextureSet.Eyes)
	{
		CreateMIDFromSlotAndMaterial(HeadComponent, Elem.Key, Elem.Value, EyesMIDs);
	}

	for (const auto& Elem : CurrentCustomizationProfile.Basebody.Eyes.ScalarParameters)
	{
		SetEyesScalarParameter(Elem.Name, Elem.Value);
	}

	for (const auto& Elem : CurrentCustomizationProfile.Basebody.Eyes.HDRScalarParameters)
	{
		SetEyesHDRVectorParameter(Elem.Name, Elem.Value);
	}

	if(OnPostUpdateEyesMaterialSets.IsBound())
		OnPostUpdateEyesMaterialSets.Broadcast(this, CurrentCustomizationProfile.Basebody.Eyes, EyesMIDs);
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

	TArray<UMeshComponent*> NewLODDriverMeshComponents;
	NewLODDriverMeshComponents.AddUnique(CachedOwner->GetMesh());
	NewLODDriverMeshComponents.AddUnique(CachedOwner->GetHeadMeshComponent());
	
	for (UMeshComponent* NewLODDriverMeshComponent : NewLODDriverMeshComponents)
	{
		FComponentSync NewComponentSync(NewLODDriverMeshComponent->GetFName(), ESyncOption::Drive);
		LODSyncComponent->ComponentsToSync.Add(NewComponentSync);
	}

	TArray<UMeshComponent*> NewLODPassiveMeshComponents;
	NewLODPassiveMeshComponents.Append(CachedOwner->GetHairstyleMeshComponents());
	NewLODPassiveMeshComponents.Append(CachedOwner->GetAttachmentMeshComponents());
	NewLODPassiveMeshComponents.Append(CachedOwner->GetEquipmentMeshComponents());
	NewLODPassiveMeshComponents.Append(CachedOwner->GetGroomComponents());		
	if(bUseSkeletalMerging)
		NewLODPassiveMeshComponents.Append(CachedOwner->GetApparelMeshComponents());
	
	for (UMeshComponent* NewLODPassiveMeshComponent : NewLODPassiveMeshComponents)
	{
		FComponentSync NewComponentSync(NewLODPassiveMeshComponent->GetFName(), ESyncOption::Passive);
		LODSyncComponent->ComponentsToSync.Add(NewComponentSync);
	}
	
	TArray<UMeshComponent*> New4LODMeshComponents;
	New4LODMeshComponents.AddUnique(CachedOwner->GetMesh());
	New4LODMeshComponents.Append(CachedOwner->GetAttachmentMeshComponents());
	New4LODMeshComponents.Append(CachedOwner->GetEquipmentMeshComponents());
	if(bUseSkeletalMerging)
		New4LODMeshComponents.Append(CachedOwner->GetApparelMeshComponents());
	
	for (UMeshComponent* New4LODMeshComponent : New4LODMeshComponents)
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

void UHCharacterCustomizationComponent::UpdateMorphTargetsOnAllMeshes()
{
	if(CachedOwner == NULL)
		return;

	USkeletalMeshComponent* BodyMeshComponent = CachedOwner->GetMesh();
	if(BodyMeshComponent == NULL)
		return;

	TArray<USkeletalMeshComponent*> SkeletalMeshComponents;
	CachedOwner->GetComponents<USkeletalMeshComponent>(SkeletalMeshComponents);

	for (FHNamedFloat MorphTarget : CurrentCustomizationProfile.Basebody.MorphTargets)
	{
		for (USkeletalMeshComponent* SkeletalMeshComponent : SkeletalMeshComponents)
		{
			SkeletalMeshComponent->SetMorphTarget(MorphTarget.Name, MorphTarget.Value);
		}
	}

	for (FName MorphTargetName : ActiveAdditionalMorphTargets_Apparel)
	{
		float Value = BodyMeshComponent->GetMorphTarget(MorphTargetName);
		for (USkeletalMeshComponent* SkeletalMeshComponent : SkeletalMeshComponents)
		{
			SkeletalMeshComponent->SetMorphTarget(MorphTargetName, Value);
		}
	}

	for (FName MorphTargetName : ActiveAdditionalMorphTargets_Hairstyle)
	{
		float Value = BodyMeshComponent->GetMorphTarget(MorphTargetName);
		for (USkeletalMeshComponent* SkeletalMeshComponent : SkeletalMeshComponents)
		{
			SkeletalMeshComponent->SetMorphTarget(MorphTargetName, Value);
		}
	}

	for (FName MorphTargetName : ActiveAdditionalMorphTargets_Equipment)
	{
		float Value = BodyMeshComponent->GetMorphTarget(MorphTargetName);
		for (USkeletalMeshComponent* SkeletalMeshComponent : SkeletalMeshComponents)
		{
			SkeletalMeshComponent->SetMorphTarget(MorphTargetName, Value);
		}
	}

	if (OnPostUpdateMorphTargetOnAllMeshes.IsBound())
	{
		OnPostUpdateMorphTargetOnAllMeshes.Broadcast(this, CurrentCustomizationProfile.Basebody.MorphTargets, ActiveAdditionalMorphTargets_Apparel, ActiveAdditionalMorphTargets_Hairstyle, ActiveAdditionalMorphTargets_Equipment);
	}
}

void UHCharacterCustomizationComponent::UpdateSkeletalMerging()
{
	if(CachedOwner == NULL)
		return;

	USkeletalMeshComponent* BodyMeshComponent = CachedOwner->GetMesh();
	if(BodyMeshComponent == NULL)
		return;

	if (bUseSkeletalMerging == false)
	{
		return;
	}

	TArray<USkeletalMeshComponent*> LSkeletalMeshComponents;
	LSkeletalMeshComponents.AddUnique(BodyMeshComponent);
	LSkeletalMeshComponents.Append(CachedOwner->GetApparelMeshComponents());

	TArray<USkeletalMesh*> LSkeletalMeshes;
	for (USkeletalMeshComponent* SkeletalMeshComponent : LSkeletalMeshComponents)
	{
		if(SkeletalMeshComponent->GetSkeletalMeshAsset())
			LSkeletalMeshes.AddUnique(SkeletalMeshComponent->GetSkeletalMeshAsset());
	}

	//USkeletalMergingLibrary::MergeMeshes(const FSkeletalMeshMergeParams & Params)
	//BodyMeshComponent->SkeletalMesh->GetSkeleton()->USkeletalMesh*
	//SetSkinnedAssetandUpdate

	LSkeletalMeshComponents.Remove(BodyMeshComponent);
	for (USkeletalMeshComponent* SkeletalMeshComponent : LSkeletalMeshComponents)
	{
		if(SkeletalMeshComponent)
			SkeletalMeshComponent->Deactivate();
	}

	if (OnPostUpdateSkeletalMerging.IsBound())
	{
		OnPostUpdateSkeletalMerging.Broadcast(this, bUseSkeletalMerging, BodyMeshComponent);
	}
}
#pragma endregion

#pragma region UpdateApparel
void UHCharacterCustomizationComponent::UpdateApparel()
{
	if(CachedOwner == NULL)
		return;

	USkeletalMeshComponent* BodyComponent = CachedOwner->GetMesh();
	if(BodyComponent == NULL)
		return;

	TArray<USkeletalMeshComponent*> ApparelMeshComponents = CachedOwner->GetApparelMeshComponents();
	if(ApparelMeshComponents.IsEmpty())
		return;

	if(OnPreUpdateApparel.IsBound())
		OnPreUpdateApparel.Broadcast(this, CurrentCustomizationProfile.Apparel, ApparelMeshComponents);

	TArray<UPrimitiveComponent*> ApparelMeshComponents_Primitive;
	for (USkeletalMeshComponent* ApparelMeshComponent : ApparelMeshComponents)
	{
		if(ApparelMeshComponent)
			ApparelMeshComponents_Primitive.AddUnique(Cast<UPrimitiveComponent>(ApparelMeshComponent));
	}

	TArray<FCDA_ApparelProfile> SkippedApparelProfiles;
	TArray<FCDA_ApparelProfile> AddedApaarelProfiles;
	FApparelProfile ApparelProfile = CurrentCustomizationProfile.Apparel;
	if (CleanCDAs(ApparelMeshComponents_Primitive, ApparelMIDs, ActiveAdditionalMorphTargets_Apparel, CurrentCustomizationProfile.Apparel.DataAssets.Num(), "Apparel"))
	{
		for (int i = 0 ; i < CurrentCustomizationProfile.Apparel.DataAssets.Num() ; i ++)
		{
			if (USkeletalMeshComponent* NewSkeletalComponent = AddCDASkeletalComponent(ApparelProfile.DataAssets[i].DataAsset, ApparelProfile.DataAssets[i].MaterialVariantIndex,
			ApparelMeshComponents, ApparelMIDs, ActiveAdditionalMorphTargets_Apparel, ApparelProfile.GlobalScalarParameters,
			ApparelProfile.GlobalHDRVectorParameters, "", FTransform::Identity, i))
			{
				if(OnPostAddedCDAApparelProfile.IsBound())
					OnPostAddedCDAApparelProfile.Broadcast(this, CurrentCustomizationProfile.Apparel.DataAssets[i], NewSkeletalComponent, i);

				AddedApaarelProfiles.AddUnique(ApparelProfile.DataAssets[i]);
			}
			else
			{
				if(OnSkippedCDAAparelProfile.IsBound())
					OnSkippedCDAAparelProfile.Broadcast(this, CurrentCustomizationProfile.Apparel.DataAssets[i], i);

				SkippedApparelProfiles.AddUnique(ApparelProfile.DataAssets[i]);
			}	
		}
	}

	UpdateApparelBasebodyMasks();

	bool bUseAlternativeSkinTextures = false;
	for (FCDA_ApparelProfile Profile : CurrentCustomizationProfile.Apparel.DataAssets)
	{
		if(Profile.DataAsset && Profile.DataAsset->UseAlternativeSkinTexture)
		{
			bUseAlternativeSkinTextures = true;
			break;
		}
	}

	SetSkinScalarParameter(ShowAlternativeTexturesParameterName, bUseAlternativeSkinTextures);

	UpdateLODSyncComponent();

	if(OnPostUpdateApparel.IsBound())
		OnPostUpdateApparel.Broadcast(this, CurrentCustomizationProfile.Apparel, AddedApaarelProfiles, ApparelMeshComponents, SkippedApparelProfiles);
}

void UHCharacterCustomizationComponent::UpdateApparelBasebodyMasks()
{
	for (FName SkinMask : SkinMasks)
	{
		for (UMaterialInstanceDynamic* MID : BasebodyBodySkinMIDs)
		{
			if(MID)
				MID->SetTextureParameterValue(SkinMask, DefaultTexture);
		}
	}

	TArray<FName> LSelectedSkinMasks;
	for (FCDA_ApparelProfile ApparelProfile : CurrentCustomizationProfile.Apparel.DataAssets)
	{
		if (ApparelProfile.DataAsset && IsCDAVisible(ApparelProfile.DataAsset) && ApparelProfile.DataAsset->BasebodyMask)
		{
			for (UMaterialInstanceDynamic* MID : BasebodyBodySkinMIDs)
			{
				if (MID)
				{
					FName ParameterName = ApparelProfile.DataAsset->ToMaterialParameterName();
					MID->SetTextureParameterValue(ParameterName, ApparelProfile.DataAsset->BasebodyMask);
					LSelectedSkinMasks.AddUnique(ParameterName);
				}
			}
		}
	}

	if(OnPostUpdateApparelBasebodyMasks.IsBound())
		OnPostUpdateApparelBasebodyMasks.Broadcast(this, SkinMasks, LSelectedSkinMasks);
}

void UHCharacterCustomizationComponent::UpdateAdvancedCDAOptions()
{
	HiddenCDAs = GetHiddenCDAs();

	if(OnUpdateAdvancedCDAOptions.IsBound())
		OnUpdateAdvancedCDAOptions.Broadcast(this, HiddenCDAs);
}
#pragma endregion

#pragma region UpdateEquipment
void UHCharacterCustomizationComponent::UpdateEquipment()
{
	if(CachedOwner == NULL)
		return;

	TArray<USkeletalMeshComponent*> EquipmentMeshComponents = CachedOwner->GetEquipmentMeshComponents();

	if(OnPreUpdateEquipment.IsBound())
		OnPreUpdateEquipment.Broadcast(this, CurrentCustomizationProfile.Equipment, EquipmentMeshComponents);

	TArray<UPrimitiveComponent*> EquipmentMeshComponents_Primitive;
	for (USkeletalMeshComponent* EquipmentMesh : EquipmentMeshComponents)
	{
		if (UPrimitiveComponent* EquipmentMesh_Primitive = Cast<UPrimitiveComponent>(EquipmentMesh))
		{
			EquipmentMeshComponents_Primitive.AddUnique(EquipmentMesh_Primitive);
		}
	}

	TArray<FCDA_EquipmentProfile> SkippedEquipmentProfiles;
	TArray<FCDA_EquipmentProfile> AddedEquipmentProfiles;
	FEquipmentProfile EquipmentProfile = CurrentCustomizationProfile.Equipment;
	if (CleanCDAs(EquipmentMeshComponents_Primitive, EquipmentMIDs, ActiveAdditionalMorphTargets_Equipment, CurrentCustomizationProfile.Equipment.DataAssets.Num(), "Equipment"))
	{
		for (int i = 0 ; i < CurrentCustomizationProfile.Equipment.DataAssets.Num(); i ++)
		{
			if (USkeletalMeshComponent* NewSkeletalMeshComponents = AddCDASkeletalComponent(EquipmentProfile.DataAssets[i].DataAsset,
				EquipmentProfile.DataAssets[i].MaterialVariantIndex, EquipmentMeshComponents, EquipmentMIDs, ActiveAdditionalMorphTargets_Equipment,
				EquipmentProfile.GlobalScalarParameters, EquipmentProfile.GlobalHDRVectorParameters, EquipmentProfile.DataAssets[i].ParentSocket, EquipmentProfile.DataAssets[i].RelativeTransform, i))
			{
				if (OnPostAddedCDAEquipmentProfile.IsBound())
				{
					OnPostAddedCDAEquipmentProfile.Broadcast(this, EquipmentProfile.DataAssets[i], NewSkeletalMeshComponents, i);
				}

				//AddedEquipmentProfiles.AddUnique(EquipmentProfile.DataAssets[i]);
			}
			else
			{
				if (OnSkippedCDAEquipmentProfile.IsBound())
				{
					OnSkippedCDAEquipmentProfile.Broadcast(this, EquipmentProfile.DataAssets[i], i);
				}

				SkippedEquipmentProfiles.AddUnique(EquipmentProfile.DataAssets[i]);
			}
		}
	}

	UpdateLODSyncComponent();

	if (OnPostUpdateEquipment.IsBound())
	{
		OnPostUpdateEquipment.Broadcast(this, EquipmentProfile, AddedEquipmentProfiles, EquipmentMeshComponents, SkippedEquipmentProfiles);
	}
}
#pragma endregion

#pragma region UpdateHairstyle
void UHCharacterCustomizationComponent::UpdateHairstyle()
{
	if(CachedOwner == NULL)
		return;

	FHairstyleProfile HairstyleProfile = CurrentCustomizationProfile.Hairstyle;
	TArray<USkeletalMeshComponent*> HairstyleMeshComponents = CachedOwner->GetHairstyleMeshComponents();

	if (OnPreUpdateHairstyle.IsBound())
	{
		OnPreUpdateHairstyle.Broadcast(this, HairstyleProfile, HairstyleMeshComponents);
	}

	TArray<UPrimitiveComponent*> HairstyleMeshComponents_Primitive;
	for (USkeletalMeshComponent* HairstyleMesh : HairstyleMeshComponents)
	{
		if (UPrimitiveComponent* HairstyleMesh_Primitive = Cast<UPrimitiveComponent>(HairstyleMesh))
		{
			HairstyleMeshComponents_Primitive.AddUnique(HairstyleMesh);
		}
	}

	TArray<FCDA_HairstyleProfile> SkippedHairstyleProfiles;
	TArray<FCDA_HairstyleProfile> AddedHairstyleProfiles;
	if (CleanCDAs(HairstyleMeshComponents_Primitive, HairstyleMIDs, ActiveAdditionalMorphTargets_Hairstyle, CurrentCustomizationProfile.Hairstyle.DataAssets.Num(), "Hairstyle"))
	{
		for (int i = 0; i < CurrentCustomizationProfile.Hairstyle.DataAssets.Num(); i++)
		{
			if (USkeletalMeshComponent* NewSkeletalMeshComponents = AddCDASkeletalComponent(HairstyleProfile.DataAssets[i].DataAsset, -1, 
			HairstyleMeshComponents, HairstyleMIDs, ActiveAdditionalMorphTargets_Hairstyle, HairstyleProfile.GlobalScalarParameters, 
				HairstyleProfile.GlobalHDRVectorParameters, "", FTransform::Identity, i))
			{
				if (OnAddedCDAHairstyleProfile.IsBound())
				{
					OnAddedCDAHairstyleProfile.Broadcast(this, HairstyleProfile.DataAssets[i], NewSkeletalMeshComponents, i);
				}

				AddedHairstyleProfiles.AddUnique(HairstyleProfile.DataAssets[i]);
			}
			else
			{
				if (OnSkippedCDAHairstyleProfile.IsBound())
				{
					OnSkippedCDAHairstyleProfile.Broadcast(this, HairstyleProfile.DataAssets[i], i);
				}

				SkippedHairstyleProfiles.AddUnique(HairstyleProfile.DataAssets[i]);
			}
		}
	}

	UpdateLODSyncComponent();

	if (OnPostUpdateHairstyle.IsBound())
	{
		OnPostUpdateHairstyle.Broadcast(this, HairstyleProfile, AddedHairstyleProfiles, HairstyleMeshComponents, SkippedHairstyleProfiles);
	}
}
#pragma endregion

#pragma region
void UHCharacterCustomizationComponent::UpdateAttachment()
{
	if (CachedOwner == NULL)
		return;

	FAttachmentProfile AttachmentProfile = CurrentCustomizationProfile.Attachment;
	TArray<UStaticMeshComponent*> AttachmentMeshComponents = CachedOwner->GetAttachmentMeshComponents();

	if (OnPreUpdateAttachment.IsBound())
	{
		OnPreUpdateAttachment.Broadcast(this, AttachmentProfile, AttachmentMeshComponents);
	}

	TArray<UPrimitiveComponent*> AttachmentMeshComponents_Primitive;
	for (UStaticMeshComponent* AttachmentMesh : AttachmentMeshComponents)
	{
		if (UPrimitiveComponent* AttachmentMesh_Primitive = Cast<UPrimitiveComponent>(AttachmentMesh))
		{
			AttachmentMeshComponents_Primitive.AddUnique(AttachmentMesh);
		}
	}

	TArray<FCDA_AttachmentProfile> SkippedAttachmentProfiles;
	TArray<FCDA_AttachmentProfile> AddedAttachmentProfiles;
	if (CleanCDAs(AttachmentMeshComponents_Primitive, AttachmentsMIDs, ActiveAdditionalMorphTargets_Attachment, AttachmentProfile.DataAssets.Num(), "Attachment"))
	{
		for (int i = 0; i < AttachmentProfile.DataAssets.Num(); i++)
		{
			if (UStaticMeshComponent* NewStaticMeshComponent = AddCDAStaticMeshComponent(AttachmentProfile.DataAssets[i].DataAsset, -1,
				AttachmentMeshComponents, AttachmentsMIDs, AttachmentProfile.GlobalScalarParameters,
				AttachmentProfile.GlobalHDRVectorParameters, AttachmentProfile.DataAssets[i].ParentSocket, AttachmentProfile.DataAssets[i].RelativeTransform, i))
			{
				if (OnPostAddedCDAAttachmentProfile.IsBound())
				{
					OnPostAddedCDAAttachmentProfile.Broadcast(this, AttachmentProfile.DataAssets[i], NewStaticMeshComponent, i);
				}

				AddedAttachmentProfiles.AddUnique(AttachmentProfile.DataAssets[i]);
			}
			else
			{
				if (OnSkippedCDAAttachmentProfile.IsBound())
				{
					OnSkippedCDAAttachmentProfile.Broadcast(this, AttachmentProfile.DataAssets[i], i);
				}

				SkippedAttachmentProfiles.AddUnique(AttachmentProfile.DataAssets[i]);
			}
		}
	}

	UpdateLODSyncComponent();

	if (OnPostUpdateAttachment.IsBound())
	{
		OnPostUpdateAttachment.Broadcast(this, AttachmentProfile, AddedAttachmentProfiles, AttachmentMeshComponents, SkippedAttachmentProfiles);
	}
}