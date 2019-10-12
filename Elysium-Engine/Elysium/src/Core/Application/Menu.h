/**
 * FILENAME		: Menu.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 12/10/2019
 * Description	: This file contains the class declaration for the console interface to interact with the user.
 * Useful Links	: Enums -> https://docs.microsoft.com/en-us/cpp/cpp/enumerations-cpp?view=vs-2019
 */
#pragma once

namespace Elysium
{
	namespace UI
	{
		class MenuUI
		{
		public:
			MenuUI() = default;
			~MenuUI() = default;

			void RunOptionsMenu();
			bool RunExitMenu() const;
		private:
			enum Options { MENU_OPTIONS, EXIT = 0 };
			bool InputHandler(Options option) const;

			bool HandleExit() const;
		};
	}
}