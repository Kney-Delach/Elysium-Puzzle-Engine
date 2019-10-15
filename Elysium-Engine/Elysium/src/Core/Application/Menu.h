/**
 * FILENAME		: Menu.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 12/10/2019
 * Description	: This file contains the class declaration for the console interface to interact with the user.
 * Useful Links	: Enums -> https://docs.microsoft.com/en-us/cpp/cpp/enumerations-cpp?view=vs-2019
 */
#pragma once
#include "Core/Utility/InputHandler.h"

namespace Elysium
{
	namespace Application
	{
		class Menu
		{
		public:
			Menu() : m_InputHandler(new Utility::InputHandler()) {}
			~Menu() = default;
			void RunOptionsMenu();
			bool RunQuitMenu() const;
		private:
			enum MenuOptions { QUIT = 0, MANUAL = 1, AUTO = 2, MENU = 6};
			bool OptionsHandler(MenuOptions option) const;
			bool HandleManualConfig() const;
			bool HandleAutoConfig() const;
			bool HandleQuit() const;
		private:
			Utility::InputHandler* m_InputHandler;
		};
	}
}
