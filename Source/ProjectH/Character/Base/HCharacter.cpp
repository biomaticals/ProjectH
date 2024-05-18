// Copyright 2024. Unique Turtle. All rights reserved.

#include "Character/Base/HCharacter.h"
#include "Character/Component/HCharacterCustomizationComponent.h"

FName AHCharacter::HeadMeshComponentName(TEXT("HeadMeshComponent"));
FName AHCharacter::HeadApparelComponentName(TEXT("HeadApparelComponent"));
FName AHCharacter::EarAccessoryComponentName(TEXT("EarAccessoryComponent"));
FName AHCharacter::UpperApparelComponentName(TEXT("UpperApparelComponent"));
FName AHCharacter::LowerApparelComponentName(TEXT("LowerApparelComponent"));
FName AHCharacter::FeetApparelComponentName(TEXT("FeetApparelComponent"));
FName AHCharacter::CharacterCustomizationComponentName(TEXT("CharacterCustomizationComponent"));
 
AHCharacter::AHCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	HeadMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(AHCharacter::HeadMeshComponentName);
	
	HeadApparelComponent = CreateDefaultSubobject<USkeletalMeshComponent>(AHCharacter::HeadApparelComponentName);
	HeadApparelComponent->SetupAttachment(GetMesh());

	EarAccessoryComponent = CreateDefaultSubobject<USkeletalMeshComponent>(AHCharacter::EarAccessoryComponentName);
	EarAccessoryComponent->SetupAttachment(GetMesh());

	UpperApparelComponent = CreateDefaultSubobject<USkeletalMeshComponent>(AHCharacter::UpperApparelComponentName);
	UpperApparelComponent->SetupAttachment(GetMesh());

	LowerApparelComponent = CreateDefaultSubobject<USkeletalMeshComponent>(AHCharacter::LowerApparelComponentName);
	LowerApparelComponent->SetupAttachment(GetMesh());

	FeetApparelComponent = CreateDefaultSubobject<USkeletalMeshComponent>(AHCharacter::FeetApparelComponentName);
	FeetApparelComponent->SetupAttachment(GetMesh());

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

USkeletalMeshComponent* AHCharacter::GetHeadApparelMeshComponent()
{
	return HeadApparelComponent;
}

USkeletalMeshComponent* AHCharacter::GetEarAccessoryComponent()
{
	return EarAccessoryComponent;
}

USkeletalMeshComponent* AHCharacter::GetUpperApparelComponent()
{
	return UpperApparelComponent;
}

USkeletalMeshComponent* AHCharacter::GetLowerApparelComponent()
{
	return LowerApparelComponent;
}

USkeletalMeshComponent* AHCharacter::GetFeetApparelComponent()
{
	return FeetApparelComponent;
}

UHCharacterCustomizationComponent* AHCharacter::GetCHaracterCustomizationComponent()
{
	return CharacterCustomizationComponent;
}