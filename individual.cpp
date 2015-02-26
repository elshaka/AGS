#include "individual.h"

Individual::Individual(unsigned long long value)
{
    chromosome = value;
}

double Individual::function(double x, double y)
{
    double x2 = x * x;
    double x4 = x2 * x2;
    double x6 = x4 * x2;
    double y2 = y * y;
    double y4 = y2 * y2;
    return 4 * x2 - 2.1 * x4 + x6 / 3 +  x * y - 4 * y2 + 4 * y4;
}

string Individual::toString()
{
    ostringstream out;
    out << "(" << x() << ", " << y() << ")";
    return out.str();
}

double Individual::x()
{
    return decode((chromosome >> CHROMOSOME_SIZE / 2).to_ullong());
}

double Individual::y()
{
    return decode((chromosome & (bitset<CHROMOSOME_SIZE>) MASK).to_ullong());
}

double Individual::decode(unsigned long long value)
{
    return LB + (UB - LB) / (double) MASK * value;
}

double Individual::fitness()
{
    return function(x(), y());
}
