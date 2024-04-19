#include "TestSaveObj.h"
#include "Serialization/MemoryReader.h"
#include "Serialization/MemoryWriter.h"

ATestSaveObj::ATestSaveObj(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}


FSaveDataRecord ATestSaveObj::SaveToRecord()
{
	FSaveDataRecord NewRecord = FSaveDataRecord();
	NewRecord.ActorClass = GetClass();
	NewRecord.ActorTransform = GetActorTransform();
	NewRecord.ActorName = GetName();
	NewRecord.ObjectID = GetUniqueID();			//record our own unique ID so we can correctly load the game later.



	//POINTER SAMPLE: If your object doesnt have pointers, you can skip this

	//Here is how we save a LIST of pointers. You can really save any type of data structure, using any scheme you want.
	//In this case, I'm first saving a number which indicates how many objects I'm going to be saving (meta data). If I have an array of 3 pointers, the first
	//number I save is 3. When I load, I'll see the number 3 and know that the next three numbers are going to indicate the unique ID's for 3 objects.
	//first, save the meta data
	NewRecord.PointerList.Add(TestList.Num());
	for (int32 a = 0; a < TestList.Num(); a++)
	{
		//Go through the list of pointers and figure out what their unique ID's are
		if (TestList[a] != NULL)
		{
			NewRecord.PointerList.Add(TestList[a]->GetUniqueID());
		}
		else
		{
			NewRecord.PointerList.Add(0);
		}
	}


	//Saving a single pointer is really easy: We just save the unique ID of the object we're pointing to.
	if(OtherObj != NULL)
	{
		NewRecord.PointerList.Add(1);	//this is totally optional! It's up to you to decide your saving schema and meta data identifiers.
		NewRecord.PointerList.Add(OtherObj->GetUniqueID());
	}
	else
	{
		NewRecord.PointerList.Add(0);	//null object marker
	}
	//END POINTER SAMPLE

	//store any properties which have CPF_SaveGame checked and store that in a binary data array
	FMemoryWriter Writer = FMemoryWriter(NewRecord.Data);
	Writer.ArIsSaveGame = true;
	Serialize(Writer);

	return NewRecord;
}

void ATestSaveObj::LoadFromRecord(FSaveDataRecord Record)
{
	FMemoryReader Reader = FMemoryReader(Record.Data);
	Serialize(Reader);
}

void ATestSaveObj::RelinkPointers(TMap<uint32, AActor*> ObjectDB, TArray<uint32> OIDList)
{
	//////////////////////////////////////
	//SAMPLE FOR FIXING UP POINTER LINKS//
	//////////////////////////////////////
	int i = 0;
	int32 count = OIDList[i++];	//pull the meta data on how many pointers we're restoring
	if (count > 0)
	{
		//fill in the test list with a variable number of actor references
		for (int32 counter = 0; counter < count; i++, counter++)
		{
			//do an OID lookup so we can match pointers
			if (OIDList[i] != 0)
			{
				TestList.Add(Cast<ATestSaveObj>(ObjectDB[OIDList[i]]));
			}
			else
			{
				TestList.Add(NULL);
			}
		}
	}


	//fix the link for the single pointer
	count = OIDList[i];
	if (count != 0)
	{
		uint32 uid = OIDList[++i];
		if (uid != 0)
		{
			OtherObj = Cast<ATestSaveObj>(ObjectDB[uid]);
		}
		else
		{
			OtherObj = NULL;
		}
	}
	

}