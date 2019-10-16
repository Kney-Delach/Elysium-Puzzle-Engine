/**
 * FILENAME		: InputHandler.cpp
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 14/10/2019
 * Description	: This file contains the method implementations for the input handler,
 *				  the methods here are used in multiple parts of the system, thus abstracted
 *				  as a utility.
 */
#include "empch.h"
#include "Core/Utility/InputHandler.h"
//todo: Insert pre-processor defines for unit testing this.

namespace Elysium
{
	namespace Utility
	{
		bool InputHandler::HandleInput(const char* requestMessage)
		{
			for(;;)
			{
				std::string inputString = "";
				char inputChar = { 0 };
				std::cout << requestMessage;
				std::getline(std::cin, inputString);
				if (inputString.length() == 1)
				{
					inputChar = inputString[0];
					if (inputChar == 'y' || inputChar == 'Y')	return true;
					if (inputChar == 'n' || inputChar == 'N')	return false;
				}
				std::cout << "Invalid input! - ";
			}
		}

		void InputHandler::HandleInput(const char* requestMessage, std::string& inputString)
		{
			for (;;)
			{
				std::cout << requestMessage;
				std::getline(std::cin, inputString);
				if (inputString.length() > 0)	
					break;
				std::cout << "Invalid input! - ";
			}
		}

		int InputHandler::HandleInput(const char* requestMessage, int rangeMax, int rangeMin)
		{
			for(;;)
			{
				int inputNumber = 0;
				std::string inputString = "";
				std::cout << requestMessage;
				std::getline(std::cin, inputString);
				std::stringstream myStream(inputString);
				if (myStream >> inputNumber && !(inputNumber > rangeMax || inputNumber <= rangeMin))	
					return inputNumber;
				std::cout << "Invalid Input, enter a number between " << rangeMin + 1 << " and " << rangeMax << " (inclusive): \n";
			}
		}
	}
}