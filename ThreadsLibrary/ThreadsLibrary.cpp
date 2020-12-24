#include "pch.h"
#include "ThreadsLibrary.h"

#include <Windows.h>
#include <iostream>


using namespace std;


//variable for syncing
int progres = 0;
double ammForProgress = 0;

int choise() {
    int ch;
    cout << "\nChoose operation type"
        << " (\033[33m0\033[0m - Iteration | \033[33m1\033[0m - Id) : ";
    cin >> ch;

    if (ch == 0) {
        cout << "\nYou choose (\033[33m0\033[0m | iteration)";
        return 0;
    }

    if (ch == 1) {
        cout << "\nYou choose (\033[33m1\033[0m | id)";
        return 1;
    }

    cout << "\nWrong input\n\n";
    return -1;
}

int ammountOfThreads() {
    int ammount;
    cout << "\nEnter ammount of processes (up to \033[30m"
        << MAX_THREADS << "\033[0m) : ";
    cin >> ammount;

    if (ammount > 0 && ammount < MAX_THREADS + 1)
        return ammount;
    else
        return 0;
}

//Creating threads
void createThreads(int ammount) {
    int ch = choise();

    if (ch == -1) {
        return;
    }

    if (ch == 0) {
        double step,
            left = -0.9,
            right = -0.9 + (1.8 / ammount);

        cout << "\n Enter iteration step : ";
        cin >> step;

        for (double i = left; i <= 0.9; i += step) {
            ammForProgress += 1.0;
        }

        double data[3] = { step, left, right };

        for (int i = 0; i < ammount; i++) {
            createThreadA_Iter(&data, i);

            data[1] = data[1] + (1.8 / ammount);
            data[2] = data[2] + (1.8 / ammount);
        }
    }

    if (ch == 1) {
        int cycles;
        cout << "\n Enter ammoun of cycles : ";
        cin >> cycles;
        cycles /= ammount;
        ammForProgress = (double)ammount * (double)cycles;

        for (int i = 0; i < ammount; i++) {
            createThreadB_Id(&cycles, i);
        }
    }

}


//Thread funcs
void createThreadA_Iter(void* data, int num) {
    threadList[num] = CreateThread(
        NULL,
        0,
        iteration,
        data,
        NULL,
        &threadIDList[num]
    );
    if (threadList[num] == NULL) {
        printf(
            "\n\033[32mERROR\033[0m Could`n create thread (%d)",
            GetLastError()
        );
        ExitProcess(3);
    }
}

void createThreadB_Id(void* data, int num) {
    threadList[num] = CreateThread(
        NULL,
        0,
        idPrint,
        data,
        NULL,
        &threadIDList[num]
    );
    if (threadList[num] == NULL) {
        printf(
            "\n\033[32mERROR\033[0m Could`n create thread (%d)",
            GetLastError()
        );
        ExitProcess(3);
    }
}

void closeHandles(int ammount) {
    for (int i = 0; i < ammount; i++) {
        CloseHandle(threadList[i]);
    }
}

//Thread work functions
DWORD WINAPI iteration(LPVOID data) {

    double* arr = (double*)data;
    double step = arr[0], left = arr[1], right = arr[2];
    printf("\n (\033[32m%d\033[0m) Parameters: \n  step  :\033[33m %+.4f \033[0m \n  left  :\033[33m %+.4f \033[0m  \n  right :\033[33m %+.4f \033[0m\n", GetCurrentThreadId(), step, left, right);
    double x;
    Sleep(10);
    for (double i = left; i < right; i += step) {
        EnterCriticalSection(&CriticalSection);
        progres++;
        double percent = progres * 100 / ammForProgress;
        cout << "\n" << percent << "% | ";
        x = 1 + i / 3 - i * i / 9 + i * i * i * 5 / 81 - i * i * i * i * 80 / 1944;
        printf("\033[36m %d\033[0m -> X: %+.4f | Y: %+.4f ", GetCurrentThreadId(), i, x);
        LeaveCriticalSection(&CriticalSection);
    }
    printf("\n\n (\033[32m%d\033[0m) FINISHED!\n", GetCurrentThreadId());
    return 0;
}

DWORD WINAPI idPrint(LPVOID data) {
    int n = *(int*)data;
    for (int i = 0; i < n; i++) {
        WaitForSingleObject(Mutex, INFINITE);
        progres++;
        double percent = progres * (100.0 / (double)ammForProgress);
        cout << "\n" << percent << "% | ";
        cout << "\033[36m " << GetCurrentThreadId() << "\033[0m -> Shevcuk Illia #001244012 ";
        ReleaseMutex(Mutex);
    }
    printf("\n\n (\033[32m%d\033[0m) FINISHED!\n", GetCurrentThreadId());
    return 0;
}