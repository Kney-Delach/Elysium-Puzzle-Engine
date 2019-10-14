/**
 * FILENAME		: Sandbox.cpp
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 12/10/2019
 * Description	: This file should be the entry point for an application that uses the Elysium Puzzle Engine.
 *				: It was created with the goal of providing a clearer abstraction of the system entry point.
 */
#include "Elysium.h"

#ifdef EM_PLATFORM_WINDOWS

int main()
{
	auto app = new Elysium::Application::Application();
	app->Run();
	delete app;
	return 0;
}
#endif