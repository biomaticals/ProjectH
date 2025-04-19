// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include <list>
#include "Common.h"

static void DrawSelectorWindow()
{
	static std::list<FSampleCodeData> SampleCodeDataList;

	if (ImGui::CollapsingHeader("Part02 Introduction to OpenGL"))
	{
		ImGui::Indent();
		if (ImGui::CollapsingHeader("Chapter05 Basic OpenGL Tool"))
		{
			ImGui::Indent();
			if (ImGui::CollapsingHeader("Section 03 Sample OpenGL Program"))
			{
				ImGui::MenuItem("Code 5-2", nullptr);

				
			}
			
			ImGui::Unindent();
		}
		
		ImGui::Unindent();
	}
	

	if (ImGui::CollapsingHeader("Part03 Graphic Pipeline"))
	{

	}

};