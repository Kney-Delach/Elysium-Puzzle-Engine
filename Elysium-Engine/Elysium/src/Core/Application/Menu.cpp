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
#include "Core/Model/Puzzle/PuzzleProcessor.h"
#include "Core/Utility/Random.h"

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
			bool result = OptionsHandler(MENU);
			ASSERT(!result, "[Elysium::Menu::RunOptionsMenu]: Undefined behaviour reached!", true);
		}

		bool Menu::RunQuitMenu() const
		{
			return OptionsHandler(QUIT);
		}

		bool Menu::OptionsHandler(MenuOptions option) const
		{
			if(option == MENU)		option = static_cast<MenuOptions>(m_InputHandler->HandleInput("-> ",2, 0));
			if(option == MANUAL)	return HandleManualConfig();
			if(option == AUTO)		return HandleAutoConfig();
			if(option == QUIT)		return HandleQuit();
			return false;
		}

		bool Menu::HandleManualConfig() const
		{
			Model::PuzzleProcessor<Model::Puzzle<unsigned, 4>> pp(50);
			for (;;)
			{
				Model::Puzzle<unsigned, 4>* puzzle = pp.InsertPuzzle(Model::Puzzle<unsigned, 4>()); //todo: Optimize, as currently results in a copy per puzzle.
				if (!(puzzle == nullptr))
				{
					for (int i = 0; i < 15; i++)
					{
						for(;;)
						{
							if (puzzle->InsertValue(m_InputHandler->HandleInput("Enter value to add to the configuration:\n-> ",20, 0))) 
								break;
							std::cout << "That number already exists in the configuration, try entering a different one:\n";
						}
					}
					puzzle->InsertEmptyBlock();
					if (!m_InputHandler->HandleInput("Puzzle has been completed and saved, do you want to configure another puzzle? Enter [Y/N]:\n-> "))	
						break;
				}
				else
				{
					std::cout << "Unable to insert another puzzle as stack capacity is full!\n";
					break;
				}
			}
			pp.ProcessPuzzles();
			return true;
		}

		bool Menu::HandleAutoConfig() const
		{
			std::cout << "How many configurations would you like to generate? Range -> [1-20000]:\n";
			int size = m_InputHandler->HandleInput("-> ", 20000, 0);
			std::cout << "Your request has been accepted, generating puzzles now...\n";
			Model::PuzzleProcessor<Model::Puzzle<unsigned, 4>> pp(size);
			Utility::Random random;
			unsigned unsortedArray[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
			for (unsigned i = 0; i < size; i++)
			{
				random.Randomize(unsortedArray, 20);
				Model::Puzzle<unsigned, 4> * puzzle = pp.InsertPuzzle(Model::Puzzle<unsigned, 4>(unsortedArray)); //todo: Optimize, as currently results in a copy per puzzle.
			}
			pp.ProcessPuzzles();
			return true;
		}

		bool Menu::HandleQuit() const
		{
			return m_InputHandler->HandleInput("Do  you want to EXIT the application? Enter [Y/N]:\n-> ");
		}
	}
}