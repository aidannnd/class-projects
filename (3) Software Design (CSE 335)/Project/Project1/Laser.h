/**
 * \file Laser.h
 *
 * \author Ryan Piotrowicz
 *
 * Class for a Laser
 */

#pragma once
#include "Projectile.h"

 /**
  * Class for a Laser
  */
class CLaser : public CProjectile
{
public:
	/// Default constructor (disabled)
	CLaser() = delete;

	CLaser(CGame* game);

	/** Accept a visitor
	 * \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitLaser(this); }

};

