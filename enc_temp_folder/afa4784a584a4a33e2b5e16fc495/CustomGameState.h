#pragma once

#include "GameFramework/GameState.h"
#include "ISaveable.h"
#include "ProjectH.h"

#include "CustomGameState.generated.h"

UCLASS()
class ACustomGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	ACustomGameState(const FObjectInitializer& ObjectInitializer);

	/*******************************************************************
	* LOADING / SAVING
	********************************************************************/

	//Increment this every time you release a new game build **which makes savegames incompatible!!**
	//This is the current version of the game build. If this doesn't match the serialized version, the savegame file
	//is out of date and shouldn't be loaded!
	const uint32 BuildVersion = 1;

	//Increment this every time you release a new game build **which makes savegames incompatible!!**
	//We're going to be checking this number against the loaded version to see if there are any compatibility mismatches.
	//this number is saved with the savegame file, so if a user loads a savegame which contains an older number than the build,
	//you will have incompatible savegame data. Try to fail gracefully in the background instead of failing hard.
	UPROPERTY(SaveGame)
		uint32 SaveVersion = 1;

	//This is the data which gets saved to disk. This is sort of "transient", where there is no data in here except during
	//loading and saving the game state.
	UPROPERTY(SaveGame)
		TArray<FSaveDataRecord> ObjectRecords;

	UFUNCTION(BlueprintCallable, Category = "Records")
		virtual void SaveGameState();

	UFUNCTION(BlueprintCallable, Category = "Records")
		virtual void LoadGameState();

private:
	//Saves all actors of a given class to disk.
	void SaveActors(TSubclassOf<AActor> ActorClass);

	/*Goes through the level and destroys every actor of the given class*/
	void ClearAllActors(TSubclassOf<AActor> ActorClass);

	virtual void PostFixupReferences(TMap<uint32, AActor*> ObjectDB);
	
};