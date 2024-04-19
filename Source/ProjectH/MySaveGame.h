#pragma once

#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

UCLASS()
class UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UMySaveGame();

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Basic")
	int32 TestData;

	UPROPERTY()
	TArray<uint8> ByteData;

};
