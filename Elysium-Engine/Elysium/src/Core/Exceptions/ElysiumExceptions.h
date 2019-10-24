/**
 * FILENAME		: ElysiumExceptions.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 24/10/2019
 * Description	: This file contains the header files of all the exceptions in this engine,
 *                it also contains a useful macro to display any exception information.
 */
#pragma once
#include "StackOutOfBoundsAccessException.h"

namespace Elysium
{
	namespace Exceptions
	{
		#define LOG_EXCEPTION(vse) \
		std::cout << vse.what() << "\n"; \
		std::cout << "Function	: " << vse.GetFunctionName() << "\n";\
		std::cout << "File		: " << vse.GetFile() << "\n";\
		std::cout << "Line		: " << vse.GetLine() << "\n";
	}
}