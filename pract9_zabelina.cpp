// pract9_zabelina.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
HANDLE counterThread = NULL;
DWORD WINAPI CounterThread(LPVOID id) {
    int count = 0;
    while (true) {
        cout << "Счётчик: " << ++count << endl;
        Sleep(1000);
    }
    return 0;
}
int main()
{
    setlocale(LC_ALL, "rus");
    wchar_t word[] = L"C:\\Program Files\\Microsoft VS Code\\Code.exe ";
    wchar_t excel[] = L"C:\\Program Files\\Microsoft VS Code\\Code.exe ";
    wchar_t paint[] = L"C:\\Program Files\\Microsoft VS Code\\Code.exe ";
    wchar_t notepad[] = L"C:\\Program Files\\Microsoft VS Code\\Code.exe ";

    STARTUPINFO si1;
    PROCESS_INFORMATION piApp1 = {0};

    STARTUPINFO si2;
    PROCESS_INFORMATION piApp2 = {0};

    STARTUPINFO si3;
    PROCESS_INFORMATION piApp3 = {0};

    STARTUPINFO si4;
    PROCESS_INFORMATION piApp4 = {0};

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
            if (!CreateProcess(word, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &piApp1))
             {
                cout << "Word не запущен!\n";
             }
            break;

        }   
        case 2: {
            if (!CreateProcess(excel, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &piApp2))
            {
                cout << "Ошибка запуска Excel!\n";
            }
            break;

        }
        case 3: {
            if (!CreateProcess(paint, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si3, &piApp3))
            {
                cout << "Ошибка запуска Paint!\n";
            }
            break;
        }
        case 4: {
            if (!CreateProcess(notepad, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si4, &piApp4))
            {
                cout << "Ошибка запуска Notepade!\n";
            }
            break;
        }
        case 5: {
            if (piApp1.hProcess != NULL) {
                TerminateProcess(piApp1.hProcess, 0);
                WaitForSingleObject(piApp1.hProcess, INFINITE);
                CloseHandle(piApp1.hThread);
                CloseHandle(piApp1.hProcess);
                piApp1.hProcess = NULL;
                piApp1.hThread = NULL;
                system("taskkill /F /IM Code.exe > nul 2>&1");
                system("taskkill /F /IM WINWORD.exe >nul 2>&1");
            }
            else {
                cout << "Word не был запущен.\n";
            }
            break;
        }
        case 6: {
            if (piApp2.hProcess != NULL) {
                TerminateProcess(piApp2.hProcess, 0);
                WaitForSingleObject(piApp2.hProcess, INFINITE);
                CloseHandle(piApp2.hThread);
                CloseHandle(piApp2.hProcess);
                piApp2.hProcess = NULL;
                piApp2.hThread = NULL;
                system("taskkill /F /IM EXCEL.exe >nul 2>&1");

            }
            else {
                cout << "Excel не был запущен.\n";
            }
            break;
        }
        case 7: {
            if (piApp3.hProcess != NULL) {
                TerminateProcess(piApp3.hProcess, 0);
                WaitForSingleObject(piApp3.hProcess, INFINITE);
                CloseHandle(piApp3.hThread);
                CloseHandle(piApp3.hProcess);
                piApp3.hProcess = NULL;
                piApp3.hThread = NULL;
                system("taskkill /F /IM mspaint.exe >nul 2>&1");
            }
            else {
                cout << "Paint не был запущен.\n";
            }
            break;
        }
        case 8: {
            if (piApp4.hProcess != NULL) {
                TerminateProcess(piApp4.hProcess, 0);
                WaitForSingleObject(piApp4.hProcess, INFINITE);
                CloseHandle(piApp4.hThread);
                CloseHandle(piApp4.hProcess);
                piApp4.hProcess = NULL;
                piApp4.hThread = NULL;
                system("taskkill /F /IM notepad.exe >nul 2>&1");
            }
            else {
                cout << "Notepade не был запущен.\n";
            }
            break;
        }
        case 9: 
        {
            STARTUPINFO si;
            PROCESS_INFORMATION pi = {0};

            ZeroMemory(&si, sizeof(STARTUPINFO));
            si.cb = sizeof(STARTUPINFO);

            counterThread = CreateThread(NULL, 0, CounterThread, NULL, 0, NULL);
            if (counterThread == NULL) {
                cout << "Ошибка создания потока-счетчика: " << endl;
                break;
            }

            HANDLE threadHandle = NULL;
            if (!DuplicateHandle(GetCurrentProcess(), counterThread,GetCurrentProcess(),&threadHandle,0,TRUE,THREAD_SUSPEND_RESUME | THREAD_TERMINATE)) {
                cout << "Ошибка дублирования дескриптора: " << GetLastError() << endl;
                break;
            }

            wchar_t exe[100] = L"C:\\Users\\User\\Desktop\\pract9_zabelina\\x64\\Debug\\pract9_2.exe ";
            wchar_t symHandle[32];
            _itow_s((int)threadHandle, symHandle, 10);
            wcscat_s(exe, symHandle);

            if (!CreateProcess( NULL,exe,NULL, NULL,TRUE,CREATE_NEW_CONSOLE,NULL,NULL,&si,&pi))
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
