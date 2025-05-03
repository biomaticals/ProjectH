// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include <list>
#include "Common.h"
#include <fstream>

#define RESOURCE_MANAGER ResourceManager::GetResourceManager()

class ResourceManager
{
protected:
	ResourceManager();
	~ResourceManager();

public:
	static ResourceManager* GetResourceManager();
	
private:
	static ResourceManager* Instance;

public:
	void UpdateManager();

#pragma region Load & Unload
public:
	bool LoadResources();
	void UnloadResources();	
#pragma endregion

#pragma region Title
public:
	const std::string GetNextTitleContext();
	
private:
	std::filesystem::path TableOfContentsPath;
	std::ifstream ContextStream;

	unsigned int LatestFoundPart;
	unsigned int LatestFoundChapter;
	unsigned int LatestFoundSection;
	unsigned int LatestFoundCodeIndex;
	std::string LatestFoundContext;
#pragma endregion

#pragma region ExampleCode
public:
	bool LinkExampleCode();
	const FExampleCodeData GetSelectedExampleCodeData() const;

private:
	std::filesystem::path ExampleCodePath;
	std::ifstream ExampleCodeStream;
	FExampleCodeData SelectedExampleCodeData;
	bool bSelectedExampleChanged;

	std::vector<FExampleCodeData> ExampleCodeDataList;
#pragma endregion
};