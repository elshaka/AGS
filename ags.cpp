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
}

void AGS::evolve(Population &pop, bool show, bool log)
{
    sum_best = 0;
    sum_pop = 0;
    best_g = 1;
    best_individual = pop.individuals[0];
    best_fitness = best_individual.fitness();

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

        // Codificar gray
        if(GRAY_ENABLED)
            encodeGray(pop);

        // Seleccionar y cruzar
        Population old_pop = pop;
        for(int i = 0; i < POPULATION_SIZE - 1; i += 2)
        {
            // Seleccionar
            int p1_i = selectTournament();
            int p2_i = selectTournament();

            // Cruzar
            if((*crossover_dist)(*random_gen))
            {
                pop.individuals[i] = crossover(old_pop.individuals[p1_i], old_pop.individuals[p2_i]);
                pop.individuals[i + 1] = crossover(old_pop.individuals[p2_i], old_pop.individuals[p1_i]);
            }
            else
            {
                pop.individuals[i] = old_pop.individuals[p1_i];
                pop.individuals[i + 1] = old_pop.individuals[p2_i];
            }
        }

        // Mutar
        mutate(pop);

        // Elitismo
        if(ELITISM_ENABLED)
        {
            sort(indexedFitnesses.begin(), indexedFitnesses.end());
            for(int i = 0; i < ELITISM_SIZE; ++i)
                pop.individuals[i] = old_pop.individuals[indexedFitnesses[i].index];
        }

        // Decodificar gray
        if(GRAY_ENABLED)
            decodeGray(pop);
    }

    if(show)
    {
        printw("Presione cualquier tecla para salir (Revisar log.txt para historial de resultados)");
        getch();
        endwin();
    }

    if(log)
    {
        online_stream.close();
        offline_stream.close();
        log_stream.open("log.txt", ios::out | ios::app);
        log_stream << "Mejor adaptabilidad "
                   << best_individual.toString()
                   << " = "
                   << best_fitness
                   << endl
                   << "\tParametros: CHROMOSOME_SIZE = "
                   << CHROMOSOME_SIZE << ", POPULATION_SIZE = "
                   << POPULATION_SIZE << ", GENERATIONS = "
                   << GENERATIONS << ", CROSSOVER_RATE = "
                   << CROSSOVER_RATE << ", MUTATION_RATE = "
                   << MUTATION_RATE << endl;
        log_stream.close();
    }

}

void AGS::evaluate(Population &pop)
{
    int best_i = 0;
    min_fitness = pop.individuals[0].fitness();
    total_fitnesses = 0;

    if(ELITISM_ENABLED)
        indexedFitnesses.clear();

    for(int i = 0; i < POPULATION_SIZE; ++i)
    {
        fitnesses[i] = pop.individuals[i].fitness();

        if(ELITISM_ENABLED)
            indexedFitnesses.push_back(IndexedFitness(i, fitnesses[i]));

        if(fitnesses[i] < min_fitness)
        {
            min_fitness = fitnesses[i];
            best_i = i;
        }
        total_fitnesses += fitnesses[i];
    }

    if(min_fitness < best_fitness)
    {
        best_fitness = min_fitness;
        best_individual = pop.individuals[best_i];
        best_g = g;
    }
}

void AGS::normalize()
{
    total_fitnesses = 0;
    double offset = min_fitness <= 0 ? abs(min_fitness) + DBL_MIN : 0;
    for(int i = 0; i < POPULATION_SIZE; ++i)
    {
        fitnesses[i] += offset;
        fitnesses[i] = min_fitness / fitnesses[i];
        total_fitnesses += fitnesses[i];
    }
}

int AGS::selectRoulette()
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

int AGS::selectTournament()
{
    int k = (*population_dist)(*random_gen);
    int winner_i = k;
    double winnerFitness = fitnesses[k];

    for(int i = 1; i < TOURNAMENT_SIZE; ++i)
    {
        k = (*population_dist)(*random_gen);
        if(fitnesses[k] < winnerFitness)
        {
            winner_i = k;
            winnerFitness = fitnesses[k];
        }
    }

    return winner_i;
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

void AGS::encodeGray(Population &pop)
{
    Individual *individual;
    for(int i = 0; i < POPULATION_SIZE; ++i)
    {
        individual = &(pop.individuals[i]);
        individual->chromosome ^= (individual->chromosome >> 1);
    }
}

void AGS::decodeGray(Population &pop)
{
    Individual *individual;
    unsigned long long value;
    for(int i = 0; i < POPULATION_SIZE; ++i)
    {
        individual = &(pop.individuals[i]);
        value = individual->chromosome.to_ullong();
        for(unsigned long long mask = value >> 1; mask != 0; mask = mask >> 1)
            value ^= mask;
        individual->chromosome = value;
    }
}

void AGS::show_generation(Population &pop)
{
    move(0, 0);
    printw("Generacion: %d\n", g);
    printw("Mejor adaptabilidad (Generacion %d): %s = %f\n", best_g, best_individual.toString().c_str(), best_fitness);
    printw(pop.toString().c_str());
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
