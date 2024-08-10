// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "AssetTypeActions_Base.h"
#include "EnumKeyBasedDataTableFactory.generated.h"


class FAssetTypeActions_EnumKeyBasedDataTable : public FAssetTypeActions_Base
{
public:
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_EnumBasedDataTable", "Enum Key Based DataTable"); }
	virtual FColor GetTypeColor() const override { return FColor(102, 51, 51); }
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Misc; }
};

/**
 * 
 */
UCLASS(hideCategories = Object)
class UTASSETEDITOR_API UEnumKeyBasedDataTableFactory : public UFactory
{
	GENERATED_UCLASS_BODY()

public:

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	
	virtual bool ShouldShowInNewMenu() const override;
};
