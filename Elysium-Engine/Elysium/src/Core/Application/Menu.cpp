/**
 * FILENAME		: Menu.cpp
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 12/10/2019
 * Description	: This file contains the class declaration for the console interface to interact with the user, 
 *				  it is also the entry point for the puzzle processing, as it is requires user input.
 */
#include "empch.h"
#include "Core/Application/Menu.h"
#include "Core/Model/Puzzle/Puzzle.h"
#include "Core/Model/Puzzle/PuzzleProcessor.h"
//todo: Research how to test these, if not unit testing then use peer-to-peer tests.
//todo: Research how to implement multiple number read from 1 line.
//todo: implement pseudo-random configurations
//todo: Abstract this class out.

namespace Elysium
{
	namespace Application
	{

#pragma region STATIC_TEXT
		static const char* g_Banner = R"(
############################################################################################################
##                             ______  _   __     __ _____  _____  _    _  __  __                         ##
##                            |  ____|| |  \ \   / // ____||_   _|| |  | ||  \/  |                        ##
##                            | |__   | |   \ \_/ /| (___    | |  | |  | || \  / |                        ##
##                            |  __|  | |    \   /  \___ \   | |  | |  | || |\/| |                        ##
##                            | |____ | |____ | |   ____) | _| |_ | |__| || |  | |                        ##
##                            |______||______||_|  |_____/ |_____| \____/ |_|  |_|                        ##
##   _____   _    _  ______ ______ _       ______           ______  _   _   _____  _____  _   _  ______   ##
##  |  __ \ | |  | ||___  /|___  /| |     |  ____|         |  ____|| \ | | / ____||_   _|| \ | ||  ____|  ##
##  | |__) || |  | |   / /    / / | |     | |__            | |__   |  \| || |  __   | |  |  \| || |__     ##
##  |  ___/ | |  | |  / /    / /  | |     |  __|           |  __|  | . ` || | |_ |  | |  | . ` ||  __|    ##
##  | |     | |__| | / /__  / /__ | |____ | |____          | |____ | |\  || |__| | _| |_ | |\  || |____   ##
##  |_|      \____/ /_____|/_____||______||______|         |______||_| \_| \_____||_____||_| \_||______|  ##
##                                                                                                        ##
############################################################################################################
			)";

		static const char* g_Menu = R"(
+-----------------------------------------------------------------+
|                                                                 |
|  Enter a number from the menu below to select that option       |
|                                                                 |
+-----------------------------------------------------------------+
|                                                                 |
|  [1]: Manually Configure 1+ puzzles                             |
|                                                                 |
|  [2]: Pseudo-Randomly generate puzzle 1+ puzzle configurations  |
|                                                                 |
+-----------------------------------------------------------------+
			)";
#pragma endregion STATIC_TEXT

		void Menu::RunOptionsMenu()
		{
			std::cout << g_Banner << "\n" << g_Menu << "\n";
			bool result = InputHandler(MENU);
			ASSERT(!result, "[Elysium::Menu::RunOptionsMenu]: Undefined behaviour reached!", true);
		}

		bool Menu::RunExitMenu() const
		{
			return InputHandler(EXIT);
		}

		bool Menu::InputHandler(Options option) const
		{
			if(option == MENU)		option = (Options) HandleNumberInput(2,0);
			if(option == MANUAL)	return HandleManualConfig();
			if(option == AUTO)		return HandleAutoConfig();
			if(option == EXIT)		return HandleExit();
			return false;
		}

		const int Menu::HandleNumberInput(int rangeMax, int rangeMin) const
		{
			while (true) 
			{
				int inputNumber = 0;
				std::string inputString = "";
				std::getline(std::cin, inputString);
				std::stringstream myStream(inputString);
				if (myStream >> inputNumber && !(inputNumber > rangeMax || inputNumber <= rangeMin))	return inputNumber;
				std::cout << "Invalid Input, enter a number between " << rangeMin+1 << " and " << rangeMax << " (inclusive): ";
			}
		}

		bool Menu::HandleExit() const
		{
			return HandleBinaryChoice("Do  you want to EXIT the application? Enter [Y/N]: ");
		}

		bool Menu::HandleBinaryChoice(const char* message) const
		{
			while (true) 
			{
				std::string inputString = "";
				char inputChar = { 0 };
				std::cout << message;
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

		bool Menu::HandleManualConfig() const
		{
			Model::PuzzleProcessor<Model::Puzzle<unsigned, 4>> pp(50); //todo: Implement dynamic capacity integration.
			while (true)
			{
				Model::Puzzle<unsigned, 4>* puzzle = pp.InsertPuzzle(Model::Puzzle<unsigned, 4>());
				if (!(puzzle == nullptr))
				{
					std::cout << "Enter value to add to the configuration:\n";
					for (int i = 0; i < 15; i++)
					{
						for(;;)
						{
							if (puzzle->InsertValue(HandleNumberInput(20, 0))) break;
							std::cout << "That number already exists in the configuration, try entering a different one:\n";
						}
					}
					puzzle->InsertEmptyBlock();
					if (!HandleBinaryChoice("Puzzle has been completed and saved, do you want to configure another puzzle? Enter [Y/N]: "))	break;
				}
				else
				{
					std::cout << "Unable to insert another puzzle as stack capacity is full!\n";
					break;
				}
			}
			std::cout << pp << "\n"; //todo: Implement calls to further process functionality here.
			return true;
		}

		bool Menu::HandleAutoConfig() const
		{
			return true;
		}
	}
}
