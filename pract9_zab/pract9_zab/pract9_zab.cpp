// pract9_zab.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>
#define MAX_PROCESS 10
using namespace std;
HANDLE counterThread = NULL;
PROCESS_INFORMATION processes[4][MAX_PROCESS] = { 0 };
int processCount[4] = {0};
DWORD WINAPI CounterThread(LPVOID ipParam) {
    int count = 0;
    while (true) {
        cout << "Счётчик: " << ++count << endl;
        Sleep(1000);
    }
    return 0;
}
int main()
{
    int count = 0;
    setlocale(LC_ALL, "rus");
    wchar_t word[] = L"C:\\Program Files\\Microsoft Office\\root\\Office16\\WINWORD.EXE ";
    wchar_t excel[] = L"C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE ";
    wchar_t paint[] = L"C:\\WINDOWS\\system32\\mspaint.exe ";
    wchar_t notepad[] = L"C:\\WINDOWS\\system32\\notepad.exe ";

    STARTUPINFO si1;

    STARTUPINFO si2;
   
    STARTUPINFO si3;

    STARTUPINFO si4;
 

    ZeroMemory(&si1, sizeof(STARTUPINFO));
    si1.cb = sizeof(STARTUPINFO);

    ZeroMemory(&si2, sizeof(STARTUPINFO));
    si2.cb = sizeof(STARTUPINFO);

    ZeroMemory(&si3, sizeof(STARTUPINFO));
    si3.cb = sizeof(STARTUPINFO);

    ZeroMemory(&si4, sizeof(STARTUPINFO));
    si4.cb = sizeof(STARTUPINFO);

    while (true)
    {
        cout << "*Меню*\n";
        cout << " 1. Word\n 2. Excel\n 3. Paint\n 4. Notepad \n 5. Закрыть Word\n6. Закрыть Excel\n7. Закрыть Paint\n8. Закрыть Notepad\n9. Открыть счетчик\n";
        int opens;
        cin >> opens;
        switch (opens)
        {
        case 1:
        {
      
            //файл, кс, права процесса, права потока, наследуемость, запуск, среда родителя, директория, процесс, фукнции 
            if (!CreateProcess(word, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &processes[0][processCount[0]]))
            {
                cout << "Word не запущен!\n";
            }
            else
            {
                ++processCount[0];
            }
            break;

        }
        case 2: {
            if (!CreateProcess(excel, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &processes[1][processCount[1]]))
            {
                cout << "Ошибка запуска Excel!\n";
            }
            break;

        }
        case 3: {
            if (!CreateProcess(paint, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si3, &processes[2][processCount[2]]))
            {
                cout << "Ошибка запуска Paint!\n";
            }
            else
            {
                ++processCount[2];
            }
            break;
        }
        case 4: {
            if (!CreateProcess(notepad, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si4, &processes[3][processCount[3]]))
            {
                cout << "Ошибка запуска Notepade!\n";
            }
            break;
        }
        case 5: {
            if (processCount[0] > 0)
            {
                int index=processCount[0]-1;
    TerminateProcess(processes[0][index].hProcess, 0);
                        WaitForSingleObject(processes[0][index].hProcess, INFINITE);
                        CloseHandle(processes[0][index].hThread);
                        CloseHandle(processes[0][index].hProcess);
                        processes[0][index].hProcess = NULL;
                        processes[0][index].hThread = NULL;
                        processCount[0]--;
           }
            
            else {
                cout << "Word не был запущен.\n";
            }
            break;
        }
        case 6: {
            if (processCount[1]>0) {
                int index = processCount[1] - 1;
                TerminateProcess(processes[1][processCount[1]].hProcess, 0);
                WaitForSingleObject(processes[1][processCount[1]].hProcess, INFINITE);
                CloseHandle(processes[1][processCount[1]].hThread);
                CloseHandle(processes[1][processCount[1]].hProcess);
                processes[1][processCount[1]].hProcess = NULL;
                processes[1][processCount[1]].hThread = NULL;
            

            }
            else {
                cout << "Excel не был запущен.\n";
            }
            break;
        }
        case 7: {
            if (processCount[2] > 0) {
                int index = processCount[2] - 1;
                TerminateProcess(processes[2][index].hProcess, 0);
                WaitForSingleObject(processes[2][index].hProcess, INFINITE);
                CloseHandle(processes[2][index].hThread);
                CloseHandle(processes[2][index].hProcess);
                processes[2][index].hProcess = NULL;
                processes[2][index].hThread = NULL;
            }
            else {
                cout << "Paint не был запущен.\n";
            }
            break;
        }
        case 8: {
            if (processCount[3] > 0) {
                TerminateProcess(processes[1][processCount[1]].hProcess, 0);
                WaitForSingleObject(processes[1][processCount[1]].hProcess, INFINITE);
                CloseHandle(processes[1][processCount[1]].hThread);
                CloseHandle(processes[1][processCount[1]].hProcess);
                processes[1][processCount[1]].hProcess = NULL;
                processes[1][processCount[1]].hThread = NULL;
            }
            else {
                cout << "Notepade не был запущен.\n";
            }
            break;
        }
        case 9:
        {
            STARTUPINFO si;
            PROCESS_INFORMATION pi = { 0 };

            ZeroMemory(&si, sizeof(STARTUPINFO));
            si.cb = sizeof(STARTUPINFO);

            counterThread = CreateThread(NULL, 0, CounterThread, NULL, 0, NULL);
            if (counterThread == NULL) {
                cout << "Ошибка создания потока-счетчика: " << endl;
                break;
            }

            HANDLE threadHandle = NULL;
            if (!DuplicateHandle(GetCurrentProcess(), counterThread, GetCurrentProcess(), &threadHandle, 0, TRUE, THREAD_SUSPEND_RESUME | THREAD_TERMINATE)) {
                cout << "Ошибка дублирования дескриптора: " << GetLastError() << endl;
                break;
            }

            wchar_t exe[100] = L"C:\\Users\\st310-07\\Desktop\\pract9_zab\\x64\\Debug\\pract9_2.exe ";
            wchar_t symHandle[32];
            _itow_s((int)threadHandle, symHandle, 10);
            wcscat_s(exe, symHandle);

            if (!CreateProcess(NULL, exe, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
            {
                cout << "Не удалось запустить дочерний процесс!" << endl;
                CloseHandle(threadHandle);
                TerminateThread(counterThread, 0);
                CloseHandle(counterThread);
                break;
            }

            CloseHandle(threadHandle);
            CloseHandle(pi.hThread);
            CloseHandle(pi.hProcess);
            break;
        }
        default:
            cout << "Неверный выбор.\n";
            return 0;
        }

    }
    return 0;

}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
