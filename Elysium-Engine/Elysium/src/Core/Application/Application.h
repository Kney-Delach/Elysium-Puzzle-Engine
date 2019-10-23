/**
 * FILENAME		: Application.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 12/10/2019
 * Description	: This file contains the declaration of the interface which is used to interact with the client (user).
 */
#pragma once
#include "Threads/Thread.h"

namespace Elysium
{
	namespace Application
	{
		class Application : public ElysiumThread
		{
		public:
			Application(DWORD id) { m_Id = id; }
			~Application() = default;
			virtual void Run() override;
		private:
			bool m_Running = true;
		};
	}
}