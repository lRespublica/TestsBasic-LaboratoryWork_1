#include <iostream>
#include <vector>
#include <algorithm>
#include "mover.h"

using namespace std;

int main()
{
    uint64_t sizeOfStreet = 0;
    vector<int64_t> input;

    while (!cin.eof())
    {
        uint64_t number;
        cin >> number;

        if(cin.eof())
            break;

        while (cin.fail()){
            cerr << "Error. Input is not integer number. Please, try again" << endl;
            return 1;
        }


        if (number <= 0)
        {
            cerr << "Error. Numbers cannot be less or equal to 0!" << endl;
            return 1;
        }

        if(sizeOfStreet > 0)
            input.push_back(number);
        else
            sizeOfStreet = number;
    }

    for(int i = 0; i < input.size(); i++)
    {
        if (input[i] > sizeOfStreet)
        {
            cerr << "Error. Points is not available in that field" << endl;
            return 1;
        }
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

    sort(input.begin(), input.end());
    uint64_t var = ceil(double(input.size()) / 2) ;

    for(int i = 0; i < var; i++)
    {
        steps += mover->moveTo(input.at(input.size() - 1 - i));
        steps += mover->moveTo(input.at(i));
    }

    steps += mover->moveTo(mover->sizeOfStreet());

    cout << steps << endl;

    return 0;
}
