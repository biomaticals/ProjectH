// Copy Rigts are in Team UniqueTurtle. 


#include "Character/Base/HCharacter.h"
#include "System/Manager/SaveGameManager.h"

// Sets default values
AHCharacter::AHCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

// Called to bind functionality to input
void AHCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

const FString AHCharacter::GetHSaveGameObjectID_Implementation() const
{
	return GetName();
}

const FTransform AHCharacter::GetHSaveGameObjectTransform_Implementation() const
{
	return GetTransform();
}