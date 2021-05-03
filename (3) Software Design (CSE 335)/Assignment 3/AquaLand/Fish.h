/**
 * \file Fish.h
 *
 * \author Aidan Delfuoco
 *
 * Class that represents a fish.
 */

#pragma once
#include "Item.h"

/**
 * Base class for a fish
 * This applies to all of the fish, but not the decor
 * items in the aquarium.
 */
class CFish : public CItem
{
public:
	/// Default constructor (disabled)
	CFish() = delete;

	/// Copy constructor (disabled)
	CFish(const CFish&) = delete;

	void CFish::Update(double elapsed);

protected:
	CFish::CFish(CAquarium* aquarium, const std::wstring& filename);
		

private:
	/// Fish speed in the X direction
	double mSpeedX;

	/// Fish speed in the Y direction
	double mSpeedY;
};