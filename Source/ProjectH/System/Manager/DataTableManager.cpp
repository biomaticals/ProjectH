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
}

#pragma region CharacterCustomization
bool UDataTableManager::UpdateAvaiableAnatomyProfiles()
{
	if(NeedUpdatAnatomyProfiles == false)
		return true;

	if (AnatomyProfilesDataTable == nullptr || AnatomyProfilesDataTable->IsValidLowLevel() == false)
	{
		UT_LOG(HLog, Error, TEXT("[AnatomyProfilesDataTable] is invalid."));
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

	return Success;
}

TMap<EAnatomy, FAnatomyProfile> UDataTableManager::GetAvailableAnatomyProfiles()
{
	if(NeedUpdatAnatomyProfiles && UpdateAvaiableAnatomyProfiles() == false)
		return TMap<EAnatomy, FAnatomyProfile>();

	return AvailableAnatomyProfiles;
}