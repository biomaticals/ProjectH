// Copyright 2024. Unique Turtle. All rights reserved.


#include "Character/Base/HCharacter.h"
#include "Character/Component/HCharacterCustomizationComponent.h"
#include "System/Manager/SaveGameManager.h"

FName AHCharacter::CharacterCustomizationComponentName(TEXT("CharacterCustomizationComponent"));

AHCharacter::AHCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	CharacterCustomizationComponent = CreateDefaultSubobject<UHCharacterCustomizationComponent>(AHCharacter::CharacterCustomizationComponentName);
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

UHCharacterCustomizationComponent* AHCharacter::GetCHaracterCustomizationComponent()
{
	return CharacterCustomizationComponent;
}