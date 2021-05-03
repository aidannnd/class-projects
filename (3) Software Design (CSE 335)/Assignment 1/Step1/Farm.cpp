/**
 * \file Farm.cpp
 *
 * \author Aidan Delfuoco
 */

#include "Farm.h"
#include "leak.h"
#include "Animal.h"

/** Add an animal to the farm inventory.
 *
 * \param animal the animal to add to the inventory
 */
void CFarm::AddAnimal(CAnimal* animal)
{
    mInventory.push_back(animal);
}

/**
 * Display the farm inventory.
 */
void CFarm::DisplayInventory()
{
    for (auto animal : mInventory)
    {
        animal->DisplayAnimal();
    }
}

/**
 * Counts hairy animals in the farm inventory
 * \return number of hairy animals
 */
int CFarm::CountHairyAnimals()
{
    int hairyAnimalsCount = 0;
    for (auto animal : mInventory)
    {
        if (animal->IsHairy())
        {
            hairyAnimalsCount++;
        }
    }

    return hairyAnimalsCount;
}

/**
 * CFarm destructor
 */
CFarm::~CFarm()
{
    // Iterate over all of the animals, destroying 
    // each one.
    for (auto animal : mInventory)
    {
        delete animal;
    }

    // And clear the list
    mInventory.clear();
}