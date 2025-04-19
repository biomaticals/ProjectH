#pragma once

#include <iostream>

struct FWindowData
{
    bool ShowIntroduction = true;
};

struct FSampleCodeData
{
    FSampleCodeData()
    : Part(0)
    , Chapter(0)
    , Section(0)
    , Name("")
    , SampleCode("")
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
    GLFWimage Output;
};