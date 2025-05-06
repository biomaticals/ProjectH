// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include <string>
#include <fstream>
#include <filesystem>

struct FExampleCodeData
{
    FExampleCodeData()
    : Part(0)
    , Chapter(0)
    , Section(0)
    , CodeIndex(0)
    , Name("")
    , Codes(0)
    , Description("")
    {

    }

    FExampleCodeData(unsigned int InPart, unsigned int InChapter, unsigned int InSection, unsigned int InCodeIndex)
        : Part(InPart)
        , Chapter(InChapter)
        , Section(InSection)
        , CodeIndex(InCodeIndex)
        , Name("")
        , Codes(0)
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
    const char* Name;
    const char* Codes;
    const char* Description;
};

extern std::string ReadFileToString(const std::filesystem::path& FilePath);
extern std::string LeftTrim(const std::string& Str);
extern std::string RightTrim(const std::string& Str);