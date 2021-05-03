/**
 * \file Balloon.h
 *
 * \author Aidan Delfuoco
 *
 * Base class for a balloon
 */

#pragma once
#include "Item.h"
#include <memory>
#include <string>
#include "Game.h"
#include "ItemVisitor.h"

class CItemVisitor;
class CGame;

/**
 * Class for a balloon
 */
class CBalloon : public CItem
{
public:
	CBalloon() = delete;

	/// Hit getter
	/// \returns mHit
	bool GetHit() const { return mHit; }

	/// Hit setter
	/// \param hit Hit bool
	void SetHit(bool hit) { mHit = hit; }

	/// Set speed
	/// \param s Speed
	void SetSpeed(double s) { mSpeed = s; }

	void Update(double elapsed);

	CBalloon(CGame* game, const std::wstring& filename);

	/// <summary>
	/// Identifies the type of object, which is a balloon
	/// </summary>
	/// <returns> string with the type of object</returns>
	std::string GetType() { return mType; }

	/// Changes set by
	/// \param x string changing
	void ChangeSetBy(std::string x) { mSetBy = x; }
	
	/// Reinitializes
	void Reinitialize() { mXMultiplier = 0; mYMultiplier = 0; mSetBy = "right or down"; }

	/// <summary>
	/// checks if balloon updated the score
	/// </summary>
	/// <returns> boolean flag with true if updated, false otherwise </returns>
	bool ScoreUpdatedByBalloon() { return mScoreUpdated; }

	/** Accept a visitor
	 * \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitBalloon(this); }

	///  Gets hit status
	/// \returns mHit
	bool GetHitStatus() { return mHit; }

	///  Sets mHit to true
	void BalloonHit() { mHit = true; }

private:
	/// Speed of the balloon
	double mSpeed;

	/// If the balloon has been hit or not
	bool mHit = false;
	
	/// Image of the balloon
	std::unique_ptr<Gdiplus::Bitmap> mBalloonImage;

	/// identifies object
	std::string mType = "Balloon";

	/// mX multiplier
	int mXMultiplier = 0;

	/// mY multiplier
	int mYMultiplier = 0;

	/// string variable to keep track of 'set by'
	std::string mSetBy = "right or down";

	/// boolean flag determining whether score was updated or not
	bool mScoreUpdated = false;
};