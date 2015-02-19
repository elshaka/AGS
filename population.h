#ifndef POPULATION_H
#define POPULATION_H

#define POPULATION_SIZE 10

#include "individual.h"

class Population
{
    Individual *individuals[POPULATION_SIZE];
public:
    Population();
};

#endif // POPULATION_H
