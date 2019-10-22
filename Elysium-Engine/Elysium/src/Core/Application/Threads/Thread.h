/**
 * FILENAME		: Thread.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 21/10/2019
 * Description	: This header contains the implementation for the abstract thread class for this engine.
 */
#pragma once

#ifdef EM_PLATFORM_WINDOWS
#include <windows.h>

class Thread
{
public:
	Thread() {}
	virtual ~Thread() { CloseHandle(m_Handle); }
	virtual void Start();
	virtual void Join();
	inline virtual DWORD GetId() const { return m_Id; }
protected:
	virtual void run() = 0;
	friend DWORD ThreadFunction(LPVOID T);
	HANDLE m_Handle;
	DWORD m_Id;
private:
	Thread(const Thread& src);
	Thread& operator=(const Thread& rhs);
};
#endif

inline DWORD ThreadFunction(LPVOID T)
{
	Thread* t = static_cast<Thread*>(T);
	t->run();
	return NULL;
}

void Thread::Start()
{
	m_Handle = CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)& ThreadFunction,
		(LPVOID)this,
		0,
		&m_Id);
}

void Thread::Join()
{
	WaitForSingleObject(m_Handle, INFINITE);
}