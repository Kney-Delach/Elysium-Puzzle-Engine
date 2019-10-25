/**
 * FILENAME		: StackOutOfBoundsAccessException.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 24/10/2019
 * Description	: This file contains the implementation for the stack out of bounds exception, which 
 *                occurs when attempting to access a part of the stack which is empty. 
 */
#pragma once
#include <exception>

namespace Elysium
{
	namespace Exceptions
	{
		class StackOutOfBoundsAccessException : public std::exception
		{
		public:
			StackOutOfBoundsAccessException(const char* msg, const char* file, int line, const char* func)
				: std::exception(msg), m_File(file), m_Line(line), m_Func(func)
			{
			}
			const char* what() const throw () override
			{
				return "[StackOutOfBoundsAccessException]: You are making an out of range call to the stack: ";
			}
		public:
			__forceinline const char* GetFile() const
			{
				return m_File;
			}
			__forceinline int GetLine() const
			{
				return m_Line;
			}
			__forceinline const char* GetFunctionName() const
			{
				return m_Func;
			}
		protected:
			const char* m_File;
			int m_Line;
			const char* m_Func;
		};
	}
}