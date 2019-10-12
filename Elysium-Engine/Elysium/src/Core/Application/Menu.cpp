/**
 * FILENAME		: Logger.cpp
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 12/10/2019
 * Description	: This file contains the class declaration for the console interface to interact with the user.
 */
#include "empch.h"
#include "Core/Application/Menu.h"

namespace Elysium
{
	namespace UI
	{

		void MenuUI::RunOptionsMenu()
		{
			// display the possible options to the user, and then call the relevant functionality 
			// in the system to process those choices.
			std::cout << "This is a temporary options menu.\n";
		}

		bool MenuUI::RunExitMenu() const
		{
			return InputHandler(EXIT);
		}

		//todo: Verify conditions are in order of most -> least called.
		bool MenuUI::InputHandler(Options option) const
		{
			if(option == EXIT)
			{
				return HandleExit();
			}
			return false;
		}

		bool MenuUI::HandleExit() const
		{
			std::string input = "";
			char cInput = { 0 };

			while (true) {
				std::cout << "Do  you want to EXIT the application? Enter [Y/N]: ";

				std::getline(std::cin, input);

				if (input.length() == 1) 
				{
					cInput = input[0];
					if(cInput == 'y' || cInput == 'Y')
					{
						return true;
					}
					if(cInput == 'n' || cInput == 'N')
					{
						return false;
					}
				}
				std::cout << "Invalid input! - ";
			}
		}
	}
}