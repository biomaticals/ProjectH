#include "CustomGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/MemoryReader.h"
#include "Serialization/MemoryWriter.h"
#include "TestSaveObj.h"
#include "MySaveGame.h"

ACustomGameState::ACustomGameState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void ACustomGameState::ClearAllActors(TSubclassOf<AActor> ActorClass)
{

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ActorClass, FoundActors);
	for (int32 a = 0; a < FoundActors.Num(); a++)
	{
		FoundActors[a]->Destroy();
	}

	
}

void ACustomGameState::SaveActors(TSubclassOf<AActor> ActorClass)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ActorClass, FoundActors);

	for (int32 a = 0; a < FoundActors.Num(); a++)
	{
		ISaveable* SaveInterface = Cast<ISaveable>(FoundActors[a]);
		if (SaveInterface)
		{
			ObjectRecords.Add(SaveInterface->SaveToRecord());
		}
	}

}

void ACustomGameState::SaveGameState()
{
	ObjectRecords.Empty();

	//We're going to save all of our dynamic actors via their base class. Any inheriting actors will get their properties
	//saved. This will populate ObjectDB with a list of all objects of the given class.
	SaveActors(ATestSaveObj::StaticClass());


	//We're going to be writing to this block of binary data!
	TArray<uint8> BinaryDataBlock;
	FMemoryWriter MyWriter = FMemoryWriter(BinaryDataBlock);
	MyWriter.ArIsSaveGame = true;

	FSaveGameArchive Ar(MyWriter, false);

	//we call this->serialize which knows how to serialize itself. We're passing the "writer" as the archive which gets serialized to.
	//when this is complete, "BinaryDataBlock" will have all of the serialized data from ourself! This includes all of the FSaveDataRecord objects.
	Serialize(Ar);


	//now we want to write our serialized data to a file so that we can restore from it.
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	SaveGameInstance->PlayerName = TEXT("PLAYER_NAME");	//TODO: Create player profiles
	SaveGameInstance->ByteData = BinaryDataBlock;
	SaveGameInstance->SaveSlotName = TEXT("TestSave");
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}
void ACustomGameState::LoadGameState()
{

	//destroy everything dynamic in the game world
	ClearAllActors(ATestSaveObj::StaticClass());

	//sanity check
	ObjectRecords.Empty();

	UMySaveGame* LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	LoadGameInstance->SaveSlotName = TEXT("TestSave");
	LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));

	if (LoadGameInstance != NULL)
	{
		TArray<uint8> BinaryDataBlock = LoadGameInstance->ByteData;

		//This sets the context to READ from a binary block of data.
		FMemoryReader MyReader = FMemoryReader(BinaryDataBlock);
		FSaveGameArchive Ar(MyReader, true);

		//We are going to take the data in the block of binary data, deserialize it, and fill our class with the result.
		//our class knows how to serialize and deserialize itself, so this shouldn't be a problem.
		Serialize(Ar);

		//compare the current game version with the saved version. If the versions are incompatible, you're gonna have problems!
		if (BuildVersion != SaveVersion)
		{
			//print a nice friendly message to the user?
		}
		else
		{
			UWorld* World = GetWorld();

			TMap<uint32, AActor*> ObjectDB;
			//DESERIALIZATION: PASS 1
			//Restore all objects from the saved records
			for (int a = 0; a < ObjectRecords.Num(); a++)
			{
				UClass* SpawnedClass = ObjectRecords[a].ActorClass;
				FVector Pos = ObjectRecords[a].ActorTransform.GetLocation();
				FRotator Rot = ObjectRecords[a].ActorTransform.GetRotation().Rotator();
				int32 AssignedID = ObjectRecords[a].ObjectID;

				//We want to use deferred spawning because this lets any state logic in an actors construction script to run.
				AActor* newActor = World->SpawnActorDeferred<AActor>(SpawnedClass, ObjectRecords[a].ActorTransform);
				newActor->SetActorLabel(ObjectRecords[a].ActorName);

				//restore the actor to the object database, using the saved unique ID as the hash value. This is critical for relinking pointers.
				ObjectDB.Add(AssignedID, newActor);

				if (newActor)
				{
					//check to make sure the actor implements our save interface
					ISaveable* LoadInterface = Cast<ISaveable>(newActor);
					if (LoadInterface)
					{
						//Each object knows how to load itself!
						LoadInterface->LoadFromRecord(ObjectRecords[a]);
					}

					newActor->FinishSpawning(ObjectRecords[a].ActorTransform);
				}
			}

			//DESERIALIZATION: PASS 2
			//Now, we go through every actor and relink their pointer references
			PostFixupReferences(ObjectDB);

			//Don't need this anymore, so free up the memory!
			ObjectRecords.Empty();
		}
		
	}
}

void ACustomGameState::PostFixupReferences(TMap<uint32, AActor*> ObjectDB)
{

	//go through every object record, pull the ObjectID from the record, use that to find the loaded
	//actor in the ObjectDB, and then pass in the pointer list for the current object.
	for (int a = 0; a < ObjectRecords.Num(); a++)
	{
		uint32 uid = ObjectRecords[a].ObjectID;
		ISaveable* LoadInterface = Cast<ISaveable>(ObjectDB[uid]);
		if (LoadInterface)
		{
			LoadInterface->RelinkPointers(ObjectDB, ObjectRecords[a].PointerList);
		}
	}
}
