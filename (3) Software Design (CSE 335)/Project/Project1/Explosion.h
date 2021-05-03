/**
 * \file Explosion.h
 *
 * \author Ryan Piotrowicz
 *
 * Class for the explosion created by CTowerBomb
 */

#pragma once
#include "Game.h"
#include "Item.h"

/**
 * Class for the explosion created by CTowerBomb
 */
class CExplosion : public CItem
{
public:
	CExplosion() = delete;

	CExplosion(CGame* game);

	/** Set the radius of explosion
	 * \param r Radius to be set to
	 */
	void SetRadius(int r) { mRadius = r; }

	/** Set the timer for smoke cloud length
	 * \param t Time to be set to (seconds)
	 */
	void SetTimer(int t) { mTimer = t; }

	/// Handle updates for animation
	/// \param elapsed The time since the last update
	void Update(double elapsed);

	/// Handle drawing
	/// \param graphics Graphics
	void Draw(Gdiplus::Graphics* graphics);

	/** Accept a visitor
	 * \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitExplosion(this); }


private:
	/// Radius of explosion
	int mRadius = 0;

	/// Length of time the cloud lasts in seconds
	double mTimer = 0;
};

