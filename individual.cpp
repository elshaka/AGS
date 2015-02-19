#include "individual.h"

#include <string>

Individual::Individual()
{
}

bool Individual::getGen(int index)
{
    return cromosome[index];
}

void Individual::setGen(int index, bool value)
{
    cromosome[index] = value;
}

string Individual::toString()
{
    string s = "";
    for(int i = 0; i < CROMOSOME_SIZE; ++i)
        if(cromosome[i])
            s.append("1");
        else
            s.append("0");
    return s;
}
