// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	Instance = nullptr;
	bSelectedExampleChanged = false;
	TableOfContentsPath = std::filesystem::path("Resource\\TableOfContents.txt");
}

ResourceManager::~ResourceManager()
{

}

ResourceManager* ResourceManager::GetResourceManager()
{
	if (Instance == nullptr)
	{
		Instance = new ResourceManager();
	}

	return Instance;
}

bool ResourceManager::LoadResources()
{

}

void ResourceManager::UnloadResources()
{

}

#pragma region Title
const std::string ResourceManager::FindContext(unsigned int Part, unsigned int Chapter, unsigned int Section, unsigned int CodeIndex)
{
	std::string Line{};
	std::string Found{};

	std::string Keyword = std::format("Part {:02}", Part);
	if (Part != 0)
	{
		while (std::getline(Stream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::string::npos)
			{
				Found = std::string(Line).substr(Position);
				RecentPosition_ContextFound = Position;
				break;
			}
		}
	}

	if (Chapter != 0)
	{
		Keyword = std::format("Chapter {:02}", Chapter);
		while (std::getline(Stream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::string::npos)
			{
				Found = std::string(Line).substr(Position);
				RecentPosition_ContextFound = Position;
				break;
			}
		}
	}

	if (Section != 0)
	{
		Keyword = std::format("Section {:02}", Section);
		while (std::getline(Stream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::string::npos)
			{
				Found = std::string(Line).substr(Position);
				RecentPosition_ContextFound = Position;
				break;
			}
		}
	}

	if (CodeIndex != 0)
	{
		Keyword = std::format("Code {}-{}", Chapter, CodeIndex);
		while (std::getline(Stream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::string::npos)
			{
				Found = std::string(Line).substr(Position);
				RecentPosition_ContextFound = Position;
				break;
			}
		}
	}

	return Found;
}
#pragma endregion

#pragma region ExampleCode
auto ResourceManager::UpdateSelectedExample(unsigned int Part, unsigned int Chapter, unsigned int Section, unsigned int CodeIndex)
{
	if (SelectedExampleCodeData.Part == Part && SelectedExampleCodeData.Chapter == Chapter && SelectedExampleCodeData.Section == Section && SelectedExampleCodeData.CodeIndex == CodeIndex)
	{
		bSelectedExampleChanged = false;
		return;
	}

	bSelectedExampleChanged = true;
	FExampleCodeData Target = FExampleCodeData(Part, Chapter, Section, CodeIndex);
	auto Result = std::find(ExampleCodeDataList.begin(), ExampleCodeDataList.end(), Target);
	SelectedExampleCodeData = Result._Ptr->_Myval;
}

bool ResourceManager::LinkExampleCode()
{
	std::ifstream Stream(TableOfContentsPath, std::ios::in);
	std::string Line{};
	std::string Found{};
	if (Stream.is_open())
	{
		while (std::getline(Stream, Line))
		{
			if (auto Position = Line.find("Part"); Position != std::string::npos)
			{
				Found = std::string(Line).substr(Position);
				break;
			}
		}
	}
	return Found;
}

const FExampleCodeData ResourceManager::GetExampleCodeData() const
{
	return SelectedExampleCodeData;
}
#pragma endregion