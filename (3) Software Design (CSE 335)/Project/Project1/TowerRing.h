/**
 * \file TowerRing.h
 *
 * \author Ryan Piotrowicz
 *
 * Class for tower that creates an expanding ring
 */

#pragma once

#include <memory>
#include "Tower.h"
#include "Ring.h"

 /**
  * Class for a tower that creates an expanding ring
  */
class CTowerRing : public CTower
{
public:
	/// Default constructor (disabled)
	CTowerRing() = delete;

	CTowerRing(CGame* game);

	bool HitTest(double x, double y) override final;

	/// Gets type
	/// \returns mType
	std::string GetType() { return mType; }

	void Attack();

	/** Accept a visitor
	 * \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTowerRing(this); }


private:
	/// Image of the tower
	std::unique_ptr<Gdiplus::Bitmap> mTowerImage;

	/// identifies object
	std::string mType = "Ring";
};

