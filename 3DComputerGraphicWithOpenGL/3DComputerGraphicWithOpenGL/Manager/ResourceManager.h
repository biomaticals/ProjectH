// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include <list>
#include "Common.h"
#include <fstream>

class ResourceManager
{
protected:
	ResourceManager();
	~ResourceManager();

public:
	ResourceManager* GetResourceManager();

private:
	static ResourceManager* Instance;

#pragma region Load & Unload
public:
	bool LoadResources();
	void UnloadResources();
#pragma endregion

#pragma region Title
public:
	const std::string FindContext(unsigned int Part, unsigned int Chapter, unsigned int Section, unsigned int CodeIndex);
	
private:
	std::filesystem::path TableOfContentsPath;
	std::ifstream Stream(TableOfContentsPath, std::ios::in);
	
#pragma endregion

#pragma region ExampleCode
public:
	bool LinkExampleCode();
	const FExampleCodeData GetExampleCodeData() const;

private:
	FExampleCodeData SelectedExampleCodeData;
	bool bSelectedExampleChanged;
#pragma endregion


	std::vector<FExampleCodeData> ExampleCodeDataList;
private:
	auto UpdateSelectedExample(unsigned int Part, unsigned int Chapter, unsigned int Section, unsigned int CodeIndex);
};