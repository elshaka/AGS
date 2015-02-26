#include "ags.h"
#include "tester.h"
#include <fstream>

int main()
{

    Population pop;
    AGS ags;

    pop.randomize();
    ags.evolve(pop, true, true);

    Individual fittest = pop.getFittest();

    ofstream log;
    log.open("log.txt", ios::out | ios::app);
    log << "f" << fittest.toString() << " = "<< fittest.fitness() << endl;
    log.close();
/*
    Tester::run();
*/
    return 0;
}
