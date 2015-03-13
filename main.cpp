#include "ags.h"

int main()
{
    Population pop;
    AGS ags;

    pop.randomize();
    ags.evolve(pop);

    return 0;
}
