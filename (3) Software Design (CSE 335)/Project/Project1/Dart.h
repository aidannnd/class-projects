/**
 * \file Dart.h
 *
 * \author Ryan Piotrowicz
 *
 * Class for a dart
 */

#pragma once
#include "Projectile.h"

/**
 * Class for a dart
 */
class CDart : public CProjectile
{
public:
	/// Default constructor (disabled)
	CDart() = delete;

	CDart(CGame* game);

	/** Accept a visitor
	 * \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitDart(this); }

};

