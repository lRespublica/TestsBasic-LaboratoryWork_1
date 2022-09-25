#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

//! Инициализировать массив случайными числами в диапаоне от -100 до 30
//! \param arr Адрес начала массива
//! \param size Размер массива
void initArray(int64_t * arr, uint64_t size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 130 - 99;
    }
}

//! Копировать значения одного массива в другой
//! \warning Предполагается то, что на новый массив уже выделена память, не меньше чем на оригинальный
void copyArray(int64_t * originalArr, int64_t * newArray, uint64_t size)
{
    for(int i = 0; i < size; i++)
    {
        newArray[i] = originalArr[i];
    }
}

//! Проверить массив на то, что больше половины элементов - не отрицательные
//! \param arr Адрес начала массива
//! \param size Размер массива
bool checkArray(int64_t * arr, uint64_t size)
{
    uint64_t amountNegative = 0;
    uint64_t amountPositive = 0;
    for(int i = 0; i < size; i++)
    {
        if(arr[i] < 0)
            amountNegative++;
        else
            amountPositive++;
    }
    return (amountPositive > amountNegative);
}

//! Случайно поменять знаки у чисел в массиве
//! \param arr Адрес начала массива
//! \param size Размер массива
void changeSignes(int64_t * arr, uint64_t size)
{
    for(int i = 0; i < size; i++)
    {
        if (rand() % 2)
            arr[i] = -arr[i];
    }
}

//! Проверить чётность числа
bool isEven(int64_t num)
{
    return !(num%2);
}

//! Проверить нечётность числа
bool isOdd(int64_t num)
{
    return num%2;
}

//! Посчитать количество четных положительных чисел на нечётных позициях
uint64_t countEvenPositiveOnOddPositions(int64_t * arr, uint64_t size)
{
    uint64_t counter = 0;
    for(int i = 1; i < size; i += 2)
    {
        if(arr[i] > 0 && isEven(arr[i]))
            counter++;
    }
    return counter;
}

//! Посчитать, сколько цифр содержит число
uint64_t howManyDigitsContain(int64_t num)
{
    num = abs(num);
    uint64_t count = 0;
    while(num > 0)
    {
        num /= 10;
        count++;
    }
    return count;
}

//! Посчитать сколько цифр содержат в себе все отрицательные числа массива
uint64_t countDigitsInNegativeNumbers(int64_t * arr, uint64_t size)
{
    uint64_t count = 0;
    for(int i = 0; i < size; i++)
    {
        if(arr[i] < 0)
            count += howManyDigitsContain(arr[i]);
    }
    return count;
}

//! Посчитать сумму нечётных чисел на чётных позициях
int64_t countSumOfOddNumbersOnEvenPosition(int64_t * arr, uint64_t size)
{
    int64_t sum = 0;
    for(int i = 0 ; i < size; i += 1)
    {
        if(isOdd(arr[i]))
            sum += arr[i];
    }
    return sum;
}

//! Найти количество отрицательных элементов в массиве
uint64_t getAmountOfNegativeNumbers(int64_t * arr, uint64_t size)
{
    uint64_t count;
    for(int i = 0; i < size; i++)
    {
        if(arr[i] < 0)
            count++;
    }
    return count;
}

//! Записать в файл значение массива
void writeValueOfArray(ofstream &fout, int64_t * arr, uint64_t size)
{
    for(int i = 0; i < size; i++)
        fout << arr[i] << " ";
    fout << endl;
}

int main()
{
    srand(time(0));

    uint64_t size = rand() % 30 + 20;
    int64_t arr[size];
    int64_t originalArr[size];

    initArray(originalArr, size);
    copyArray(originalArr, arr, size);

    while(checkArray(arr, size) == false)
        changeSignes(arr, size);

    uint64_t evenPositiveOnOddPositions = countEvenPositiveOnOddPositions(arr, size);
    uint64_t digitsInNegativeNumbers = countDigitsInNegativeNumbers(arr, size);
    int64_t sumOfOddNumbersOnEvenPositions = countSumOfOddNumbersOnEvenPosition(arr, size);

    int64_t allParameters = evenPositiveOnOddPositions + digitsInNegativeNumbers + sumOfOddNumbersOnEvenPositions;
    uint64_t amountOfNegativeNumbers = getAmountOfNegativeNumbers(arr, size);

    if(isEven(allParameters))
        allParameters += amountOfNegativeNumbers;
    else
        allParameters -= amountOfNegativeNumbers;

    ofstream fout;
    fout.open("3.txt");

    if(!fout.is_open())
    {
        cerr << "Cannot open file to write" << endl;
        return 1;
    }

    writeValueOfArray(fout, originalArr, size);
    writeValueOfArray(fout, arr, size);
    fout << evenPositiveOnOddPositions << ";" << digitsInNegativeNumbers << ";" << sumOfOddNumbersOnEvenPositions << endl;
    fout.close();

    return 0;
}
