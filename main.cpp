#include <iostream>
#include "individual.h"

using namespace std;

int main()
{
    Individual i;
    i.chromosome = 0b111111000000;
    cout << i.chromosome << endl;
    cout << i.x() << endl;
    cout << i.y() << endl;
    return 0;
}
