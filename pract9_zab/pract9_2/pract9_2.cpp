// pract9_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale>
#include <conio.h>
#include <windows.h>
using namespace std;
int main(int argc, char* argv[]) {

    setlocale(LC_ALL, "rus");
    if (argc != 2)
    {
        cout << "Выход из консоли.\n";
        cin.get();
        return 1;
    }
    HANDLE hThread = (HANDLE)(ULONG_PTR)_atoi64(argv[1]);
    cout << "Дочерний процесс запущен. " << endl;
    
    int opens;
    while (true) {
   
        cout << "*Меню*\n";
        cout << "1 - Приостановить счетчик\n2 - Возобновить счетчик\n3 - Завершить счетчик и выйти\n";
         
            cin >> opens;

        switch (opens) {
        case 1: {
            DWORD suspendCount = SuspendThread(hThread);
            cout << "Остановлен.\n";
            break;
        }

        case 2: {
            DWORD suspendCount = ResumeThread(hThread);
            cout << "Возобновлен.\n";
            break;
        }

        case 3: {
            cout << "Выход.\n";
            TerminateThread(hThread, 0);
            WaitForSingleObject(hThread, INFINITE);
            CloseHandle(hThread);
            return 0;
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
