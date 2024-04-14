// Copy Rigts are in Team UniqueTurtle. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "System/SaveGame/HSaveGameObjectInterface.h"
#include "HCharacter.generated.h"

UCLASS()
class PROJECTH_API AHCharacter : public ACharacter, public IHSaveGameObjectInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


/** IHSaveGameObjectInterface ~ */
public:
	virtual const FString GetHSaveGameObjectKey_Implementation() const override;
	virtual const TArray<UObject*> GetHSaveGameObjectChildren_Implementation() const override;
	virtual bool WriteSaveGameObjectData_Implementation(FHSaveGameObjectData& SaveGameObjectData) override;
	virtual bool ReadSaveGameObjectData_Implementation(FHSaveGameObjectData& SaveGameObjectData) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int SaveTest = 0;


/** ~ IHSavveGameObjectInterface */
};
