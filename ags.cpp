#include "ags.h"

AGS::AGS()
{
    random_device random_dev;
    random_gen = new mt19937(random_dev());
    roulette_dist = new uniform_real_distribution<double>(0, 1);
    crossover_dist = new bernoulli_distribution(CROSSOVER_RATE);
    chiasma_dist = new uniform_int_distribution<int>(0, CHROMOSOME_SIZE);
    population_dist = new uniform_int_distribution<int>(0, POPULATION_SIZE - 1);
    mutation_dist = new bernoulli_distribution(MUTATION_RATE);
    sum_best = 0;
    sum_pop = 0;
}

void AGS::evolve(Population &pop, bool show, bool log)
{
    if(show)
        initscr();

    if(log)
    {
        offline_stream.open("offline.dat", ios::out | ios::trunc);
        online_stream.open("online.dat", ios::out | ios::trunc);
    }

    for(g = 1; g <= GENERATIONS; ++g)
    {
        // Evaluar
        evaluate(pop);

        // Loggear
        if(log)
        {
            offline_stream << g << " " << average_best() << endl;
            online_stream << g << " " << average_pop() << endl;
        }

        // Mostrar
        if(show)
            show_generation(pop);

        // Normalizar
        normalize();

        // Seleccionar
        int p1_i = select();
        int p2_i = select();

        // Cruzar
        if((*crossover_dist)(*random_gen))
        {
            Individual child1 = crossover(pop.individuals[p1_i], pop.individuals[p2_i]);
            Individual child2 = crossover(pop.individuals[p2_i], pop.individuals[p1_i]);
            pop.individuals[(*population_dist)(*random_gen)] = child1;
            pop.individuals[(*population_dist)(*random_gen)] = child2;
        }

        // Mutar
        mutate(pop);
    }

    if(show)
    {
        printw("Presione cualquier tecla para salir\n");
        getch();
        endwin();
    }

    if(log)
    {
        online_stream.close();
        offline_stream.close();
    }

}

void AGS::evaluate(Population &pop)
{
    // Evaluar
    min_fitness = pop.individuals[0].fitness();
    total_fitnesses = 0;

    for(int i = 0; i < POPULATION_SIZE; ++i)
    {
        fitnesses[i] = pop.individuals[i].fitness();

        if(fitnesses[i] < min_fitness)
            min_fitness = fitnesses[i];

        total_fitnesses += fitnesses[i];
    }
}

void AGS::normalize()
{
    // Normalizar
    total_fitnesses = 0;
    double offset = min_fitness < 0 ? min_fitness : 0;
    for(int i = 0; i < POPULATION_SIZE; ++i)
    {
        fitnesses[i] -= offset;

        if(fitnesses[i] == 0)
            fitnesses[i] = 1;
        else
            fitnesses[i] = 1 / fitnesses[i];

        total_fitnesses += fitnesses[i];
    }
}

int AGS::select()
{
    int i = -1;
    double sum = 0;
    double rand = (*roulette_dist)(*random_gen);
    double push = rand * total_fitnesses;

    do
        sum += fitnesses[++i];
    while (!((sum >= push) || (i == POPULATION_SIZE - 1)));

    return i;
}

Individual AGS::crossover(Individual &parent1, Individual &parent2)
{
    Individual child;
    chiasma = (*chiasma_dist)(*random_gen);

    for(int i = 0; i < chiasma; ++i)
        child.chromosome[i] = parent1.chromosome[i];
    for(int i = chiasma; i < CHROMOSOME_SIZE; ++i)
        child.chromosome[i] = parent2.chromosome[i];
    return child;
}

void AGS::mutate(Population &pop)
{
    Individual *individual;
    for(int i = 0; i < POPULATION_SIZE; ++i) {
        individual = &(pop.individuals[i]);
        for(int j = 0; j < CHROMOSOME_SIZE; ++j)
          if((*mutation_dist)(*random_gen))
              individual->chromosome[j] = !individual->chromosome[j];
    }
}

void AGS::show_generation(Population &pop)
{
    move(0, 0);
    printw(pop.toString().c_str());
    printw("Generacion: %i\n", g);
    Individual best = pop.getFittest();
    printw("Mejor adaptabilidad: %s = %f\n", best.toString().c_str(), best.fitness());
    refresh();
    usleep(SHOW_DELAY);
}

double AGS::average_best()
{
    sum_best += min_fitness;
    return sum_best / g;
}

double AGS::average_pop()
{
    sum_pop += total_fitnesses / POPULATION_SIZE;
    return sum_pop / g;
}
