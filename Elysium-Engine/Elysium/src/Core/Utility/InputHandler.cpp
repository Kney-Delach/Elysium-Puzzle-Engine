/**
 * FILENAME		: InputHandler.cpp
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 14/10/2019
 * Description	: This file contains the method implementations for the input handler,
 *				  the methods here were abstracted from the menu for clarity and
				  potential other uses in the system.
 */
#include "empch.h"
#include "Core/Utility/InputHandler.h"
//todo: Insert pre-processor defines for cout to be able to implement unit tests for this.

namespace Elysium
{
	namespace Utility
	{
		bool InputHandler::HandleInput(const char* requestMessage) const
		{
			while (true)
			{
				std::string inputString = "";
				char inputChar = { 0 };
				std::cout << requestMessage;	//todo: Insert pre-processor defines here for unit testing
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

		const int InputHandler::HandleInput(const char* requestMessage, int rangeMax, int rangeMin) const //todo: Fix scenario where entering 2.3, system accepts the '2'. 
		{
			while (true)
			{
				int inputNumber = 0;
				std::string inputString = "";
				std::cout << requestMessage;	//todo: Insert pre-processor defines here for unit testing
				std::getline(std::cin, inputString);
				std::stringstream myStream(inputString);
				if (myStream >> inputNumber && !(inputNumber > rangeMax || inputNumber <= rangeMin))	return inputNumber;
				std::cout << "Invalid Input, enter a number between " << rangeMin + 1 << " and " << rangeMax << " (inclusive): \n";
			}
		}
	}
}