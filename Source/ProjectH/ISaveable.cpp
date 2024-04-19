#include "ISaveable.h"
#include "Serialization/MemoryReader.h"
#include "Serialization/MemoryWriter.h"

USaveable::USaveable(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

FSaveDataRecord ISaveable::SaveToRecord()
{
	//need to figure out how I can get a reference to the owning actor
	//NewRecord.ActorClass = GetOwner()->GetClass();
	//NewRecord.ActorTransform = GetActorTransform();
	//NewRecord.ActorName = GetName();

	//store any properties which have CPF_SaveGame checked and store that in a binary data array
	//FMemoryWriter Writer = FMemoryWriter(NewRecord.Data);
	//Writer.ArIsSaveGame = true;
	//Serialize(Writer);


	return FSaveDataRecord();
}

void ISaveable::LoadFromRecord(FSaveDataRecord Record)
{
	
}

void ISaveable::RelinkPointers(TMap<uint32, AActor*> ObjectDB, TArray<uint32> OIDList)
{

}

bool ISaveable::IsTransient() const
{
	return false;
}