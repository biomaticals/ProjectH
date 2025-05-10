// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include "UTWindow.h"
#include <vector>

#define REGISTER_DRAW_FUNCTION(Chapter, CodeIndex) \
	{ \
		if (this->DrawFunctions.size() <= Chapter) \
		{ \
			this->DrawFunctions.resize(Chapter + 1); \
		} \
		if (this->DrawFunctions[Chapter].size() <= CodeIndex) \
		{ \
			this->DrawFunctions[Chapter].resize(CodeIndex + 1); \
		} \
		(this->DrawFunctions)[Chapter][CodeIndex] = &UTOutputWindow::MyDisplay_##Chapter##_##CodeIndex; \
	} \

class UTOutputWindow;

struct FExampleCode
{
	FExampleCode();
	FExampleCode(const std::string& InTitle);
	FExampleCode(const std::string& InTitle, void (UTOutputWindow::* InDrawFunction)(), const std::string& InDescription);
	FExampleCode(const FExampleCode& Other);
	~FExampleCode();
	const FExampleCode& operator=(const FExampleCode& Other);
	bool IsValid() const;

	std::string Title;
	void (UTOutputWindow::* DrawFunction)() = nullptr;
	std::string Description;
};

class UTOutputWindow : public UTWindow
{
public:
	UTOutputWindow(const std::string& Title, int Width, int Height);
	virtual ~UTOutputWindow() override;
	void Initialize() override;
	virtual void RenderDrawData() override;

public:
	void SetSelectedExampleCodeData(unsigned int InPart, unsigned int InChapter, unsigned int InSection, unsigned int InCodeIndex);

private:
	void MyDisplay_5_2();

private:
	using DrawFuncPtr = void (UTOutputWindow::*)();
	std::vector<std::vector<DrawFuncPtr>> DrawFunctions;
public:
	FExampleCode OutputExampleCodeData;
};