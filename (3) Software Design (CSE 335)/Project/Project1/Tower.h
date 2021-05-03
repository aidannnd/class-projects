/**
 * \file Tower.h
 *
 * \author Ryan Piotrowicz
 *
 * Base class for a tower object
 */

#pragma once
#include "Game.h"
#include "Item.h"

#include <memory>
#include <string>


/**
 * Base class for a tower object
 */
class CTower : public CItem
{
public:
	/// Default constructor (disabled)
	CTower() = delete;

	void SetAttackTimer(double t);
	
	/// Gets Attack Timer
	/// \returns mAttackTimer
	double GetAttackTimer() { return mAttackTimer; }

	/// Gets mTimeUntilAttack
	/// \returns mTimeUntilAttack
	double GetTimeUntilAttack() { return mTimeUntilAttack; }

	/// Tower attack function
	virtual void Attack() {};

	void Update(double elapsed);

	/** Test this item to see if it has been clicked on
	 * \param x X location on the game to test
	 * \param y Y location on the game to test
	 * \return true if clicked on */
	virtual bool HitTest(double x, double y) { return false; }

	/// Gets type
	/// \returns type
	virtual std::string GetType() { return ""; }

protected:
	CTower(CGame* game, const std::wstring& filename);

private:
	/// Attack Timer in seconds between attack
	double mAttackTimer = 0;

	/// Running timer between each attack
	double mTimeUntilAttack = 0;

	/// Game
	CGame* mGame;

};
