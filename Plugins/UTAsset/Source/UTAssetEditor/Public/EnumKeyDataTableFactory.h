// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Factories/DataTableFactory.h"
#include "AssetTypeActions_Base.h"
#include "EnumKeyDataTableFactory.generated.h"

class UEnumKeyDataTable;

class FAssetTypeActions_EnumKeyDataTable : public FAssetTypeActions_Base
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
class UTASSETEDITOR_API UEnumKeyDataTableFactory : public UDataTableFactory
{
	GENERATED_UCLASS_BODY()

public:
	virtual bool ConfigureProperties() override;
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	
	virtual bool ShouldShowInNewMenu() const override;

protected:
	virtual UDataTable* MakeNewDataTable(UObject* InParent, FName Name, EObjectFlags Flags);
};