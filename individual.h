#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "parameters.h"
#include <bitset>
#include <cmath>
#include <sstream>

using namespace std;

class Individual
{
    friend class Tester;
public:
    Individual(unsigned long long value = 0);
    bitset<CHROMOSOME_SIZE> chromosome;
    double x();
    double y();
    double fitness();
    string toString();
private:
    static double decode(unsigned long long value);
    static double function(double x, double y);
};

#endif // INDIVIDUAL_H
