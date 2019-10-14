/**
 * FILENAME		: Application.cpp
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 12/10/2019
 * Description	: This file contains the implementation of the interface which is used to interact with the client (user).
 */
#include "empch.h"
#include "Core/Application/Application.h"
#include "Core/Application/Menu.h"

namespace Elysium
{
	namespace Application
	{
		void Application::Run()
		{
			Menu* menu = new Menu();
			ASSERT(!menu, "[Sandox::main::Application] - Application is null!", true);
			while (m_Running)
			{
				menu->RunOptionsMenu();
				m_Running = !(menu->RunQuitMenu());
			}
			delete menu;
		}
	}
}