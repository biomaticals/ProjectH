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
	, ExampleCodeDataList()
	, TableOfContentsPath("Resource\\TableOfContents.txt")
{

}

FSelectorWindowData::~FSelectorWindowData()
{

}

auto FSelectorWindowData::UpdateSelectedExample(unsigned int Part, unsigned int Chapter, unsigned int Section, unsigned int CodeIndex)
{
	if(SelectedExampleCodeData.Part == Part && SelectedExampleCodeData.Chapter == Chapter && SelectedExampleCodeData.Section == Section && SelectedExampleCodeData.CodeIndex == CodeIndex)
		return;

	FExampleCodeData Target = FExampleCodeData(Part, Chapter, Section, CodeIndex);
	auto Result = std::find(ExampleCodeDataList.begin(), ExampleCodeDataList.end(), Target);
	SelectedExampleCodeData = Result._Ptr->_Myval;
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
				ImGui::Indent();
				if (ImGui::MenuItem(FindContext(2, 5, 3, 2).c_str(), nullptr))
				{
					UpdateSelectedExample(2, 5, 3, 2);
				}
				ImGui::Unindent();
			}
			ImGui::Unindent();
		}
		ImGui::Unindent();
	}

	if (ImGui::CollapsingHeader("Part03 Graphic Pipeline"))
	{

	}
};

const FExampleCodeData FSelectorWindowData::GetExampleCodeData() const
{
	return SelectedExampleCodeData;
}

const std::string FSelectorWindowData::FindContext(unsigned int Part, unsigned int Chapter, unsigned int Section, unsigned int CodeIndex)
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
				Found = std::string(Line).substr(Position);
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
				Found = std::string(Line).substr(Position);
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
				Found = std::string(Line).substr(Position);
				break;
			}
		}
	}

	if (CodeIndex != 0)
	{
		Keyword = std::format("Code {}-{}", Chapter, CodeIndex);
		while (std::getline(Stream, Line))
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