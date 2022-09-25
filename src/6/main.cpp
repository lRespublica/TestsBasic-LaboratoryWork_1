#include<iostream>
#include<cstdlib>
#include<string>
#include<time.h>

using namespace std;

void generateAmount(uint64_t * amountOf, uint64_t size, int64_t length)
{
    int64_t amountSize = 0;
    for(int i = 0; i < size; i++)
    {
        if(amountSize >= length)
        {
            amountSize = 0;
            break;
        }
        amountOf[i] = rand() % (length - amountSize) + 1;
        amountSize += amountOf[i];
    }

    if(amountSize != length)
        generateAmount(amountOf, size, length);
}

//! Копировать значения одного массива в другой
//! \warning Предполагается то, что на новый массив уже выделена память, не меньше чем на оригинальный
void copyArray(uint64_t * originalArr, uint64_t * newArray, uint64_t size)
{
    for(int i = 0; i < size; i++)
    {
        newArray[i] = originalArr[i];
    }
}

char generateSpecialSymbol(uint64_t number)
{
    string symbols = {
      '!', '#', '%', ':', ',', '.', ';', '*', '(', ')', '[', ']', '{', '}', '<', '>', '/', '?', '@', '&', '-', '+', '='
    };

    return symbols.at(number % symbols.size());
}

// 0 - Lowercase;
// 1 - Uppercase;
// 2 - Nums;
// 3 - Special symbols
char generateSymbol(uint64_t type)
{
    if(type == 0)
        // From a to z
        return (rand() % 26) + 97;
    else if(type == 1)
        // From A to Z
        return (rand() % 26) + 65;
    else if(type == 2)
        // from 0 to 9
        return (rand() % 10) + 48;
    else
        return generateSpecialSymbol(rand());
}

int main()
{
    srand(time(0));

    int64_t length;

    cin >> length;
    if (cin.fail())
    {
        cerr << "Error. Input is not integer number. Please, try again" << endl;
        return 1;
    }

    if (length <= 0)
    {
        cerr << "Error. Numbers cannot be less or equal to 0!" << endl;
        return 1;
    }

    string textString;
    textString.reserve(length);

    // 0 - Lowercase;
    // 1 - Uppercase;
    // 2 - Nums;
    // 3 - Special symbols
    uint64_t amountOf[4];
    uint64_t amountOfReduced[4];

    generateAmount(amountOf, 4, length);
    copyArray(amountOf, amountOfReduced, 4);

    for(int i = 0; i < length; i++)
    {
        uint64_t type = rand() % 4;
        if(amountOfReduced[type] != 0)
        {
            textString += generateSymbol(type);
            amountOfReduced[type]--;
        }
        else
        {
            i--;
        }
    }

    cout << textString << endl;

    return 0;
}
