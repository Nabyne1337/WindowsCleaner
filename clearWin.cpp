#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <codecvt>

using namespace std;

int choice_user_in_main, delete_file, delete_directory;
string userdisk_choice = "C";
bool running = true;

void cleanDirectory(const string& directoryPath) {
    delete_file = 0;
    delete_directory = 0;
    WIN32_FIND_DATAA findFileDataA;
    HANDLE hFind = FindFirstFileA((directoryPath + "\\*.*").c_str(), &findFileDataA);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (findFileDataA.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (strcmp(findFileDataA.cFileName, ".") != 0 && strcmp(findFileDataA.cFileName, "..") != 0) {
                    string subPath = directoryPath + "\\" + findFileDataA.cFileName;
                    RemoveDirectoryA(subPath.c_str());
                    delete_directory++;
                }
            }
            else {
                string filePath = directoryPath + "\\" + findFileDataA.cFileName;
                DeleteFileA(filePath.c_str());
                delete_file++;
            }
            //system("cls");
        } while (FindNextFileA(hFind, &findFileDataA));

        FindClose(hFind); 
    }
    else {
        cerr << "Ошибка при доступе к папке " << directoryPath << endl;
    }
}
void cleaner_func() {
    wchar_t tempPath[MAX_PATH];
    GetTempPathW(MAX_PATH, tempPath);

    wstring tempPathW(tempPath);
    string tempPathStr;
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    tempPathStr = converter.to_bytes(tempPathW);

    cleanDirectory(tempPathStr);
}
void cleanTempOSOn() {
    string TempOS = userdisk_choice + ":\\Windows\\TEMP";
    cleanDirectory(TempOS);
}
void cleanWindowsoldOSOn() {
    string WindowsOld = ":\\Windows.old";
    cleanDirectory(WindowsOld);
}
void cleanKERNELOn() {
    string KernelDrv = ":\\Windows\\LiveKernelReports";
    cleanDirectory(KernelDrv);
}
void cleancashOn() {
    string cashon = ":\\Windows\\Downloaded Program Files";
    cleanDirectory(cashon);
}
void cleancash() {
    string cleancash = ":\\Windows\\SoftwareDistribution";
    cleanDirectory(cleancash);
}
void startclean() {
    system("cls");
    cout << "В процессе.." << endl;
    cleanTempOSOn();
    cleanWindowsoldOSOn();
    cleanKERNELOn();
    cleancashOn();
    cleancash();
    cleaner_func(); system("cls");
    cout << "Удалено папок: " << delete_directory << endl;
    cout << "Удалено файлов: " << delete_file << endl; _getch();
}
void choicetomdisk() {
    system("cls");
    cout << "Введите только букву вашего тома с Windows: " << endl
        << "Пример: C, D, E, F" << endl
        << "Ввод --> ";
    cin >> userdisk_choice;
}

int main()
{
    setlocale(LC_ALL, "");
    while (running) {
    system("cls");
    cout << "Cleaner Windows от мусора\n"
        << "1) Запустить очистку windows\n"
        << "2) Указать том с windows\n"
        << "3) Выход\n"
        << "Выбран том диска: " + userdisk_choice << endl
        << "Ввод --> ";
    cin >> choice_user_in_main;
    switch (choice_user_in_main) {
    case 1: startclean(); break;
    case 2: choicetomdisk(); break;
    case 3: return 0; break;
    default: cout << "Введено не верно !" << endl << "Нажмите любую клавишу для продолжения!"; _getch();
        }
    }
}
