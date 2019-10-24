/**
 * FILENAME		: ElysiumThread.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 21/10/2019
 * Description	: This header contains the declaration for the abstract thread class for this engine, used to run the application.
 *                Can be extended to run multiple instances of the application simultaneously using: https://docs.microsoft.com/en-us/windows/console/creation-of-a-console?redirectedfrom=MSDN
 *                and https://www.codeproject.com/Articles/13368/Multiple-consoles-for-a-single-application
 */
#pragma once

#ifdef EM_PLATFORM_WINDOWS
#include <windows.h>

namespace Elysium
{
	namespace Application
	{
		class ElysiumThread
		{
		public:
			ElysiumThread() {}
			virtual ~ElysiumThread() { CloseHandle(m_Handle); }
			virtual void Start();
			virtual void Join();
			inline virtual DWORD GetId() const { return m_Id; }
		protected:
			virtual void Run() = 0;
			friend DWORD ThreadFunction(LPVOID T);
			HANDLE m_Handle;
			DWORD m_Id;
		private:
			ElysiumThread(const ElysiumThread& src);
			ElysiumThread& operator=(const ElysiumThread& rhs);
		};
	}
}
#endif