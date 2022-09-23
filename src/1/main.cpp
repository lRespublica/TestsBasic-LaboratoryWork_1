#include <iostream>
#include "mover.h"

using namespace std;

int main()
{
    uint64_t sizeOfStreet, firstPoint, secondPoint;
    int64_t input[3];

    for (int i = 0; i < 3; i++)
    {
        cin >> input[i];
        while (cin.fail()){
            cin.clear();
            cin.ignore(__LONG_LONG_MAX__, '\n');
            cerr << "Error. Input is not integer number. Please, try again" << endl;
            cin >> input[i];
        }

        if (input[i] <= 0)
        {
            cerr << "Numbers cannot be less or equal to 0!" << endl;
            return 1;
        }
    }

    sizeOfStreet = input[0];
    firstPoint = input[1];
    secondPoint = input[2];

    if (firstPoint > sizeOfStreet or secondPoint > sizeOfStreet)
    {
        cerr << "Error. Points is not available in that field" << endl;
        return 1;
    }

    mover *mover;
    try
    {
        mover = new class mover(1, sizeOfStreet);
    }
    catch (std::out_of_range error)
    {
       cerr << error.what() << endl;
       return 1;
    }

    uint64_t steps = 0;
    steps += mover->moveTo(firstPoint);
    steps += mover->moveTo(secondPoint);
    steps += mover->goHome();

    cout << steps << endl;

    return 0;
}
