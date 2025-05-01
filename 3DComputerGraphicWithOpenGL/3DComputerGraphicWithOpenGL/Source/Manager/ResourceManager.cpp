// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "ResourceManager.h"

ResourceManager* ResourceManager::Instance = nullptr;

ResourceManager::ResourceManager()
{
#pragma region Title
	TableOfContentsPath = std::filesystem::path("Resource\\TableOfContents.txt");
	ContextStream = std::ifstream();
	LatestFoundPart = 0;
	LatestFoundChapter = 0;
	LatestFoundSection = 0;
	LatestFoundCodeIndex = 0;
#pragma endregion

#pragma region ExampleCode	
	ExampleCodePath = std::filesystem::path("Resource\\ExampleCode.txt");
	ExampleCodeStream = std::ifstream();
	SelectedExampleCodeData = FExampleCodeData();
	bSelectedExampleChanged = false;
	ExampleCodeDataList = std::vector<FExampleCodeData>();
	ExampleCodeDataList.reserve(100);
#pragma endregion
}

ResourceManager::~ResourceManager()
{
	if (ContextStream.is_open())
	{
		ContextStream.close();
	}

	if (ExampleCodeStream.is_open())
	{
		ExampleCodeStream.close();
	}

	if (ExampleCodeDataList.size() > 0)
	{
		ExampleCodeDataList.clear();
	}

	if (Instance != nullptr)
	{
		delete Instance;
		Instance = nullptr;
	}
}

const ResourceManager* ResourceManager::GetResourceManager() const
{
	if (Instance == nullptr)
	{
		Instance = new ResourceManager();
	}

	return Instance;
}

bool ResourceManager::LoadResources()
{
	return true;
}

void ResourceManager::UnloadResources()
{

}

#pragma region Title
const std::string ResourceManager::FindContext(unsigned int Part, unsigned int Chapter, unsigned int Section, unsigned int CodeIndex)
{
	ContextStream = std::ifstream(TableOfContentsPath, std::ios::in);

	std::string Line{};
	std::string Found{};

	std::string Keyword = std::format("Part {:02}", Part);
	if (Part != 0 && Part != LatestFoundPart)
	{
		while (std::getline(ContextStream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::string::npos)
			{
				Found = std::string(Line).substr(Position);
				LatestFoundPart = Part;
				break;
			}
		}
	}

	if (Chapter != 0 && Chapter != LatestFoundChapter)
	{
		Keyword = std::format("Chapter {:02}", Chapter);
		while (std::getline(ContextStream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::string::npos)
			{
				Found = std::string(Line).substr(Position);
				LatestFoundChapter = Chapter;
				break;
			}
		}
	}

	if (Section != 0 && Section != LatestFoundSection)
	{
		Keyword = std::format("Section {:02}", Section);
		while (std::getline(ContextStream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::string::npos)
			{
				Found = std::string(Line).substr(Position);
				LatestFoundSection = Section;
				break;
			}
		}
	}

	if (CodeIndex != 0 && CodeIndex != LatestFoundCodeIndex)
	{
		Keyword = std::format("Code {}-{}", Chapter, CodeIndex);
		while (std::getline(ContextStream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::string::npos)
			{
				Found = std::string(Line).substr(Position);
				LatestFoundCodeIndex = CodeIndex;
				break;
			}
		}
	}

	if (Found != "")
	{
		LatestFoundContext = Found;
		return Found;
	}
	
	return LatestFoundContext;

}
#pragma endregion

#pragma region ExampleCode
//auto ResourceManager::UpdateSelectedExample(unsigned int Part, unsigned int Chapter, unsigned int //Section, unsigned int CodeIndex)
//{
//	if (SelectedExampleCodeData.Part == Part && SelectedExampleCodeData.Chapter == Chapter && //SelectedExampleCodeData.Section == Section && SelectedExampleCodeData.CodeIndex == CodeIndex)
//	{
//		bSelectedExampleChanged = false;
//		return;
//	}
//
//	bSelectedExampleChanged = true;
//	FExampleCodeData Target = FExampleCodeData(Part, Chapter, Section, CodeIndex);
//	auto Result = std::find(ExampleCodeDataList.begin(), ExampleCodeDataList.end(), Target);
//	SelectedExampleCodeData = Result._Ptr->_Myval;
//}

bool ResourceManager::LinkExampleCode()
{
	ExampleCodePath = std::filesystem::path("Resource\\ExampleCode.txt");

	ExampleCodeStream = std::ifstream(ExampleCodePath, std::ios::in);
	if (!ExampleCodeStream.is_open())
	{
		std::cerr << "Failed to open ExampleCode.txt" << std::endl;
		return false;
	}

	std::string Line{};
	while (std::getline(ExampleCodeStream, Line))
	{
		FExampleCodeData ExampleCodeData = FExampleCodeData();
		if (Line.find("Part") != std::string::npos)
		{
			ExampleCodeData.Part = std::stoi(Line.substr(Line.find("Part") + 5));
		}
		else if (Line.find("Chapter") != std::string::npos)
		{
			ExampleCodeData.Chapter = std::stoi(Line.substr(Line.find("Chapter") + 8));
		}
		else if (Line.find("Section") != std::string::npos)
		{
			ExampleCodeData.Section = std::stoi(Line.substr(Line.find("Section") + 8));
		}
		else if (Line.find("Code") != std::string::npos)
		{
			std::string CodeIndexString = Line.substr(Line.find("Code") + 5);
			size_t DelimiterPosition = CodeIndexString.find('-');
			if (DelimiterPosition != std::string::npos)
			{
				CodeIndexString = CodeIndexString.substr(0, DelimiterPosition);
			}
			else
			{
				CodeIndexString = CodeIndexString.substr(CodeIndexString.find(' ') + 1);
			}
			ExampleCodeData.CodeIndex = std::stoi(CodeIndexString);
			//UpdateSelectedExample(ExampleCodeData.Part, ExampleCodeData.Chapter, ExampleCodeData.Section, ExampleCodeData.CodeIndex);
			break;
		}

		if (bSelectedExampleChanged)
			break;

	}
	return true;
}

const FExampleCodeData ResourceManager::GetSelectedExampleCodeData() const
{
	return SelectedExampleCodeData;
}
#pragma endregion