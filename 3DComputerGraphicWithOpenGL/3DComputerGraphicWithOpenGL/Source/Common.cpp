// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "Common.h"

ExampleCode::ExampleCode()
	: Title("")
	, DrawFunction(nullptr)
	, Description("")
{
}

const ExampleCode& ExampleCode::operator=(const ExampleCode& Other)
{
	if (this != &Other)
	{
		Title = Other.Title;
		DrawFunction = Other.DrawFunction;
		Description = Other.Description;
	}
	return *this;
}

Section::Section()
	: Title("")
{
}

const Section& Section::operator=(const Section& Other)
{
	if (this != &Other)
	{
		Title = Other.Title;
		ExampleCodes = Other.ExampleCodes;
	}
	return *this;
}

Chapter::Chapter()
	: Title("")
{
}

const Chapter& Chapter::operator=(const Chapter& Other)
{
	if (this != &Other)
	{
		Title = Other.Title;
		Sections = Other.Sections;
	}
	return *this;
}

Part::Part()
	: Title("")
{
}

const Part& Part::operator=(const Part& Other)
{
	if (this != &Other)
	{
		Title = Other.Title;
		Chapters = Other.Chapters;
	}
	return *this;
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
	return (FirstNonSpace == std::string::npos) ? "" : Str.substr(FirstNonSpace);
}

std::string RightTrim(const std::string& Str, size_t& OutOffset)
{
	size_t LastNonSpace = Str.find_last_not_of(" \t\n\r");
	return (LastNonSpace == std::string::npos) ? "" : Str.substr(0, LastNonSpace + 1);
}