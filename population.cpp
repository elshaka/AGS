#include "population.h"

Population::Population(bool initialize)
{
    if (initialize)
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<unsigned long long> dis(0, (unsigned long long) pow(2, CHROMOSOME_SIZE) - 1);

        for(int i = 0; i < POPULATION_SIZE; ++i)
            individuals[i].chromosome = dis(gen);
    }
}

Individual Population::getFittest()
{
    int best_i = 0;
    double best = individuals[best_i].fitness();

    for(int i = 1; i < POPULATION_SIZE; ++i)
    {
        double fitness = individuals[i].fitness();
        if(fitness > best)
        {
            best = fitness;
            best_i = i;
        }
    }
    return individuals[best_i];
}
