// Copyright 2024. Unique Turtle. All rights reserved.


#include "EnumKeyBasedDataTableFactory.h"
#include "EnumKeyBasedDataTable.h"

UClass* FAssetTypeActions_EnumKeyBasedDataTable::GetSupportedClass() const
{
	return UEnumKeyBasedDataTable::StaticClass();
}

UEnumKeyBasedDataTableFactory::UEnumKeyBasedDataTableFactory(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bCreateNew = true;

	SupportedClass = UEnumKeyBasedDataTable::StaticClass();
	bEditAfterNew = 1;
}

UObject* UEnumKeyBasedDataTableFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UEnumKeyBasedDataTable>(InParent, InClass, InName, Flags);
}

bool UEnumKeyBasedDataTableFactory::ShouldShowInNewMenu() const
{
	return true;
}