/**
 * FILENAME		: Sandbox.cpp
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 12/10/2019
 * Description	: This file should be the entry point for an application that uses the Elysium Puzzle Engine.
 *				: It was created with the goal of providing a clearer abstraction of the system entry point.
 */

#ifdef EM_PLATFORM_WINDOWS
#include "Elysium.h"

int main()
{
	auto app1 = new Elysium::Application::Application(1);
	ASSERT(app1, "[Sandox::main::Application] - Application is null!", true);
	app1->Start();
	app1->Join();
	delete app1;
	return 0;
}
#endif