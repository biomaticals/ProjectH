// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "Common.h"
#include "CoreMinimal.h"
#include <fstream>
#include <list>
#include <filesystem>

#define RESOURCE_MANAGER ResourceManager::GetResourceManager()

class ResourceManager
{
protected:
	ResourceManager();
	~ResourceManager();

public:
	static ResourceManager* GetResourceManager();
	static void Destroy();
	
private:
	static ResourceManager* Instance;

public:
	void Update();

#pragma region Load & Unload
public:
	bool LoadResources();
	void UnloadResources();	
#pragma endregion

#pragma region Title
public:
	bool LoadTitleContext();
	FBook GetBook() const;


	//bool GetNextTitleContext(ETitleType& OutTitleType, std::string& OutTitleContext);
	const std::string FindTitleContext(unsigned int InPart, unsigned int InChapter, unsigned int InSection, unsigned int InCodeIndex);
	
private:
	FBook Book;
	std::string TableOfContentsPath = "Resource\\TableOfContents.txt";
#pragma endregion
};