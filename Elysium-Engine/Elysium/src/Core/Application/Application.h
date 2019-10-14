/**
 * FILENAME		: Application.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 12/10/2019
 * Description	: This file contains the declaration of the interface which is used to interact with the client (user).
 */
#pragma once

namespace Elysium
{
	namespace Application
	{
		class Application
		{
		public:
			Application() = default;
			~Application() = default;
			void Run();
		private:
			bool m_Running = true;
		};
	}
}