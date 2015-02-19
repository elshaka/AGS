#ifndef PARAMETERS_H
#define PARAMETERS_H

#define UB 10
#define LB -10
#define CHROMOSOME_SIZE 64
#define POPULATION_SIZE 10
#define CROSS_RATIO 0.75
#define MUTATION_RATIO 0.001
#define GENERATIONS 20

#define MASK ((unsigned long long) pow(2, CHROMOSOME_SIZE / 2) - 1)

#endif // PARAMETERS_H
