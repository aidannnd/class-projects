/**
 * \file Projectile.h
 *
 * \author Ryan Piotrowicz
 *
 * Base class for a projectile shot from a tower
 */

#pragma once
#include "Game.h"
#include "PanelScore.h"
#include "Item.h"

#include <memory>
#include <string>


/**
 * Base class for a projectile shot from a tower
 */
class CProjectile : public CItem
{
public:
	/// Default constructor (disabled)
	CProjectile() = delete;

	/** The angle of the projectile
	* \returns angle of the projectile in radians */
	double GetAngle() const { return mAngle;  }

	/** The speed of the projectile
	* \returns speed of the projectile in virtual pixels per second */
	double GetSpeed() const { return mSpeed; }

	/** The max range of the projectile
	* \returns the max range of the projectile in pixels */
	double GetMaxRange() const { return mMaxRange; }

	/** Set the speed of the projectile
	* \param s Speed in virtual pixels per second
	*/
	void SetSpeed(double s) { mSpeed = s; }

	/** Set the angle of the projectile
	* \param a Angle to be set to in radians
	*/
	void SetAngle(double a) { mAngle = a; }

	/** Set the max range of the projectile
	* \param r The range to be set to
	*/
	void SetMaxRange(double r) { mMaxRange = r; }

	/// <summary>
	/// Set the score, enabling projectile the ability to change score
	/// </summary>
	/// <param name="score"> score object </param>
	void SetScore(CPanelScore score) { mScore = score; }

	/// Updates
	/// \param elapsed The time since the last update
	void Update(double elapsed);

	void Draw(Gdiplus::Graphics* graphics) override;

	void ProjectileDraw(Gdiplus::Graphics* graphics, int offsetX, int offsetY);

protected:
	CProjectile(CGame* game, const std::wstring& filename);

private:

	/// The angle of the projectile
	double mAngle = 0;

	/// The speed of the projectile in virtual pixels per second
	double mSpeed = 0;

	/// The distance traveled from spawn point
	double mDistanceTraveled = 0;

	/// The max range a projectile can travel
	double mMaxRange = 0;

	/// Image of the projectile
	std::unique_ptr<Gdiplus::Bitmap> mProjectileImage;

	/// score of the game
	CPanelScore mScore;
};

