/**
 * \file Item.h
 *
 * \author Ryan Piotrowicz
 *
 * Base class for all items
 */

#pragma once

#include <string>
#include <memory>
#include "ItemVisitor.h"

class CGame;
class CItemVisitor;

/**
 * Class for an item
 */
class CItem : public std::enable_shared_from_this<CItem>
{
public:
	/// Destructor
	virtual ~CItem() {};

	/// Default constructor (deleted)
	CItem() = delete;

	/** The X location of the item
	 * \returns X location in pixels */
	double GetX() const { return mPositionX; }

	/** The Y location of the item
	 * \returns Y location in pixels */
	double GetY() const { return mPositionY; }

	virtual void SetLocation(double x, double y);

	/** Draw this item
	 * \param graphics Graphics device to draw on */
	virtual void Draw(Gdiplus::Graphics* graphics);

	/// Handle updates for animation
	/// \param elapsed The time since the last update
	virtual void Update(double elapsed) {}

	/// Hit test
	/// \param x X coord
	/// \param y Y coord
	/// \return false
	virtual bool HitTest(double x, double y) { return false; }

	/** The type of the item
	 * \returns empty string */
	virtual std::string GetType() { return ""; }

	/** The game this item belongs to
	 * \returns Game pointer */
	CGame* GetGame() { return mGame; }

	/// Moves tower
	/// \param tower Tower
	/// \returns bool
	virtual bool MoveTower(std::shared_ptr<CItem> tower) { return false; }

	///  Sets the road ahead of this one
	/// \param next Next item
	virtual void SetNext(std::shared_ptr<CItem> next) {}

	///  Gets mType
	/// \returns type
	virtual std::wstring GetRoadType() { return L""; }

	/// <summary>
	/// checks if balloon updated the score
	/// </summary>
	/// <returns> boolean flag with true if updated, false otherwise </returns>
	virtual bool ScoreUpdatedByBalloon() { return false; }

	/** Accept a visitor
	 * \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor* visitor) = 0;

	///  Gets hit status
	/// \returns bool
	virtual bool GetHitStatus() { return false; }

	///  Overrides BallonHit
	virtual void BalloonHit() {}


protected:
	CItem(CGame* game, const std::wstring& filename);

private:
	/// The X position of the item
	double mPositionX = 0;

	/// The Y position of the item
	double mPositionY = 0;

	/// Image of the item
	std::unique_ptr<Gdiplus::Bitmap> mItemImage;

	/// The game this item belongs to
	CGame* mGame;

	
};

