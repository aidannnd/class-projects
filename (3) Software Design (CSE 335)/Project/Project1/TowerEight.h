/**
 * \file TowerEight.h
 *
 * \author Ryan Piotrowicz
 *
 * Class for tower that shoots eight darts
 */

#pragma once
#include <string>
#include "Tower.h"
#include "Dart.h"

/**
 * Class for a tower that shoots eight darts
 */
class CTowerEight : public CTower
{
public:
	/// Default constructor (disabled)
	CTowerEight() = delete;

	CTowerEight(CGame* game);

	bool HitTest(double x, double y);
	
	/// Gets type
	/// \returns mType
	std::string GetType() { return mType; }

	void Attack();

	/** Accept a visitor
	 * \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTowerEight(this); }


private:
	/// Image of the tower
	std::unique_ptr<Gdiplus::Bitmap> mTowerImage;

	/// Type of tower
	std::string mType = "Eight";

};

