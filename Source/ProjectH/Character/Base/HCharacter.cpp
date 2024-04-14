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

const FString AHCharacter::GetHSaveGameObjectKey_Implementation() const
{
	return GetName();
}

const TArray<UObject*> AHCharacter::GetHSaveGameObjectChildren_Implementation() const
{
	return TArray<UObject*>();
}

bool AHCharacter::WriteSaveGameObjectData_Implementation(FHSaveGameObjectData& SaveGameObjectData)
{
	const FString& PropertyName = GET_MEMBER_NAME_STRING_CHECKED(AHCharacter, SaveTest);
	USaveGameManager::WriteObjectProperty(SaveGameObjectData, this, PropertyName);

	return true;
}

bool AHCharacter::ReadSaveGameObjectData_Implementation(FHSaveGameObjectData& SaveGameObjectData)
{
	USaveGameManager::ReadObjectProperty(SaveGameObjectData, this);

	return true;
}