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
	namespace Application
	{
		class MenuUI
		{
		public:
			MenuUI() = default;
			~MenuUI() = default;

			void RunOptionsMenu();
			bool RunExitMenu() const;
		private:
			enum Options { EXIT = 0, MANUAL = 1, AUTO = 2, MENU = 6};

			bool InputHandler(Options option) const;
			const int HandleNumberInput(int rangeMax, int rangeMin) const;

			bool HandleBinaryChoice(const char* message) const;

			bool HandleExit() const;

			bool HandleManualConfig() const;
			bool HandleAutoConfig() const;
		};
	}
}