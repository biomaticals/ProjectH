// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "ResourceManager.h"
#include "format"

ResourceManager* ResourceManager::Instance = nullptr;

ResourceManager::ResourceManager()
{

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
bool ResourceManager::LoadTitleContext()
{

	std::filesystem::path TableOfContentsPath = std::filesystem::path("Resource\\TableOfContents.txt");
	std::ifstream ContextStream(TableOfContentsPath, std::ios::in);

	FPart* CurrentPart = nullptr;
	FChapter* CurrentChapter = nullptr;
	FSection* CurrentSection = nullptr;
	std::string Line{};
	while (std::getline(ContextStream, Line))
	{
		size_t Indent = 0;
		while (Indent < Line.size() && Line[Indent] == '\t')
		{
			++Indent;
		}

		std::string Title = Line.substr(Indent);

		switch (Indent)
		{
		case 0:
			Book.Parts.push_back(FPart(Title));
			CurrentPart = &Book.Parts.back();
			break;
		case 1:
			if (CurrentPart)
			{
				CurrentPart->Chapters.push_back(FChapter(Title));
				CurrentChapter = &CurrentPart->Chapters.back();
			}
			break;
		case 2:
			if (CurrentChapter)
			{
				CurrentChapter->Sections.push_back(FSection(Title));
				CurrentSection = &CurrentChapter->Sections.back();
			}
			break;
		case 3:
			if (CurrentSection)
			{
				CurrentSection->ExampleCodes.push_back(FExampleCode(Title));
				//CurrentSection->ExampleCodes.back().DrawFunction = &UTOutputWindow::MyDisplay5_2;
			}
			break;

		}
	}
}

bool ResourceManager::GetNextTitleContext(ETitleType& OutTitleType, std::string& OutTitleContext)
{
	std::string Line{};
	std::string Found{};

	while (std::getline(ContextStream, Line))
	{
		auto Position = Line.find(": ");

		if (Position != std::string::npos)
		{
			size_t Offset = 0;
			OutTitleContext = LeftTrim(Line, Offset);

			if (Offset == 0)
			{
				OutTitleType = ETitleType::TitleType_Part;
			}
			else if (Offset == 1)
			{
				OutTitleType = ETitleType::TitleType_Chapter;
			}
			else if (Offset == 2)
			{
				OutTitleType = ETitleType::TitleType_Section;
			}
			else if (Offset == 3)
			{
				OutTitleType = ETitleType::TitleType_ExampleCode;
			}
			else
			{
				OutTitleType = ETitleType::TitleType_None;
				return false;
			}
			return true;
		}
		else if (Line.find("End") != std::string::npos)
		{
			OutTitleType = ETitleType::TitleType_End;
			return true;
		}
	}

	return false;
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