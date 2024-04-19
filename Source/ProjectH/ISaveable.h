#pragma once

#include "GameFramework/GameState.h"
#include "CoreMinimal.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "ISaveable.generated.h"

USTRUCT()
struct FSaveDataRecord
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(SaveGame)
		UClass* ActorClass;

	UPROPERTY(SaveGame)
		FTransform ActorTransform;

	UPROPERTY(SaveGame)
		FString ActorName;

	//This is for fixing up pointer references on the second pass of deserialization.
	UPROPERTY(SaveGame)
		uint32 ObjectID = -1;

	//This contains a list of object id's which correspond to pointer references.
	UPROPERTY(SaveGame)
	TArray<uint32> PointerList;

	//extra data for actor specific implementations
	UPROPERTY(SaveGame)
		TArray<uint8> Data;

	//might be able to do an internal serialize here...
	FORCEINLINE FArchive& Serialize(FArchive& Ar)
	{
		Ar << ActorClass;
		Ar << ActorTransform;
		Ar << ActorName;
		Ar << ObjectID;
		Ar << Data;
		return Ar;
	}
};

struct FSaveGameArchive : public FObjectAndNameAsStringProxyArchive
{
	FSaveGameArchive(FArchive& InInnerArchive, bool bInLoadIfFindFails)
		: FObjectAndNameAsStringProxyArchive(InInnerArchive, bInLoadIfFindFails)
	{
		ArIsSaveGame = true;
	}
};

UINTERFACE(Blueprintable)
class USaveable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ISaveable
{
	GENERATED_IINTERFACE_BODY()

public:
	//UFUNCTION(BlueprintCallable, Category = "Saveable")
	virtual FSaveDataRecord SaveToRecord();

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Saveable")
	virtual void LoadFromRecord(FSaveDataRecord Record);

	//Some objects should not be saved (such as pop up menu items).
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Saveable")
	virtual bool IsTransient() const;

	//called when all object instances have been loaded and spawned. Use this to fixup pointer references.
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Saveable")
	virtual void RelinkPointers(TMap<uint32, AActor*> ObjectDB, TArray<uint32> OIDList);
};