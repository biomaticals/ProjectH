// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Common.h"
#include "Windows/UTOutputWindow.h"

FSection::FSection()
	: Title("")
{
}

FSection::FSection(const std::string& InTitle)
	: Title(InTitle)
{
}

const FSection& FSection::operator=(const FSection& Other)
{
	if (this != &Other)
	{
		Title = Other.Title;
		ExampleCodes = Other.ExampleCodes;
	}
	return *this;
}

bool FSection::IsValid() const
{
	return !Title.empty();
}

FChapter::FChapter()
	: Title("")
{
}

FChapter::FChapter(const std::string& InTitle)
	: Title(InTitle)
{
}

const FChapter& FChapter::operator=(const FChapter& Other)
{
	if (this != &Other)
	{
		Title = Other.Title;
		Sections = Other.Sections;
	}
	return *this;
}

bool FChapter::IsValid() const
{
	return !Title.empty();
}

FPart::FPart()
	: Title("")
{
}

FPart::FPart(const std::string& InTitle)
	: Title(InTitle)
{
}

const FPart& FPart::operator=(const FPart& Other)
{
	if (this != &Other)
	{
		Title = Other.Title;
		Chapters = Other.Chapters;
	}
	return *this;
}

bool FPart::IsValid() const
{
	return !Title.empty();
}

FBook::FBook()
{
}

std::string ReadFileToString(const std::filesystem::path& FilePath)
{
    std::ifstream Stream(FilePath, std::ios::in |std::ios::binary);
    if (!Stream)
    {
        std::cerr << std::format("failed to open {}\n", FilePath.string());
        return {};
    }

    std::string Contents((std::istreambuf_iterator<char>(Stream)), std::istreambuf_iterator<char>());
    return Contents;
}

std::string LeftTrim(const std::string& Str, size_t& OutOffset)
{
	size_t FirstNonSpace = Str.find_first_not_of(" \t\n\r");
	OutOffset = FirstNonSpace;
	return (FirstNonSpace == std::string::npos) ? "" : Str.substr(FirstNonSpace);
}

std::string RightTrim(const std::string& Str, size_t& OutOffset)
{
	size_t LastNonSpace = Str.find_last_not_of(" \t\n\r");
	OutOffset = LastNonSpace;
	return (LastNonSpace == std::string::npos) ? "" : Str.substr(0, LastNonSpace + 1);
}