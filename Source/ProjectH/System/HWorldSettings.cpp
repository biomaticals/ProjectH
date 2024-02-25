// Copy Rigts are in Team UniqueTurtle. 


#include "System/HWorldSettings.h"
#include "Experience/HExperienceDefinition.h"

TSoftClassPtr<UHExperienceDefinition> AHWorldSettings::GetDefaultExperienceDefinition()
{ 
	return DefaultExperienceDefinition.IsValid() ? DefaultExperienceDefinition.Get() : nullptr; 
}
