#include "empch.h"
#include "Thread.h"

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