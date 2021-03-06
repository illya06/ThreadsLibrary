#pragma once

#ifdef  THREADSLIBRARY_EXPORTS
#define THREADSLIBRARY_API __declspec(dllexport)
#else
#define THREADSLIBRARY_API __declspec(dllimport)
#endif


#include <Windows.h>
#include <iostream>

#define MAX_THREADS 16

//syncing globals
CRITICAL_SECTION CriticalSection;
HANDLE Mutex = NULL;

//threads globals
HANDLE threadList[MAX_THREADS];
DWORD  threadIDList[MAX_THREADS];

extern "C" THREADSLIBRARY_API void shortMain();

extern "C" THREADSLIBRARY_API int  choise();
int  ammountOfThreads();

extern "C" THREADSLIBRARY_API void createThreads(int ammount);
extern "C" THREADSLIBRARY_API void closeHandles(int ammount);

extern "C" THREADSLIBRARY_API void createThreadA_Iter(void* data, int num);
extern "C" THREADSLIBRARY_API void createThreadB_Id(void* data, int num);

extern "C" THREADSLIBRARY_API DWORD WINAPI iteration(LPVOID data);
extern "C" THREADSLIBRARY_API DWORD WINAPI idPrint(LPVOID data);


