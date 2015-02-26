#ifndef POPULATION_H
#define POPULATION_H

#include "individual.h"
#include <cmath>
#include <random>

using namespace std;

class Population
{
public:
    Population();
    Individual individuals[POPULATION_SIZE];
    Individual getFittest();
    string toString();
    void randomize();
};

#endif // POPULATION_H
