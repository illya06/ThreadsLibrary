#pragma once

#ifdef THREADSLIBRARY_EXPORTS
#define THREADSLIBRARY_API __declspec(dllexport)
#else
#define THREADSLIBRARY_API __declspec(dllimport)
#endif

extern "C" THREADSLIBRARY_API int  ammountOfThreads();

extern "C" THREADSLIBRARY_API void createThreads(int ammount);

extern "C" THREADSLIBRARY_API void closeHandles(int ammount);

int  choise();

void createThreadA_Iter(void* data, int num);
void createThreadB_Id(void* data, int num);

DWORD WINAPI iteration(LPVOID data);
DWORD WINAPI idPrint(LPVOID data);