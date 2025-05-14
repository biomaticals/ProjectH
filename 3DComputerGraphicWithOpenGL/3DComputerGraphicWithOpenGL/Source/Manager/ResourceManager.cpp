// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "ResourceManager.h"
#include "Windows/UTOutputWindow.h"
#include "format"

ResourceManager* ResourceManager::Instance = nullptr;

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
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
bool ResourceManager::LoadTitleContext()
{
	Book.Parts.clear();

	std::ifstream ContextStream(TableOfContentsPath, std::ios::in);

	unsigned int PartIndex = 0;
	unsigned int ChapterIndex = 0;
	unsigned int SectionIndex = 0;
	unsigned int CodeIndex = 0;
	size_t StartPosition = 0;
	size_t EndPosition = 0;
	std::string NumberStr{};
	std::string Line{};
	std::string Prefix{};
	std::string Delimeter{ ": " };
	while (std::getline(ContextStream, Line))
	{
		if (PartIndex == 0)
		{
			Prefix = "Part ";
			Delimeter = ": ";
			StartPosition = Line.find(Prefix);
			if (StartPosition == std::string::npos)
				continue;
			std::string PartTitle = Line.substr(StartPosition);

			StartPosition += Prefix.length();
			EndPosition = Line.find(Delimeter, StartPosition);
			if (EndPosition == std::string::npos)
				break;
			
			NumberStr = Line.substr(StartPosition, EndPosition - StartPosition);
			PartIndex = std::stoi(NumberStr);
			if (Book.Parts.size() <= PartIndex)
			{
				Book.Parts.resize(PartIndex + 1);
			}
			
			Book.Parts[PartIndex] = FPart(PartTitle);
		}
		else if (ChapterIndex == 0)
		{
			Prefix = "Chapter ";
			Delimeter = ": ";
			StartPosition = Line.find(Prefix);
			if (StartPosition == std::string::npos)
				break;
			std::string ChapterTitle = Line.substr(StartPosition);
			
			StartPosition += Prefix.length();
			EndPosition = Line.find(Delimeter, StartPosition);
			if (EndPosition == std::string::npos)
				break;

			NumberStr = Line.substr(StartPosition, EndPosition - StartPosition);
			ChapterIndex = std::stoi(NumberStr);
			if (Book.Parts[PartIndex].Chapters.size() <= ChapterIndex)
			{
				Book.Parts[PartIndex].Chapters.resize(ChapterIndex + 1);
			}

			Book.Parts[PartIndex].Chapters[ChapterIndex] = FChapter(ChapterTitle);
		}
		else if (SectionIndex == 0)
		{
			Prefix = "Section ";
			Delimeter = ": ";
			StartPosition = Line.find(Prefix);
			if (StartPosition == std::string::npos)
				break;
			std::string SectionTitle = Line.substr(StartPosition);

			StartPosition += Prefix.length();
			EndPosition = Line.find(Delimeter, StartPosition);
			if (EndPosition == std::string::npos)
				break;

			NumberStr = Line.substr(StartPosition, EndPosition - StartPosition);
			SectionIndex = std::stoi(NumberStr);
			
			if (Book.Parts[PartIndex].Chapters[ChapterIndex].Sections.size() <= SectionIndex)
			{
				Book.Parts[PartIndex].Chapters[ChapterIndex].Sections.resize(SectionIndex + 1);
			}

			Book.Parts[PartIndex].Chapters[ChapterIndex].Sections[SectionIndex] = FSection(SectionTitle);
		}
		else
		{
			Prefix = "Code ";
			Delimeter = ": ";
			StartPosition = Line.find(Prefix);
			if (StartPosition == std::string::npos)
				break;
			std::string CodeTitle = Line.substr(StartPosition);

			StartPosition += Prefix.length();
			EndPosition = Line.find(Delimeter, StartPosition);
			if (EndPosition == std::string::npos)
				break;

			std::string IntermediateStr = Line.substr(StartPosition, EndPosition - StartPosition);
			StartPosition = Line.find("-");
			if (StartPosition == std::string::npos)
				break;

			StartPosition += 1;
			NumberStr = Line.substr(StartPosition, EndPosition - StartPosition);
			CodeIndex = std::stoi(NumberStr);
			
			if (Book.Parts[PartIndex].Chapters[ChapterIndex].Sections[SectionIndex].ExampleCodes.size() <= CodeIndex)
			{
				Book.Parts[PartIndex].Chapters[ChapterIndex].Sections[SectionIndex].ExampleCodes.resize(CodeIndex + 1);
			}

			Book.Parts[PartIndex].Chapters[ChapterIndex].Sections[SectionIndex].ExampleCodes[CodeIndex] = FExampleCode(CodeTitle);   
		}
	}
	ContextStream.close();

	if (Book.Parts.size() > 0)
		return true;

	return false;
}

FBook ResourceManager::GetBook() const
{
	return Book;
}

const std::string ResourceManager::FindTitleContext(unsigned int InPart, unsigned int InChapter,unsigned int InSection, unsigned int InCodeIndex)
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