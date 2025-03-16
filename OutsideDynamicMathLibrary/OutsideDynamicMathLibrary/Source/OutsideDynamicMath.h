// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#ifdef OUTSIDEDYNAMICMATHLIBRARY_EXPORTS
#define OUTSIDEDYNAMICMATHLIBRARY_API __declspec(dllexport)
#else
#define OUTSIDEDYNAMICMATHLIBRARY_API __declspec(dllimport)
#endif

namespace OutsideDynamicMath
{
	extern "C" OUTSIDEDYNAMICMATHLIBRARY_API double Add(double a, double b);

	extern "C" OUTSIDEDYNAMICMATHLIBRARY_API double Subtract(double a, double b);

	extern "C" OUTSIDEDYNAMICMATHLIBRARY_API double Multiply(double a, double b);

	extern "C" OUTSIDEDYNAMICMATHLIBRARY_API double Divide(double a, double b);
}