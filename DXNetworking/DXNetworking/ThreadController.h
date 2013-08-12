#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <map>
#include <vector>

using namespace std;

#define ThrdCon ThreadController::Instance()

class ThreadController
{
private:
	struct ThreadInfo{
		DWORD	ID;
		HANDLE	hThread;
		int		priority;
		bool	suspended;
		ThreadInfo(HANDLE ht, int p, bool s) {
			hThread = ht;
			priority = p;
			suspended = s;
		}
	};
	HANDLE						myMutex;
	ThreadInfo*					thInfo;
	HANDLE		handle;
	map<LPCSTR, HANDLE*>		m_mMutexes;
	map<DWORD, ThreadInfo*>		m_mThreads;
	vector<ThreadInfo*>			m_vThreads;
public:
	ThreadController();
	~ThreadController();

	// Returns thread id
	DWORD		CreateNewThread(void* funcProc, void* funcParam, bool startSuspended);
	
	HANDLE		MakeMutex(LPCSTR mutexName);
	bool		MutexOpen(LPCSTR mutexName);
	bool		MutexRelease(LPCSTR mutexName);
	//void		ResumeThread(DWORD threadID);
	//void		SuspendThread(DWORD threadID);

	// Singleton
	static ThreadController* Instance(){
		static ThreadController instance; 
		return &instance;
	}
};