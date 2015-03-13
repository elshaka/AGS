#ifndef PARAMETERS_H
#define PARAMETERS_H

#define LB -5
#define UB 5
#define CHROMOSOME_SIZE 28
#define POPULATION_SIZE 200
#define CROSSOVER_RATE 0.75
#define MUTATION_RATE 0.001
#define GENERATIONS 100

#define GRAY_ENABLED true
#define ELITISM_ENABLED false
#define ELITISM_SIZE 10
#define TOURNAMENT_SIZE 5

#define MASK ((unsigned long long) pow(2, CHROMOSOME_SIZE / 2) - 1)
#define SHOW_DELAY 0

#endif // PARAMETERS_H
