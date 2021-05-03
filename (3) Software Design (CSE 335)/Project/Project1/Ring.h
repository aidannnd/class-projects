/**
 * \file Ring.h
 *
 * \author Ryan Piotrowicz
 *
 * Class for expanding ring created by CTowerRing
 */

#pragma once
#include "Game.h"
#include "Item.h"


/**
 * Class for expanding ring created by CTowerRing
 */
class CRing : public CItem
{
public:
	CRing() = delete;

	CRing(CGame* game);

	/** Set the radius of Ring
	 * \param r Radius to be set to
	 */
	void SetRadius(int r) { mRadius = r; }

	/** Set the speed of expansion
	 * \param s Speed to be set to (pixels/second)
	 */
	void SetSpeed(int s) { mSpeed = s; }

	void Update(double elapsed);

	void Draw(Gdiplus::Graphics* graphics);

	/** Accept a visitor
	 * \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitRing(this); }

private:
	/// Radius of Ring
	int mRadius = 10;

	/// Speed the ring expands at
	double mSpeed = 0;
};

