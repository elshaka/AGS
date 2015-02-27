#ifndef TESTER_H
#define TESTER_H

#include "ags.h"
#include <iostream>

#define TEST_ROULETE false
#define TEST_INDIVIDUAL false
#define TEST_CROSSOVER false
#define TEST_EVALUATION false
#define TEST_POPULATION_COPY true

#define ROULETTE_TRIES 10000000
#define CROSSOVER_TRIES 5

class Tester
{
public:
    Tester();
    static void run();
};

#endif // TESTER_H
