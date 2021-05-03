/**
 * \file Farm.h
 *
 * \author Aidan Delfuoco
 *
 * Class that describes a Farm.
 *
 * This class holds a collection of animals that make
 * up the inventory of a farm.
 */

#pragma once
#include <vector>
#include "Cow.h"

/**
 * Class that describes a farm.
 * 
 * Holds a collection of animals that make up the farm 
 * inventory.
 */
class CFarm
{
public:
    void AddAnimal(CAnimal* animal);
    void DisplayInventory();
    int CountHairyAnimals();
    ~CFarm();

private:
    /// A list with the inventory of all animals on the farm
    std::vector<CAnimal*> mInventory;
};

