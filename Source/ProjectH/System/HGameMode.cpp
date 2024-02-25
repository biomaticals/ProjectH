// Copy Rigts are in Team UniqueTurtle. 


#include "System/HGameMode.h"
#include "ProjectH.h"
#include "System/HWorldSettings.h"

void AHGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	if(GetWorld() == nullptr)
		return;

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::LoadGame);
}

void AHGameMode::LoadGame()
{
	bool bLoadSuccess = LoadAssets();
	
	if(bLoadSuccess == false)
		UT_LOG(HLog, Fatal, TEXT("LoadAssets fails."));

	
}

bool AHGameMode::LoadAssets()
{
	AHWorldSettings* WorldSettings =  Cast<AHWorldSettings>(GetWorldSettings());
	if (WorldSettings == nullptr)
	{
		UT_LOG(HLog, Fatal, TEXT("Assign a valid WorldSettings, kinds of AHWorldSettings."));
		return false;
	}

	if (WorldSettings->GetDefaultExperienceDefinition() == nullptr)
	{
		UT_LOG(HLog, Fatal, TEXT("Assign a valid WorldSettings, kinds of AHWorldSettings."));
		return false;

	}


	//UAssetRegistryHelpers::GetAssetRegistry()
	
	return true;
}