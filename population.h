#ifndef POPULATION_H
#define POPULATION_H

#include "individual.h"
#include <random>
#include <cmath>

using namespace std;

class Population
{
public:
    Population(bool initialize = true);
    Individual individuals[POPULATION_SIZE];
    Individual getFittest();
};

#endif // POPULATION_H
