#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#define CROMOSOME_SIZE 12

#include <string>

using namespace std;

class Individual
{
    bool cromosome[CROMOSOME_SIZE];
public:
    Individual();
    bool getGen(int index);
    void setGen(int index, bool value);
    string toString();
};

#endif // INDIVIDUAL_H
