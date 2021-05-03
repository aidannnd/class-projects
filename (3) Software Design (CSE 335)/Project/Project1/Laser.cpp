/**
 * \file Laser.cpp
 *
 * \author Ryan Piotrowicz
 */

#include "pch.h"
#include "Laser.h"

 /// Laser filename
const std::wstring LaserImageName = L"images/laser.png";

/// Laser speed (virtual pixels per second)
const double LaserSpeed = 600;

/// Laser range (pixels)
const double LaserRange = 1000;

/**
 * Constructor
 * \param game The game this Laser belongs to
 */
CLaser::CLaser(CGame* game) : CProjectile(game, LaserImageName)
{
	SetSpeed(LaserSpeed);
	SetMaxRange(LaserRange);
}
