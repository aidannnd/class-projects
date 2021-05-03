/**
 * \file Cow.h
 *
 * \author Aidan Delfuoco
 */

#pragma once
#include <string>
#include "Animal.h"

/**
 * Class that describes a cow.
 */
class CCow : public CAnimal
{
public:
	/// The types of cow we can have on our farm
	enum class Type { Bull, BeefCow, MilkCow };
    void ObtainCowInformation();
    void DisplayAnimal();
    virtual bool IsHairy();

private:
    /// The cow's name
    std::string mName;

    /// The type of cow: Bull, BeefCow, or MilkCow
    Type mType = Type::MilkCow;

    /// The milk production for a cow in gallons per day
    double mMilkProduction = 0;
};

