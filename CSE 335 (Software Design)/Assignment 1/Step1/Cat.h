/**
 * \file Cat.h
 *
 * \author Aidan Delfuoco
 *
 * Declaration of the CCat class.
 */

#pragma once
#include <string>
#include "Animal.h"

 /**
  * Class that describes a cat.
  */
class CCat : public CAnimal
{
public:
	enum class Type { AmericanShorthair, Persian, Siamese, Sphynx };
	void ObtainCatInformation();
	void DisplayAnimal();
	virtual bool IsHairy();

private:
	/// The cat's name
	std::string mName;

	/// The breed of cat: AmericanShorthair, Persian, Siamese, Sphynx
	Type mType = Type::Sphynx;
};

