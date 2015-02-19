#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <bitset>
#include <cmath>
#include <string>
#include <sstream>
#include "parameters.h"

using namespace std;

class Individual
{
public:
    Individual();
    bitset<CHROMOSOME_SIZE> chromosome;
    double x();
    double y();
    double fitness();
    string toString();
private:
    double decode(unsigned long long value);
    double function(double x, double y);
};

#endif // INDIVIDUAL_H
