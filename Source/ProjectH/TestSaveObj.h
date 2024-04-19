#pragma once
#include "GameFramework/Actor.h"
#include "ISaveable.h"

#include "TestSaveObj.generated.h"

UCLASS()
class ATestSaveObj : public AActor, public ISaveable
{
	GENERATED_BODY()

public:

	ATestSaveObj(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame, Category = "Test")
	float SaveMeFloat = 0;

	//Testing the de/serialization of a pointer (causes a crash if you mark "savegame")
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Test")
	ATestSaveObj* OtherObj = NULL;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Test")
	TArray<ATestSaveObj*> TestList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Test")
	TSoftClassPtr<ATestSaveObj> SavePtr = NULL;
	//void Serialize(FArchive& Ar) override;

	//ISaveable Interface implementation:
	FSaveDataRecord SaveToRecord() override;
	void LoadFromRecord(FSaveDataRecord Record) override;
	void RelinkPointers(TMap<uint32, AActor*> ObjectDB, TArray<uint32> OIDList) override;
	//End ISaveable Interface
};