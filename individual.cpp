#include "individual.h"

Individual::Individual()
{
}

double Individual::function(double x, double y)
{
    return 4 * x * x - 2.1 * x * x * x * x + 1 / 3 * x * x * x * x * x * x + x * y - 4 * y * y + 4 * y * y * y * y;
}

string Individual::toString()
{
    ostringstream out;
    out << "(" << x() << ", " << y() << ")";
    return out.str();
}

double Individual::x()
{
    return decode((chromosome & (bitset<CHROMOSOME_SIZE>) MASK).to_ullong());
}

double Individual::y()
{
    return decode((chromosome >> CHROMOSOME_SIZE / 2).to_ullong());
}

double Individual::decode(unsigned long long value)
{
    return LB + (UB - LB) / (double) MASK * value;
}

double Individual::fitness()
{
    return function(x(), y());
}

