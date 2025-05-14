// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#ifdef INSIDEDYNAMICMATHLIBRARY_EXPORTS
#define INSIDEDYNAMICMATHLIBRARY_API __declspec(dllexport)
#else
#define INSIDEDYNAMICMATHLIBRARY_API __declspec(dllimport)
#endif

namespace InsideDynamicMath
{
	extern "C" INSIDEDYNAMICMATHLIBRARY_API double Add(double a, double b);

	extern "C" INSIDEDYNAMICMATHLIBRARY_API double Subtract(double a, double b);

	extern "C" INSIDEDYNAMICMATHLIBRARY_API double Multiply(double a, double b);

	extern "C" INSIDEDYNAMICMATHLIBRARY_API double Divide(double a, double b);
}