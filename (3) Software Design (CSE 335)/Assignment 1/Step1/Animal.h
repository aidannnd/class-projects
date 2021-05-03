/**
 * \file Animal.h
 *
 * \author Aidan Delfuoco
 *
 * Declaration of the CAnimal class.
 */

#pragma once

 /**
  * Class that describes an animal.
  */
class CAnimal
{
public:
	virtual ~CAnimal();
	/** Display an animal. */
	virtual void DisplayAnimal() {}
	virtual bool IsHairy();
};

