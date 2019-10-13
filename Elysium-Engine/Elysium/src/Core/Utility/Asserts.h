/**
 * FILENAME		: Asserts.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 12/10/2019
 * Description	: This file will contain custom Assertion functions for usage within 
 *				  this engine their usage is toggled based on the pre-processor declarations.
 */
#pragma once
#include <iostream>

__forceinline bool ElysiumAssertion(const bool exp, const char* desc, const bool breakpoint, const int line, const char* file)
{
	if (exp == 0) return false;
	std::cout << "Error in expression: " << exp << "\n";
	std::cout << "Description: " << desc << "\n";
	std::cout << "Line Number: " << line << "\n";
	std::cout << "File Name: " << file << "\n";
	return breakpoint;
}
	
#ifdef EM_ENABLE_ASSERTS 
	#define	ASSERT(exp, description, breakpoint) \
		if (ElysiumAssertion((int)(exp), description, (int)breakpoint, __LINE__, __FILE__)) { _asm { int 3 } } 
#else 
#define ASSERT(exp, description, breakpoint)
#endif