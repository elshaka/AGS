#include "ags.h"
#include "tester.h"

int main()
{

    Population pop;
    AGS ags;

    pop.randomize();
    ags.evolve(pop, true, true);

    //Tester::run();

    return 0;
}
