// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "ResourceManager.h"
#include "format"

ResourceManager* ResourceManager::Instance = nullptr;

ResourceManager::ResourceManager()
{
#pragma region Title
	TableOfContentsPath = std::filesystem::path("Resource\\TableOfContents.txt");
	ContextStream = std::ifstream(TableOfContentsPath, std::ios::in);
#pragma endregion
}

ResourceManager::~ResourceManager()
{
	if (ContextStream.is_open())
	{
		ContextStream.close();
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
}

#pragma region Load & Unload
bool ResourceManager::LoadResources()
{
	return true;
}

void ResourceManager::UnloadResources()
{
	if (ContextStream.is_open())
	{
		ContextStream.close();
	}
}
#pragma endregion

#pragma region Title
const std::string ResourceManager::GetNextTitleContext(TitleType& OutTitleType)
{
	std::string Line{};
	std::string Found{};

	while (std::getline(ContextStream, Line))
	{
		auto Position = Line.find(": ");

		if (Position != std::string::npos)
		{
			size_t Offset = 0;
			const std::string Result = LeftTrim(Line, Offset);

			if (Offset == 0)
			{
				OutTitleType = TitleType::TitleType_Part;
			}
			else if (Offset == 1)
			{
				OutTitleType = TitleType::TitleType_Chapter;
			}
			else if (Offset == 2)
			{
				OutTitleType = TitleType::TitleType_Section;
			}
			else if (Offset == 3)
			{
				OutTitleType = TitleType::TitleType_ExampleCode;
			}
			else
			{
				OutTitleType = TitleType::TitleType_None;
			}


			return Result;
		}
	}

	return "";
}

const std::string ResourceManager::FindTitleContext(unsigned int InPart, unsigned int InChapter, unsigned int InSection, unsigned int InCodeIndex)
{
	std::ifstream _ContextStream(TableOfContentsPath, std::ios::in);

	std::string Line{};
	std::string Found{};
	std::string Keyword = std::format("Part {:02}", InPart);
	if (InPart != 0)
	{
		while (std::getline(_ContextStream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::string::npos)
			{
				Found = std::string(Line).substr(Position);
				break;
			}
		}
	}

	if (InChapter != 0)
	{
		Keyword = std::format("Chapter {:02}", InChapter);
		while (std::getline(_ContextStream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::string::npos)
			{
				Found = std::string(Line).substr(Position);
				break;
			}
		}
	}

	if (InSection != 0)
	{
		Keyword = std::format("Section {:02}", InSection);
		while (std::getline(_ContextStream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::string::npos)
			{
				Found = std::string(Line).substr(Position);
				break;
			}
		}
	}

	if (InCodeIndex != 0)
	{
		Keyword = std::format("Code {}-{}", InChapter, InCodeIndex);
		while (std::getline(_ContextStream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::string::npos)
			{
				Found = std::string(Line).substr(Position);
				break;
			}
		}
	}

	return Found;
}
#pragma endregion