// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include <string>
#include <fstream>
#include <filesystem>

struct FWindowData
{
    bool bShowIntroduction = true;
};

struct FSampleCodeData
{
    FSampleCodeData()
    : Part(0)
    , Chapter(0)
    , Section(0)
    , Name("")
    , SampleCode("")
    , Description("")
    {

    }

    ~FSampleCodeData()
    {

    }

    unsigned int Part;
    unsigned int Chapter;
    unsigned int Section;
    const char* Name;
    const char* SampleCode;
    const char* Description;
};

static std::string ReadFileToString(const std::filesystem::path& FilePath)
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