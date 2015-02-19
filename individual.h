#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <bitset>
#include <cmath>

#define UB 10
#define LB -10
#define CHROMOSOME_SIZE 12
#define MASK ((unsigned long long) pow(2, CHROMOSOME_SIZE / 2) - 1)

using namespace std;

class Individual
{
public:
    Individual();
    bitset<CHROMOSOME_SIZE> chromosome;
    double x();
    double y();
    double fitness();
private:
    double decode(unsigned long long value);
    double function(double x, double y);
};

#endif // INDIVIDUAL_H
