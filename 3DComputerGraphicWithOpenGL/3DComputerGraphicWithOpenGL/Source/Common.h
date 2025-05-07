// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include <string>
#include <fstream>
#include <filesystem>

enum ETitleType
{
	TitleType_None = 0,
	TitleType_Part,
	TitleType_Chapter,
	TitleType_Section,
	TitleType_ExampleCode,
	TitleType_End,
};

struct FExampleCode
{
	FExampleCode();
	FExampleCode(const std::string& InTitle, void (*InDrawFunction)(), const std::string& InDescription);
	FExampleCode(const FExampleCode& Other);
	~FExampleCode();
	const FExampleCode& operator=(const FExampleCode& Other);

    std::string Title;
	void (*DrawFunction)();
	std::string Description;
};

struct FSection
{
	FSection();
	FSection(const std::string& InTitle);
    const FSection& operator=(const FSection& Other);

	std::string Title;
	std::vector<FExampleCode> ExampleCodes;
};

struct FChapter
{
	FChapter();
	FChapter(const std::string& InTitle);
	const FChapter& operator=(const FChapter& Other);

	std::string Title;
	std::vector<FSection> Sections;
};

struct FPart
{
	FPart();
	FPart(const std::string& InTitle);
	const FPart& operator=(const FPart& Other);

	std::string Title;
	std::vector<FChapter> Chapters;
};

struct FBook
{
	FBook();

	std::vector<FPart> Parts;
};

extern std::string ReadFileToString(const std::filesystem::path& FilePath);
extern std::string LeftTrim(const std::string& Str, size_t& OutOffset);
extern std::string RightTrim(const std::string& Str, size_t& OutOffset);