// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "IntroductionWindow.h"
#include "3DComputerGraphicWithOpenGL.h"

const char* FIntroductionWindowData::WindowName = "Introduction";

void FIntroductionWindowData::Draw(bool* bOpen)
{
	const ImGuiViewport* MainViewport = ImGui::GetMainViewport();

	ImGuiWindowFlags WindowFlags{};
	WindowFlags |= ImGuiWindowFlags_NoResize;
	WindowFlags |= ImGuiWindowFlags_UnsavedDocument;

	ImGui::SetNextWindowPos(ImVec2(MainViewport->WorkSize.x / 2.f - 400.f, MainViewport->WorkSize.y / 2.f - 250.f ), ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(ImVec2(800, 500.f), ImGuiCond_Appearing);
	if (ImGui::Begin(WindowName, bOpen, WindowFlags))
	{
		ImGui::SeparatorText("3D CG With OpenGl by biomatic");
		ImGui::Text("This project was initiated to learn and practice the OpenGL API.");
		ImGui::Text("The content is adapted from a book \"3D Computer Graphics with OpenGL\".");
		ImGui::Text("Through this program, you can view and run the code examples from each part and chapter.");
		ImGui::Text("From \"Selector window\", choose part, chapter and title to proceed.");
		ImGui::Text("And then, \"Main window\" shows the codes, \"Sub window\" outputs the results.");
		ImGui::NewLine();
		ImGui::Text("To learn more about the book, please follow this link.");
		ImGui::TextLinkOpenURL("https://www.hanbit.co.kr/store/books/look.php?p_code=B1779572378");
		ImGui::NewLine();
		ImGui::Text("To access the open source for this program, please follow this link.");
		ImGui::TextLinkOpenURL("https://github.com/biomaticals/3DComputerGraphicWithOpenGL");
		ImGui::NewLine();
		ImGui::SeparatorText("biomatic");
		ImGui::Text("I am a game client programmer from Korea with 4 years of experience.");
		ImGui::NewLine();

		ImGui::Text("To visit my technical blog, please follow this link.");
		ImGui::Text("Unfortunately, the technical blog does not support English.");
		ImGui::NewLine();
		ImGui::TextLinkOpenURL("https://biomaticals.notion.site/GUI-1daed2b75184805fa19cfd4eb4be638f?pvs=4");
		ImGui::NewLine();
		ImGui::Text("To contact, please use the phone number or email address below.");
		ImGui::Text("Phone Number : +82 10 3902 8624 (Republic of Korea)");
		ImGui::Text("E-mail : biomaticals@naver.com");
		ImGui::NewLine();

		if (ImGui::Button("Close", ImVec2(-FLT_MIN, 0.f)))
		{
			*bOpen = false;
		}

		ImGui::End();
		return;
	}

	ImGui::End();
}