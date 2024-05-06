// Copy Rigts are in Team UniqueTurtle. 


#include "System/Manager/DataTableManager.h"
#include "Common/CommonStruct.h"
#include "Common/CommonEnum.h"
#include "Common/CommonTableRow.h"
#include "ProjectH.h"

void UDataTableManager::ValidateDataTables()
{
	// CharacterCustomization
	ensure(AnatomyProfilesDataTable);
	ensure(PresetCustomizationProfilesDataTable);
}

#pragma region CharacterCustomization
bool UDataTableManager::UpdateAvailableAnatomyProfiles()
{
	UT_LOG(HLog, Log, TEXT("Start UDataTableManager::UpdateAvailableAnatomyProfiles"));

	if(NeedUpdatAnatomyProfiles == false)
		return true;

	if (AnatomyProfilesDataTable == nullptr || AnatomyProfilesDataTable->IsValidLowLevel() == false)
	{
		UT_LOG(HLog, Error, TEXT("[AnatomyProfilesDataTable] is invalid."));
		return false;
	}

	AvailableAnatomyProfiles.Empty();	

	bool Success = true;

	for (EAnatomy Anatomy : TEnumRange<EAnatomy>())
	{
		FString AnatomyString = EnumToString((uint8)Anatomy, TEXT("/Script/ProjectH.EAnatomy"));
		FAnatomyProfile* Data = AnatomyProfilesDataTable->FindRow<FAnatomyProfile>(FName(AnatomyString), 
		*FString::Printf(TEXT("[AnatomyProfilesDataTable] doesn't have Row \"%s\""), *AnatomyString), true);
	
		if(Data == nullptr || Data->IsValid())
			Success = false;
		else
			AvailableAnatomyProfiles.Add(MakeTuple(Anatomy, *Data));
	}
	
	if(AvailableAnatomyProfiles.IsEmpty())
		Success = false;

	NeedUpdatAnatomyProfiles = !Success;

	ensureMsgf(Success, TEXT("UDataTableManager::UpdateAvailableAnatomyProfiles() failed."));

	return Success;
}

bool UDataTableManager::UpdatePresetCustomizationProfiles()
{
	UT_LOG(HLog, Log, TEXT("Start UDataTableManager::UpdatePresetCustomizationProfiles"));

	ensureMsgf(UpdateAvailableAnatomyProfiles(), TEXT("UpdateAvailableAnatomyProfiles() should be precede but it fails."));

	if (NeedUpdatePresetCustomizationProfiles == false)
		return true;

	if (PresetCustomizationProfilesDataTable == nullptr || PresetCustomizationProfilesDataTable->IsValidLowLevel() == false)
	{
		UT_LOG(HLog, Error, TEXT("[PresetCustomizationProfilesDataTable] is invalid."));
	}

	PresetCustomizationProfiles.Empty();

	bool Success = true;

	TArray<FCustomizationProfile*> DataTableRows;
	PresetCustomizationProfilesDataTable->GetAllRows<FCustomizationProfile>(*PresetCustomizationProfilesDataTable->GetName(), DataTableRows);
	
	for (FCustomizationProfile* DataTableRow : DataTableRows)
	{
		if(DataTableRow->MetaData.Name.IsEmpty())
		{
			Success = false;
			continue;
		}

		if (AvailableAnatomyProfiles.Find(DataTableRow->MetaData.Anatomy))
		{
			FName AnatomyString = *EnumToString((uint8)(DataTableRow->MetaData.Anatomy), TEXT("/Script/ProjectH.EAnatomy"));
			PresetCustomizationProfiles.Add(MakeTuple(AnatomyString, DataTableRow->MetaData));
		}
		else
		{
			Success = false;
			continue;
		}
	}

	if (AvailableAnatomyProfiles.IsEmpty())
		Success = false;

	NeedUpdatePresetCustomizationProfiles = !Success;

	ensureMsgf(Success, TEXT("UDataTableManager::UpdatePresetCustomizationProfiles() failed."));

	return Success;
}

TMap<EAnatomy, FAnatomyProfile> UDataTableManager::GetAvailableAnatomyProfiles()
{
	if(NeedUpdatAnatomyProfiles && UpdateAvailableAnatomyProfiles() == false)
		return TMap<EAnatomy, FAnatomyProfile>();

	return AvailableAnatomyProfiles;
}

TMap<FName, FCustomizationProfileMetaData> UDataTableManager::GetPresetCustomizationProfiles()
{
	if(NeedUpdatePresetCustomizationProfiles && UpdatePresetCustomizationProfiles())
		return TMap<FName, FCustomizationProfileMetaData>();

	return PresetCustomizationProfiles;
}

void UDataTableManager::SetNeedUpdateAnatomyProfiles()
{
	NeedUpdatAnatomyProfiles = true;
}

void UDataTableManager::SetNeedUpdatePresetCustomizationProfiles()
{
	NeedUpdatePresetCustomizationProfiles = true;
}
#pragma endregion