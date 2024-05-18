// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "System/SaveGame/HSaveGameObjectInterface.h"
#include "HCharacter.generated.h"

class UHCharacterCustomizationComponent;

UCLASS()
class PROJECTH_API AHCharacter : public ACharacter, public IHSaveGameObjectInterface
{
	GENERATED_BODY()
	 
public:
	AHCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Serialize(FArchive& Ar) override;

/** IHSaveGameObjectInterface ~ */
public:
	virtual const FString GetHSaveGameObjectID_Implementation() const override;
	virtual const FTransform GetHSaveGameObjectTransform_Implementation() const override;
/** ~ IHSavveGameObjectInterface */

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	USkeletalMeshComponent* GetHeadMeshComponent();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	USkeletalMeshComponent* GetHeadApparelMeshComponent();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	USkeletalMeshComponent* GetEarAccessoryComponent();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	USkeletalMeshComponent* GetUpperApparelComponent();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	USkeletalMeshComponent* GetLowerApparelComponent();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	USkeletalMeshComponent* GetFeetApparelComponent();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UHCharacterCustomizationComponent* GetCHaracterCustomizationComponent();

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, SaveGame)
	TObjectPtr<USkeletalMeshComponent> HeadMeshComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, SaveGame)
	TObjectPtr<USkeletalMeshComponent> HeadApparelComponent;	

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, SaveGame)
	TObjectPtr<USkeletalMeshComponent> EarAccessoryComponent;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, SaveGame)
	TObjectPtr<USkeletalMeshComponent> UpperApparelComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, SaveGame)
	TObjectPtr<USkeletalMeshComponent> LowerApparelComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, SaveGame)
	TObjectPtr<USkeletalMeshComponent> FeetApparelComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, SaveGame)
	TObjectPtr<UHCharacterCustomizationComponent> CharacterCustomizationComponent;

protected:
	static FName HeadMeshComponentName;
	static FName HeadApparelComponentName;
	static FName EarAccessoryComponentName;
	static FName UpperApparelComponentName;
	static FName LowerApparelComponentName;
	static FName FeetApparelComponentName;
	static FName CharacterCustomizationComponentName;
};
