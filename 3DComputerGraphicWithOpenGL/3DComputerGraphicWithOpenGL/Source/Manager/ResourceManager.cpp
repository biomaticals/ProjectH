// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "ResourceManager.h"

ResourceManager* ResourceManager::Instance = nullptr;

ResourceManager::ResourceManager()
{
#pragma region Title
	TableOfContentsPath = std::filesystem::path("Resource\\TableOfContents.txt");
	ContextStream = std::ifstream(TableOfContentsPath, std::ios::in);
	LatestFoundPart = 0;
	LatestFoundChapter = 0;
	LatestFoundSection = 0;
	LatestFoundCodeIndex = 0;
#pragma endregion

#pragma region ExampleCode	
	ExampleCodePath = std::filesystem::path("Resource\\ExampleCode.txt");
	ExampleCodeStream = std::ifstream(ExampleCodePath, std::ios::in);
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

	Destroy();
}

ResourceManager* ResourceManager::GetResourceManager()
{
	if (Instance == nullptr)
	{
		Instance = new ResourceManager();
	}

	return Instance;
}

void ResourceManager::Destroy()
{
	if (Instance != nullptr)
	{
		delete Instance;
		Instance = nullptr;
	}
}

void ResourceManager::Update()
{
	ContextStream = std::ifstream(TableOfContentsPath, std::ios::in);
	ExampleCodeStream = std::ifstream(ExampleCodePath, std::ios::in);
}

#pragma region Load & Unload
bool ResourceManager::LoadResources()
{
	return true;
}

void ResourceManager::UnloadResources()
{

}
#pragma endregion

#pragma region Title
const std::string ResourceManager::GetNextTitleContext()
{
	std::string Line{};
	std::string Found{};

	while (std::getline(ContextStream, Line))
	{
		auto Position = Line.find(": ");

		if (Position != std::string::npos)
		{
			Found = std::string(Line).substr(Position + 1);
			return Found;
		}
	}

	return "";
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