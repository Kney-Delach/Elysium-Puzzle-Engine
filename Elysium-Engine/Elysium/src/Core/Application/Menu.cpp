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
#include "Core/Utility/Random.h"
#include "Core/Serialization/Serializer.h"
#include "Core/Utility/InputHandler.h"

namespace Elysium
{
	using namespace Serialize;
	using namespace Model;
	using namespace Utility;
	using PuzzleStacker = Stack<Puzzle>;

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

		bool Menu::OptionsHandler(MenuOptions option) const //todo: Implement seperate threads for each menu option
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
			const int puzzleSize = InputHandler::HandleInput("Enter the dimension value of the configuration:\n-> ", 20, 3);
			const int maxElement = puzzleSize * puzzleSize + puzzleSize;
			PuzzleStacker puzzleStack (50, puzzleSize);
			for (;;)
			{
				Puzzle* puzzle = puzzleStack.Push(Puzzle(puzzleSize));
				ASSERT(puzzle == nullptr, "[Elysium::Menu::HandleManualConfig]: Puzzle pointer returned from stack shouldn't be a null pointer.",true)
				for (int i = 0; i < (puzzleSize*puzzleSize)-1; i++)
				{
					for(;;)
					{
						if (puzzle->InsertValue(InputHandler::HandleInput("Enter a value to add to the configuration:\n-> ", maxElement, 0)))
							break;
						std::cout << "That value exists already! ";
					}
				}
				puzzle->InsertEmptyBlock();
				if (!InputHandler::HandleInput("That configuration has been saved, do you want to configure another puzzle? Enter [Y/N]:\n-> "))
					break;
			}
			if (InputHandler::HandleInput("The configurations have been generated, would you like to save them to a file? Enter [Y/N]:\n-> "))
				Serializer(puzzleStack);
			if (InputHandler::HandleInput("Would you like to simulate strategies for these configurations? Enter [Y/N]:\n-> "))
			{
				ProcessPuzzle(&puzzleStack);
				Serializer(puzzleStack);
			}
			return true;
		}

		bool Menu::HandleAutoConfig() const	//todo: Verify whether or not user should be able to directly process configured puzzles, or if its sufficient to let them read that file in through the loop.
		{
			const int puzzleSize = InputHandler::HandleInput("Enter the dimension value of the configurations:\n-> ", 20, 3);
			const int elementCount = puzzleSize * puzzleSize + puzzleSize;
			const int puzzleCount = InputHandler::HandleInput("How many configurations would you like to generate? Range -> [1-20000]:\n-> ", 20000, 0);
			PuzzleStacker puzzleStack(puzzleCount, puzzleSize);

			int* unsortedArray = new int[elementCount];
			for (int i = 0; i < elementCount; ++i)
				unsortedArray[i] = i + 1;
			for (int i = 0; i < puzzleCount; i++)
			{
				Random::Randomize(unsortedArray, elementCount);
				puzzleStack.Push(Puzzle(puzzleSize, unsortedArray));
			}
			delete[] unsortedArray;
			if (InputHandler::HandleInput("The configurations have been generated, would you like to save them to a file? Enter [Y/N]:\n-> "))
				Serializer(puzzleStack);
			if (InputHandler::HandleInput("Would you like to simulate strategies for these configurations? Enter [Y/N]:\n-> "))
			{
				ProcessPuzzle(&puzzleStack);
				Serializer(puzzleStack);
			}
			return true;
		}

		bool Menu::HandleReadConfig() const	//todo: Implement and insert processing call.
		{
			PuzzleStacker puzzleStack(1);
			Deserializer(puzzleStack);
			ProcessPuzzle(&puzzleStack);
			Serializer(puzzleStack);
			return true;
		}

		void Menu::ProcessPuzzle(const Stack<Puzzle>* puzzleStacker) const
		{
			std::vector<int> partialIndexes;
			partialIndexes.reserve(puzzleStacker->GetElementSize() - 1);
			const int initialChoice = InputHandler::HandleInput("Would you like to calculate [None (0)], [All (-1)] or [Some (1)] of the partial solutions? Enter[0/-1/1]:\n-> ", 1, -2);
			if(initialChoice == -1) //todo: Verify this choice includes all the partials.
			{
				for (unsigned i = 0; i < partialIndexes.capacity(); i++)
					partialIndexes.emplace_back(i + 2);
			}
			if (initialChoice == 1)
			{		
				for (;;)
				{
					const int choice = InputHandler::HandleInput("Enter a partial you would like to calculate:\n-> ", puzzleStacker->GetElementSize(), 1);
					if (!(std::any_of(partialIndexes.begin(), partialIndexes.end(), [&](const int val) { return val == choice; })))
					{
						partialIndexes.emplace_back(choice);
						std::cout << "Partial added successfully.\n -> ";
						if (static_cast<int>(partialIndexes.size()) == (puzzleStacker->GetElementSize() - 1))
							break;
						if (!InputHandler::HandleInput("Would you like to include calculations for another partial? Enter [Y/N]:\n-> "))
							break;
					}
					else
						std::cout << "That partial already exists, try a different one!\n -> ";
				}
				std::sort(partialIndexes.begin(), partialIndexes.end()); 
			}
			for (int i = 0; i < puzzleStacker->GetSize(); i++)
				(*puzzleStacker)[i].RunPuzzleSolver(&partialIndexes);
		}

		bool Menu::HandleQuit() const
		{
			return InputHandler::HandleInput("Do  you want to EXIT the application? Enter [Y/N]:\n-> ");
		}
	}
}