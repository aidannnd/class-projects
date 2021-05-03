/**
 * \file TowerCustom.h
 *
 * \author Aidan Delfuoco
 *
 * Class for a custom tower
 */

#pragma once
#include "Tower.h"
#include "Laser.h"

 /**
  * Class for a tower that creates sparty attack
  */
class CTowerCustom : public CTower
{
public:
	/// Default constructor (disabled)
	CTowerCustom() = delete;

	CTowerCustom(CGame* game);

	bool HitTest(double x, double y);
	
	/// Gets type
	/// \returns mType
	std::string GetType() { return mType; }

	/// Attack class
	void Attack();

	/** Accept a visitor
	 * \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTowerCustom(this); }


private:
	/// Image of the tower
	std::unique_ptr<Gdiplus::Bitmap> mTowerImage;

	/// Type of tower
	std::string mType = "Custom";

};

