#include "population.h"

Population::Population()
{
}

Individual Population::getFittest()
{
    int best_i = 0;
    double best = individuals[0].fitness();

    for(int i = 1; i < POPULATION_SIZE; ++i)
    {
        double fitness = individuals[i].fitness();
        if(fitness < best)
        {
            best = fitness;
            best_i = i;
        }
    }

    return individuals[best_i];
}

void Population::randomize()
{
    random_device random_dev;
    mt19937 random_gen(random_dev());
    uniform_int_distribution<unsigned long long> dis(0, (unsigned long long) pow(2, CHROMOSOME_SIZE) - 1);

    for(int i = 0; i < POPULATION_SIZE; ++i)
        individuals[i].chromosome = dis(random_gen);
}

string Population::toString()
{
    ostringstream out;
    for(int i = 0; i < POPULATION_SIZE; ++i)
        out << individuals[i].chromosome << " (" << individuals[i].fitness() << ")" << endl;
    return out.str();
}
