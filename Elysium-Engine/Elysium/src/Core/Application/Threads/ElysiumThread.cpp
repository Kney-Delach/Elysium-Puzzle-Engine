/**
 * FILENAME		: Thread.cpp
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 21/10/2019
 * Description	: This header contains the implementation for the abstract thread class for this engine, used to run the application.
 */
#include "empch.h"
#include "ElysiumThread.h"

#ifdef EM_PLATFORM_WINDOWS
#include <windows.h>

namespace Elysium
{
	namespace Application
	{
		DWORD ThreadFunction(LPVOID T)
		{
			ElysiumThread* t = static_cast<ElysiumThread*>(T);
			t->Run();
			return NULL;
		}

		void ElysiumThread::Start()
		{
			m_Handle = CreateThread(
				NULL,
				0,
				(LPTHREAD_START_ROUTINE)&ThreadFunction,
				(LPVOID)this,
				0,
				&m_Id);
		}

		void ElysiumThread::Join()
		{
			WaitForSingleObject(m_Handle, INFINITE);
		}
	}
}
#endif