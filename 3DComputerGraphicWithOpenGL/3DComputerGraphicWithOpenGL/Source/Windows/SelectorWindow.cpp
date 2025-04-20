// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "SelectorWindow.h"
#include "Common.h"
#include <String>
#include <filesystem>
#include <iostream>
#include <istream>
#include <fstream>
#include <format>

FSelectorWindowData::FSelectorWindowData()
	: bDraw(true)
	, CodeDataList()
	, TableOfContentsPath("Resource\\TableOfContents.txt")
{

}

FSelectorWindowData::~FSelectorWindowData()
{

}

void FSelectorWindowData::Draw(bool* bOpen)
{
	if(bOpen == nullptr || *bOpen == false)
		return;

	if (ImGui::CollapsingHeader(FindContext(2, 0, 0, 0).c_str()))
	{
		ImGui::Indent();
		if (ImGui::CollapsingHeader(FindContext(2, 5, 0, 0).c_str()))
		{
			ImGui::Indent();
			if (ImGui::CollapsingHeader(FindContext(2, 5, 3, 0).c_str()))
			{
				ImGui::MenuItem(FindContext(2, 5, 3, 2).c_str(), nullptr);

				
			}
			
			ImGui::Unindent();
		}
		
		ImGui::Unindent();
	}
	

	if (ImGui::CollapsingHeader("Part03 Graphic Pipeline"))
	{

	}
};

const std::string FSelectorWindowData::FindContext(unsigned int Part, unsigned int Chapter, unsigned int Section, unsigned int SampleCode)
{
	std::ifstream Stream(TableOfContentsPath, std::ios::in);
	std::string Line{};
	std::string Found{};
	
	std::string Keyword = std::format("Part {:02}", Part);
	if (Part != 0)
	{
		while (std::getline(Stream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::string::npos)
			{
				Found = std::string(Line).substr(Position + Keyword.size() + 3 /*" : "*/);
				break;
			}
		}
	}

	if (Chapter != 0)
	{
		Keyword = std::format("Chapter {:02}", Chapter);
		while (std::getline(Stream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::string::npos)
			{
				Found = std::string(Line).substr(Position + Keyword.size() + 3 /*" : "*/);
				break;
			}
		}
	}

	if (Section != 0)
	{
		Keyword = std::format("Section {:02}", Section);
		while (std::getline(Stream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::string::npos)
			{
				Found = std::string(Line).substr(Position + Keyword.size() + 3 /*" : "*/);
				break;
			}
		}
	}

	if (SampleCode != 0)
	{
		Keyword = std::format("Code {}-{}", Chapter, SampleCode);
		while (std::getline(Stream, Line))
		{
			if (auto Position = Line.find(Keyword); Position != std::string::npos)
			{
				Found = std::string(Line).substr(Position + Keyword.size() + 3 /*" : "*/);
				break;
			}
		}
	}

	return Found;
}