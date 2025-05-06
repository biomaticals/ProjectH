// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include <string>
#include <fstream>
#include <filesystem>

enum TitleType
{
	TitleType_None = 0,
	TitleType_Part,
	TitleType_Chapter,
	TitleType_Section,
	TitleType_ExampleCode,
};

struct ExampleCode
{
	ExampleCode();
	const ExampleCode& operator=(const ExampleCode& Other);

    std::string Title;
	void (*DrawFunction)();
	std::string Description;
};

struct Section
{
	Section();
    const Section& operator=(const Section& Other);

	std::string Title;
	std::vector<ExampleCode> ExampleCodes;
};

struct Chapter
{
	Chapter();
	const Chapter& operator=(const Chapter& Other);

	std::string Title;
	std::vector<Section> Sections;
};

struct Part
{
	Part();
	const Part& operator=(const Part& Other);

	std::string Title;
	std::vector<Chapter> Chapters;
};

struct FExampleCodeData
{
    FExampleCodeData()
    : Part(0)
    , Chapter(0)
    , Section(0)
    , CodeIndex(0)
    , Title("")
    , DrawFunction(0)
    , Description("")
    {

    }

    FExampleCodeData(unsigned int InPart, unsigned int InChapter, unsigned int InSection, unsigned int InCodeIndex)
        : Part(InPart)
        , Chapter(InChapter)
        , Section(InSection)
        , CodeIndex(InCodeIndex)
        , Title("")
        , DrawFunction(0)
        , Description("")
    {

     }

    ~FExampleCodeData()
    {

    }

    bool operator==(const FExampleCodeData& Other)
    {
        return Part == Other.Part && Chapter == Other.Chapter && Section == Other.Section && CodeIndex == Other.CodeIndex;
    }

    unsigned int Part;
    unsigned int Chapter;
    unsigned int Section;
    unsigned int CodeIndex;
    const char* Title;
    void  (*DrawFunction)();
    const char* Description;
};

extern std::string ReadFileToString(const std::filesystem::path& FilePath);
extern std::string LeftTrim(const std::string& Str, size_t& OutOffset);
extern std::string RightTrim(const std::string& Str, size_t& OutOffset);