#include <iostream>
#include "individual.h"
#include "population.h"

using namespace std;

int main()
{
    /*
    AGS ags;
    Population pop;
    pop = ags.evolve(pop);
    cout << pop->getFittest().toString() << endl;
    */
    Population pop;
    cout << pop.getFittest().toString() << endl;

    return 0;
}
