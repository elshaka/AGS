#ifndef PARAMETERS_H
#define PARAMETERS_H

#define LB -5
#define UB 5
#define CHROMOSOME_SIZE 25
#define POPULATION_SIZE 50
#define CROSSOVER_RATE 0.75
#define MUTATION_RATE 0.01
#define GENERATIONS 50

#define MASK ((unsigned long long) pow(2, CHROMOSOME_SIZE / 2) - 1)
#define SHOW_DELAY 0

#endif // PARAMETERS_H
