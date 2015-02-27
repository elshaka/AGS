#ifndef AGS_H
#define AGS_H

#include "parameters.h"
#include "population.h"
#include <random>
#include <ncurses.h>
#include <unistd.h>
#include <fstream>

using namespace std;

class AGS
{
    friend class Tester;
public:
    AGS();
    void evolve(Population &pop, bool show = true, bool log = true);
private:
    int g;
    double fitnesses[POPULATION_SIZE];
    double total_fitnesses;
    double min_fitness;
    double best_fitness;
    Individual best_individual;
    double chiasma;
    void evaluate(Population &pop);
    void normalize();
    int select();
    Individual crossover(Individual &parent1, Individual &parent2);
    void mutate(Population &pop);
    void show_generation(Population &pop);
    double average_best();
    double average_pop();

    double sum_best;
    double sum_pop;
    double offline_performance[GENERATIONS];
    double online_performance[GENERATIONS];
    ofstream offline_stream;
    ofstream online_stream;
    ofstream log_stream;

    mt19937 *random_gen;
    uniform_real_distribution<double> *roulette_dist;
    bernoulli_distribution *crossover_dist;
    uniform_int_distribution<int> *chiasma_dist;
    uniform_int_distribution<int> *population_dist;
    bernoulli_distribution *mutation_dist;
};

#endif // AGS_H
