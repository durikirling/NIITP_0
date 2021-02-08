// NIITP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

// ТЕСТОВОЕ ЗАДАНИЕ №3(1) "Массивы"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h> // для определения CLOCKS_PER_SEC

using namespace std;

bool InputCheck(int value) { // проверка ввода - только целые числа
    if (cin.fail())
    {
        cin.clear(); // обнуление всех битов состояния (возвращаем cin в "обычный" режим работы)
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // удаление значения предыдущего ввода из входного буфера
        return false;
    }
    return true;
}

vector<string> compareArr(vector<string> array_1, vector<string> array_2, int size_1, int size_2) // сравниваем два входных массива и создаем третий - результирующий
{
    int size = 0; // указываем нулевую размерность результирующего массива, чтобы увеличивать её по мере необходимости
    vector <string> arrayRes(size);

    int k = 0;

    bool flag = true; // для проверки на повторную запись элемента в результирующий массив (если true - элемент еще не записан)

    for (int i = 0; i < size_1; i++) {
        for (int j = 0; j < size_2; j++) {
            if (array_1[i] == array_2[j]) {
                flag = true;
                for (int m = 0; m < arrayRes.size(); m++) {
                    if (arrayRes[m] == array_1[i]) { // если элемент уже записан в результирующий массив
                        flag = false;
                        break;
                    }
                }
                if (flag == true) { // если элемент ещё НЕ записан в результирующий массив
                    size++;
                    arrayRes.resize(size); // увеличиваем размерность результипующего массива для записи нового элемента
                    arrayRes[k] = array_1[i];
                    k++;
                }
            }
        }
    }
    return arrayRes;
}

void ArrayShow(vector<string> arrayRes) // вывод результирующего массива на экран (в консоль)
{
    cout << endl;
    cout << "Результирующий массив: ";
    for (int i = 0; i < arrayRes.size(); i++) {
        cout << arrayRes[i] << " "; // вывод элемента массива на экран          
    }
    cout << endl;
}

void ArrayWriteToFile(vector<string> arrayRes) // запись результирующего массива в файл
{
    ofstream fileOut("ResultNIITP.txt"); // создаём объект класса ofstream для записи и связываем его с файлом ResultNIITP.txt, куда будет выводится результирующий массив
    if (!fileOut)
    {
        cout << "Файл ResultNIITP.txt не может быть открыт для записи\n"; // выводим сообщение об ошибке, возникшей при открытии файла
    }

    fileOut << "Результирующий массив: ";

    for (int i = 0; i < arrayRes.size(); i++) {
        fileOut << arrayRes[i] << " "; // запись элемента массива в файл
    }
    fileOut.close();
    cout << "Запись в файл ResultNIITP.txt была осуществлена.\n";
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int size_1, size_2; // размерности входных массивов

    int firstValue, lastValue; // диапазон случайных чисел

    bool choice; // определение выбора заполнения входных массивов

    int myChoice; // выбор заполнения входных массивов

    while (true) {
        cout << "Выберите вариант заполнения входных массивов:\n"
            << "1. Вручную - можно ввести как числа, так и другие символы.\n"
            << "2. Автоматически - массивы будут заполнены случайными числами.\n\n"
            << "Выбор: ";

        cin >> myChoice;

        if (InputCheck(myChoice) && (myChoice == 1 || myChoice == 2)) {
            if (myChoice == 1)
                choice = true;
            else
                choice = false;
            cout << "---\n---\n";
            break;
        }
        cout << "Ошибка ввода, попробуйте снова. Введите 1 или 2.\n";
    }

    if (choice == false) {
        while (true) {
            cout << "Введите диапазон случайных чисел:\n"
                << "От:";
            cin >> firstValue;
            cout << "До:";
            cin >> lastValue;

            if (InputCheck(firstValue) && InputCheck(lastValue) && firstValue < lastValue) {
                lastValue = lastValue - firstValue + 1;
                cout << "---\n---\n";
                break;
            }
            cout << "Ошибка ввода, попробуйте снова. Введите числа, чтобы 'От:' было меньше 'До:'.\n";
        }
    }

    while (true) {
        cout << "Введите размерность первого массива: ";
        cin >> size_1;

        if (InputCheck(size_1) && size_1 > 15) {
            cout << "---\n---\n";
            break;
        }
        cout << "Ошибка ввода, попробуйте снова. Введите положительное число не менее 16.\n";
    }

    vector<string> array_1(size_1); // динамическое выделение памяти для первого входного массива

    if (choice == true) {
        cout << "Введите " << size_1 << " элементов: ";
        for (int i = 0; i < size_1; i++) {
            cin >> array_1[i];  // заполняем первый массив вручную
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // если было введено больше символов, чем указанная размерность массива
    }
    else {
        for (int i = 0; i < size_1; i++) {
            array_1[i] = to_string(firstValue + rand() % lastValue); // заполняем первый массив автоматически
        }
    }

    // cout << "---\n";

    while (true) {
        cout << "Введите размерность второго массива: ";
        cin >> size_2;

        if (InputCheck(size_2) && size_2 > 15) {
            cout << "---\n---\n";
            break;
        }
        cout << "Ошибка ввода, попробуйте снова. Введите положительное число не менее 16.\n";
    }

    vector<string> array_2(size_2); // динамическое выделение памяти для второго входного массива

    if (choice == true) {
        cout << "Введите " << size_2 << " элементов: ";
        for (int i = 0; i < size_2; i++) {
            cin >> array_2[i];  // заполняем второй массив вручную
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else {
        for (int i = 0; i < size_2; i++) {
            array_2[i] = to_string(firstValue + (rand() % lastValue)); // заполняем второй массив автоматически
        }
    }

    cout << "\n|||\n";

    cout << "\nПодождите, идут вычисления...\n";

    vector <string> arrayRes = compareArr(array_1, array_2, size_1, size_2); // поиск общих элементов в двух входных массивах и запись в третий

    cout << endl;

    cout << "Входной массив №1: ";
    for (int i = 0; i < size_1; i++) {
        cout << array_1[i] << " "; // вывод элементов массива №1 на экран
    }

    cout << endl << endl;

    cout << "Входной массив №2: ";
    for (int i = 0; i < size_2; i++) {
        cout << array_2[i] << " "; // вывод элементов массива №2 на экран
    }

    cout << endl;

    if (arrayRes.size() == 0) // если массив пустой
        cout << "\nНе было найдено ни одного одинакового элемента. Выходной массив пустой.\n";
    else {
        ArrayShow(arrayRes); // вывод результирующего массива на экран
        cout << endl;
        ArrayWriteToFile(arrayRes); // запись результирующего массива в файл
        cout << endl;
    }
}