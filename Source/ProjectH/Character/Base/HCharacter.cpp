// Copyright 2024. Unique Turtle. All rights reserved.

#include "Character/Base/HCharacter.h"
#include "Character/Component/HCharacterCustomizationComponent.h"
#include "Components/LODSyncComponent.h"

FName AHCharacter::HeadMeshComponentName(TEXT("HeadMeshComponent"));
FName AHCharacter::CharacterCustomizationComponentName(TEXT("CharacterCustomizationComponent"));
FName AHCharacter::LODSyncComponentName(TEXT("LODSyncComponent"));
 
AHCharacter::AHCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	HeadMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(AHCharacter::HeadMeshComponentName);
	HeadMeshComponent->SetupAttachment(GetMesh());

	CharacterCustomizationComponent = CreateDefaultSubobject<UHCharacterCustomizationComponent>(AHCharacter::CharacterCustomizationComponentName);
	
	LODSyncComponent = CreateDefaultSubobject<ULODSyncComponent>(AHCharacter::LODSyncComponentName);
}

// Called when the game starts or when spawned
void AHCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHCharacter::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if(CharacterCustomizationComponent)
		CharacterCustomizationComponent->Serialize(Ar);
}

// Called to bind functionality to input
void AHCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/** IHSaveGameObjectInterface ~ */
const FString AHCharacter::GetHSaveGameObjectID_Implementation() const
{
	return GetName();
}

const FTransform AHCharacter::GetHSaveGameObjectTransform_Implementation() const
{
	return GetTransform();
}
/** ~ IHSavveGameObjectInterface */

USkeletalMeshComponent* AHCharacter::GetHeadMeshComponent()
{
	return HeadMeshComponent;
}

TArray<USkeletalMeshComponent*> AHCharacter::GetHairstyleMeshComponents()
{
	return HairstyleMeshComponents;
}

TArray<USkeletalMeshComponent*> AHCharacter::GetApparelMeshComponents()
{
	return ApparelMeshComponents;
}

TArray<USkeletalMeshComponent*> AHCharacter::GetAttachmentMeshComponents()
{
	return AttachmentMeshComponents;
}

TArray<USkeletalMeshComponent*> AHCharacter::GetEquipmentMeshComponents()
{
	return EquipmentMeshComponents;
}

TArray<USkeletalMeshComponent*> AHCharacter::GetGroomComponents()
{
	return GroomComponents;
}

UHCharacterCustomizationComponent* AHCharacter::GetCharacterCustomizationComponent()
{
	return CharacterCustomizationComponent;
}

ULODSyncComponent* AHCharacter::GetLODSyncComponent()
{
	return LODSyncComponent;
}