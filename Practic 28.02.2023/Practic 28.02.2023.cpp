
#include <Windows.h>
#include <iostream>
#include <stdio.h>

using namespace std;
    //  fopen(), fopen_s()
    //  fclose()
    //  fgets(), fgetc(), fscanf_s()
    //  fputs(), fputc(), fprintf_s()
    //  feof_s()
    // 
    //  fwrite(const void* buffer, size_t size, size count, FILE* f)
    //  fread(void* buffer, size_t size, size count, FILE* f)
    //  fseek(FILE *f, int offset,[int origin])
    


    //  ||NEW METODS||
    #include <io.h>

    // int _access(const char* path, int mode) - определяет разрешение файла или директории
    //          mode:    (Если разрешение есть - return 0, иначе return -1)
    //           00 проверка на существование
    //           02 проверка на разрешение на запись
    //           04 проверка на разрешение на чтение
    //           06 проверка на разрешение на запись и чтение
    
    // long _filelenght(int handle) - возращает размер файла в байтах
    // handle - дескриптор
    
    // int _locking(int handle, int mode, long nBy) - блокирует или разблокирует байты файла
    //                                                начиная с текущей позиции
    //      mode:    (тип блокировки)
    //       _LK_LOCK (_LK_RLCK) - блокирует байты (если нет, повтор попытки через секунду(после десяти попыток - ошибка))
    //       _LK_BNLCKб (_LK_NBRLCK) - блокировкай байтов (если не получилось - ошибка (-1))
    //       _LK_UNLCK - разблокировка файла
    //      nBy - количество байт для блокировки
    
    // int _fileone(FILE* f) - получение дескриптора файла

void RussianMessage(const char* str) {
    char message[100];
    CharToOemA(str, message);
    cout << message;
}

bool Test_CopyFile(char* source, char* destination) {
    const int size = 65536;
    FILE* src, * dst;
    if (!fopen_s(&src, source, "r")) {
        long handle = _fileno(src); // получение дескриптора файла
        char* data = new char[size]; // выделение памяти под буфер
        if (!fopen_s(&dst, destination, "wb")) {
            int realsize;
            while (!feof(src)) {
                realsize = fread(data, sizeof(char), size, src);
                fwrite(data, sizeof(char), realsize, dst);
            }
        }
        else {
            delete[] data;
            return false;
        }
    }
    else
        return false;

    fclose(src);
    fclose(dst);

    return true;
}


    #include <stdio.h> //<io.h>
       
    // rename(char* oldname, char* newname) - переименование файла
    // remove(const char* filename) - удаляет файл

    // _findfirst(char* path, _finddata_t* fileinfo) - находит файлы по указанному пути
    //              _finddata_t: - структура информации о файле
    //                |unsigned attrib:
    //                  _A_NORMAL
    //                  _A_RONLY
    //                  _A_HIDDEN
    //                  _A_SYSTEM
    //                  _A_SUBDIR
    //                  _A_ARCH
    //                |time_t time_create
    //                |time_t time_access
    //                |time_t time_write
    //                |_fsize_t size
    //                |char name[260]

    // _findnext(long done, _finddata* fileinfo), где done - дескриптор
    // _findclose(long done) - очищает память от группы найденных файлов в памяти


void Test_RenameFile(){

    char oldName[50];
    char newName[50];

    cout << "Enter the old name -> "; cin >> oldName;
    cout << "Enter the new name -> "; cin >> newName;

    if (rename(oldName, newName) != 0)
        cout << "Error!\nfile haven't been renamed\n";
    else
        cout << "Successfuly!\n";
}


void Test_RemoveFile(){

    char name[50];
    
    cout << "Enter the name -> "; cin >> name;

    if (remove(name) != 0)
        cout << "Error!\n file haven't been deleted\n";
    else
        cout << "Successfuly!\n";
}


void Test_Dir(){

    char path[78];
    cout << "Enter the path -> "; cin >> path;

    char mask[15];
    cout << "Enter the mask -> "; cin >> mask;

    strcat_s(path, mask);
    _finddata_t* fileinfo = new _finddata_t;
    intptr_t done = _findfirst(path, fileinfo);
    int count = 1;
    do {
        cout << fileinfo->name << endl;
        count++;
    } while (_findnext(done, fileinfo) != -1);

    cout << "\nInfromation:\n were found" << count << endl;
    cout << "File(s) in folder ...... " << path << endl;

    _findclose(done);
    delete fileinfo;
}


    // ||ДИРЕКТОРИИ||
    #include <direct.h>
    // int _mkdir(const char* dirname) - создаёт директорию по указанному пути
    // int _rmdir(const char* dirname) - удаляет директорию по указанному пути

void Test_RenameDirectory() {
    char oldName[50];
    char newName[50];

    cout << "Enter the old name -> "; cin >> oldName;
    cout << "Enter the new name -> "; cin >> newName;

    if (rename(oldName, newName) != 0)
        cout << "Error!\directory haven't been renamed\n";
    else
        cout << "Successfuly!\n";
}

void Test_RemoveDirectory() {

    char name[50];

    cout << "Enter the name -> "; cin >> name;

    if (_rmdir(name) != -1)
        cout << "Error!\n directory haven't been deleted\n";
    else
        cout << "Successfuly!\n";
}

void Test_CreateDirectory() {
    char name[50];
    cout << "Enter the name -> "; cin >> name;

    if (_mkdir(name) != -1)
        cout << "Error!\n directory haven't been deleted\n";
    else
        cout << "Successfuly!\n";
}

void main()
{
    cout << "Please, select preffer number\n";
    char c;
    do {
        cout << "\n1 - Rename\n";
        cout << "\n2 - Remove\n";
        cout << "\n3 - Show some folder\n";
        cout << "\n0 - Exit\n";
        cin >> c;
        
        switch (c) {
        case '1':
            Test_RenameFile();
            break;
        case '2':
            Test_RemoveFile();
            break;
        case '3':
            Test_Dir();
            break;
        }
    } while (c != '0');

   /* char source[_MAX_PATH];
    char destination[_MAX_PATH];
    char answer[20];

    RussianMessage("\nВведите путь и название копируемого файла\n");
    cin.getline(source, _MAX_PATH);
    if (_access(destination, 00) == 0) {
        RussianMessage("\nУказан неверный путь к файлу или его название\n");
        return;
    }

    RussianMessage("\nВведите путь и название нового файла\n");
    cin.getline(destination, _MAX_PATH);

    if (_access(destination, 00) == -1) {
        RussianMessage("\nТакой файл уже создан. Перезаписать?(1 - да | 2 - нет)\n");
        cin.getline(answer, 20);
        if (!strcmp(answer, "2")) {
            RussianMessage("\nОперация отменена\n");
            return;
        }
        else if (!strcmp(answer, "1")) {
            if (_access(destination, 02) == -1) {
                RussianMessage("\nНет доступа к записи\n");
                return;
            }
        }
        else {
            RussianMessage("\nНеправильной ввод\n");
            return;
        }
    }
    if (!Test_CopyFile(source, destination)) {
        RussianMessage("\nОшибка при работе с файлом\n");
        return;
    }
    return;*/
    
}

