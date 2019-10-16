/**
 * FILENAME		: InputHandler.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 14/10/2019
 * Description	: This file contains the class declaration for the input handler, 
 *				  the methods here were abstracted from the menu for clarity and 
				  potential other uses in the system.
 */
#pragma once
#include "Core/Utility/Asserts.h"
#include <string>

namespace Elysium
{
	namespace Utility
	{
		class InputHandler
		{
		public:
			~InputHandler() = default;
			InputHandler(const InputHandler&) = delete;
			InputHandler(InputHandler&&) = delete;
			InputHandler& operator=(const InputHandler&) = delete;
			InputHandler& operator=(InputHandler&&) = delete;
			static bool HandleInput(const char* requestMessage);
			static void HandleInput(const char* requestMessage, std::string& inputString);
			static int HandleInput(const char* requestMessage, int rangeMax, int rangeMin);
		private:
			InputHandler() = default;
		};
	}
}