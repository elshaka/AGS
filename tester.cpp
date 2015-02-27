#include "tester.h"

using namespace std;

Tester::Tester()
{

}

void Tester::run()
{
    if(TEST_ROULETE)
    {
        cout << "### Probando ruleta " << ROULETTE_TRIES << " veces" << endl;
        AGS ags;
        ags.total_fitnesses = 0;
        int times_selected[POPULATION_SIZE];

        for(int i = 0; i < POPULATION_SIZE; ++i)
        {
            ags.fitnesses[i] = (*ags.chiasma_dist)(*ags.random_gen);
            ags.total_fitnesses += ags.fitnesses[i];
            times_selected[i] = 0;
        }

        for(int i = 0; i < ROULETTE_TRIES; ++i)
            times_selected[ags.select()] += 1;

        for(int i = 0; i < POPULATION_SIZE; ++i)
            cout << "Adaptabilidad: " << ags.fitnesses[i]  << ", Seleccion "<< (double) times_selected[i] / ROULETTE_TRIES * 100 << "% (" << ags.fitnesses[i] / ags.total_fitnesses * 100 << "%)\n";
    }

    if(TEST_INDIVIDUAL)
    {
        cout << "###Probando funcion de adaptabilidad\n";
        Individual i;
        cout << "Adaptabilidad para (-0.089842, 0.712656): " << i.function(-0.089842, 0.712656) << " (-1.03163)\n";
        cout << "Adaptabilidad para (1.23023, 0.162335): " << i.function(1.23023, 0.162335) << " (2.4963)\n";

        cout << "Fenotipo para cromosoma 111111000000\n";
        i.chromosome = 0b111111000000;
        cout << i.toString() << " = (5, -5)\n";
        cout << "Fenotipo para cromosoma 000000111111\n";
        i.chromosome = 0b000000111111;
        cout << i.toString() << " = (-5, 5)\n";
    }

    if(TEST_CROSSOVER)
    {
        cout << "###Probando crossover\n";
        AGS ags;
        Individual i1, i2;
        i1.chromosome = 0b111111111111;
        i2.chromosome = 0b000000000000;
        cout << "I1: " << i1.chromosome << "\n";
        cout << "I2: " << i2.chromosome << "\n";
        for(int i = 0; i < CROSSOVER_TRIES; ++i)
        {
            Individual i3 = ags.crossover(i1, i2);
            cout << "Quiasma " << ags.chiasma << ": \n";
            cout << "I1 & I2: " << i3.chromosome << "\n";
        }
    }

    if(TEST_POPULATION_COPY)
    {
        Population original_pop;
        original_pop.randomize();
        Population copy_pop(original_pop);
        copy_pop.individuals[0] = 0;
        cout << "Población original" << endl;
        cout << original_pop.toString() << endl;
        cout << "Población copia (primer individuo fijado a 0" << endl;
        cout << copy_pop.toString() << endl;
    }
}
