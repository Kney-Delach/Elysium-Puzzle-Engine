/**
 * FILENAME		: Menu.cpp
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 12/10/2019
 * Description	: This file contains the class declaration for the console interface to interact with the user, 
 *				  it is also the entry point for the puzzle processing.
 */
#include "empch.h"
#include "Core/Application/Menu.h"
#include "Core/Model/Puzzle/Puzzle.h"
#include "Core/Utility/Random.h"
#include "Core/Serialization/Serializer.h"
#include "Core/Model/DataStructures/Stack.h"
#include "Core/Utility/InputHandler.h"

namespace Elysium
{
	using namespace Model;
	using namespace Utility;
	using PuzzleStacker = Stack<Puzzle>;
	using PuzzleSerializer = Serialize::Serializer<PuzzleStacker>;

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
|  [3]: Read in a configuration file and save the solution file   |
|                                                                 |
+-----------------------------------------------------------------+
			)";

#pragma endregion STATIC_TEXT

		void Menu::RunOptionsMenu() const
		{
			std::cout << g_Banner << "\n" << g_Menu << "\n";
			bool result = OptionsHandler(MENU);
			ASSERT(!result, "[Elysium::Menu::RunOptionsMenu]: Undefined behaviour reached!", true);
		}

		bool Menu::RunQuitMenu() const
		{
			return OptionsHandler(QUIT);
		}

		bool Menu::OptionsHandler(MenuOptions option) const //todo: Remove bool return? 
		{
			if(option == MENU)		option = static_cast<MenuOptions>(InputHandler::HandleInput("-> ",3, 0));
			if(option == MANUAL)	return HandleManualConfig();
			if(option == AUTO)		return HandleAutoConfig();
			if(option == READ)		return HandleReadConfig();
			if(option == QUIT)		return HandleQuit();
			return false;
		}

		bool Menu::HandleManualConfig() const	//todo: Implement user choice to process configurations or not.
		{
			const int puzzleSize = InputHandler::HandleInput("Enter the dimension value of the configuration:\n-> ", 10, 3);
			PuzzleStacker puzzleStack (50);
			for (;;)
			{
				Puzzle* puzzle = puzzleStack.Push(Puzzle(puzzleSize));
				ASSERT(puzzle, "[Elysium::Menu::HandleManualConfig]: Puzzle pointer returned from stack shouldn't be a null pointer.",true)
				for (int i = 0; i < (puzzleSize*puzzleSize)-1; i++)
				{
					for(;;)
					{
						if (puzzle->InsertValue(InputHandler::HandleInput("Enter a value to add to the configuration:\n-> ",20, 0)))
							break;
						std::cout << "That value exists already! ";
					}
				}
				puzzle->InsertEmptyBlock();
				if (!InputHandler::HandleInput("That configuration has been saved, do you want to configure another puzzle? Enter [Y/N]:\n-> "))
					break;
			}
			PuzzleSerializer::Serialize(puzzleStack);
			return true;
		}

		bool Menu::HandleAutoConfig() const	//todo: Implement user choice to process configurations or not. (Verify this)
		{
			const int puzzleSize = InputHandler::HandleInput("Enter the dimension value of the configurations:\n-> ", 10, 3);
			const int elementCount = puzzleSize * puzzleSize + puzzleSize;
			const int puzzleCount = InputHandler::HandleInput("How many configurations would you like to generate? Range -> [1-20000]:\n-> ", 20000, 0);
			PuzzleStacker puzzleStack(puzzleCount);
			int* unsortedArray = new int[elementCount];
			for (int i = 0; i < elementCount; ++i)
				unsortedArray[i] = i + 1;
			for (int i = 0; i < puzzleCount; i++)
			{
				Random::Randomize(unsortedArray, elementCount);
				puzzleStack.Push(Puzzle(puzzleSize, unsortedArray));
			}
			delete[] unsortedArray;
			PuzzleSerializer::Serialize(puzzleStack); 
			return true;
		}

		bool Menu::HandleReadConfig() const	//todo: Implement and insert processing call.
		{
			PuzzleStacker puzzleStack(1);
			PuzzleSerializer::Deserialize(puzzleStack);
			PuzzleSerializer::Serialize(puzzleStack);
			return true;
		}

		bool Menu::HandleQuit() const
		{
			return InputHandler::HandleInput("Do  you want to EXIT the application? Enter [Y/N]:\n-> ");
		}
	}
}