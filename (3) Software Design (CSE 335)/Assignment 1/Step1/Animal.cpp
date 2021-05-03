/**
 * \file Chicken.h
 *
 * \author Aidan Delfuoco
 *
 * Declaration of the CAnimal class.
 */

#include "Animal.h"
#include "Cat.h"

/**
 * Destructor
 */
CAnimal::~CAnimal()
{
}

/** 
 * Checks if the animal is hairy.
 * \return false
 */
bool CAnimal::IsHairy()
{
	return false;
}