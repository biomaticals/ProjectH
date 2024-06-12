// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "System/SaveGame/HSaveGameObjectInterface.h"
#include "HCharacter.generated.h"

class UHCharacterCustomizationComponent;
class ULODSyncComponent;

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
	TArray<USkeletalMeshComponent*> GetHairstyleMeshComponents();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<USkeletalMeshComponent*> GetApparelMeshComponents();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UStaticMeshComponent*> GetAttachmentMeshComponents();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<USkeletalMeshComponent*> GetEquipmentMeshComponents();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<USkeletalMeshComponent*> GetGroomComponents();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UHCharacterCustomizationComponent* GetCharacterCustomizationComponent();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ULODSyncComponent* GetLODSyncComponent();

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, SaveGame)
	TObjectPtr<USkeletalMeshComponent> HeadMeshComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, SaveGame)
	TArray<TObjectPtr<USkeletalMeshComponent>> HairstyleMeshComponents;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, SaveGame)
	TArray<TObjectPtr<USkeletalMeshComponent>> ApparelMeshComponents;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, SaveGame)
	TArray<TObjectPtr<UStaticMeshComponent>> AttachmentMeshComponents;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, SaveGame)
	TArray<TObjectPtr<USkeletalMeshComponent>> EquipmentMeshComponents;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, SaveGame)
	TArray<TObjectPtr<USkeletalMeshComponent>> GroomComponents;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, SaveGame)
	TObjectPtr<ULODSyncComponent> LODSyncComponent; 
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, SaveGame)
	TObjectPtr<UHCharacterCustomizationComponent> CharacterCustomizationComponent;

protected:
	static FName HeadMeshComponentName;
	static FName LODSyncComponentName;
	static FName CharacterCustomizationComponentName;
};
