// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "SelectorWindow.h"
#include "Common.h"

FSelectorWindowData::FSelectorWindowData()
	: bDraw(true)
	, ExampleCodeDataList()
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

const bool FSelectorWindowData::HasSelectedExampleChanged() const
{
	return bSelectedExampleChanged;
}