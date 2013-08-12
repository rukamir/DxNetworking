#include "ThreadController.h"


ThreadController::ThreadController(){
}


ThreadController::~ThreadController()
{
	for(const auto &th : m_vThreads){
		delete th;
	}
	m_vThreads.clear();
}

DWORD ThreadController::CreateNewThread(void* funcProc, void* funcParam, bool startSuspended)
{
	DWORD threadID;
	if(startSuspended){
		handle = CreateThread(NULL,
								0,
								(LPTHREAD_START_ROUTINE)funcProc,		// func pointer
								funcParam,								// fun params
								CREATE_SUSPENDED,						// start suspended
								&threadID);
	} else {
		handle = CreateThread(NULL,
								0,
								(LPTHREAD_START_ROUTINE)funcProc,		// func pointer
								funcParam,								// fun params
								0,										// starts now
								&threadID);
	}

	thInfo	=	new ThreadInfo(handle, THREAD_PRIORITY_NORMAL, startSuspended);
	thInfo->ID	=	threadID;

	m_mThreads.insert(make_pair(threadID, thInfo));
	m_vThreads.push_back(thInfo);

	return threadID;
}

HANDLE ThreadController::MakeMutex(LPCSTR mutexName){
	myMutex = CreateMutex(NULL, true, mutexName);

	m_mMutexes.insert(make_pair(mutexName, &myMutex));

	return myMutex;
}

bool ThreadController::MutexOpen(LPCSTR mutexName){
	return OpenMutex(SYNCHRONIZE, false, mutexName);
}

bool ThreadController::MutexRelease(LPCSTR mutexName){
	return ReleaseMutex(m_mMutexes.find(mutexName)->second);
}

//void ThreadController::ResumeThread(DWORD threadID){
//	m_mThreads.find(threadID)->second->suspended = true;
//	ResumeThread(m_mThreads.find(threadID)->second->ID);
//}
//
//void ThreadController::SuspendThread(DWORD threadID){
//	m_mThreads.find(threadID)->second->suspended = true;
//	SuspendThread(m_mThreads.find(threadID)->second->ID);
//}