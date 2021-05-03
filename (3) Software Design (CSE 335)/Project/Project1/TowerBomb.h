/**
 * \file TowerBomb.h
 *
 * \author Ryan Piotrowicz
 *
 * Class for a tower that explodes
 */

#pragma once
#include <memory>
#include "Tower.h"
#include "Explosion.h"

 /**
  * Class for a tower that explodes
  */
class CTowerBomb : public CTower
{
public:
	/// Default constructor (disabled)
	CTowerBomb() = delete;

	CTowerBomb(CGame* game, int bombNum);

	bool HitTest(double x, double y);
	
	/// Gets type
	/// \returns mType
	std::string GetType() { return mType; }

	void Attack();

	/** Accept a visitor
	 * \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTowerBomb(this); }


private:
	/// Image of the tower
	std::unique_ptr<Gdiplus::Bitmap> mTowerImage;

	/// Type of tower
	std::string mType = "Bomb";

};

