/**
 * \file Tower.cpp
 *
 * \author Ryan Piotrowicz
 */

#include "pch.h"
#include "Tower.h"

using namespace std;
using namespace Gdiplus;

/**
 * Constructor
 * \param game The game this tower belongs to
 * \param filename The image filename of the tower
 */
CTower::CTower(CGame* game, const std::wstring& filename) : CItem(game, filename)
{
	mGame = game;
}


/**
 * Sets timer
 * \param t Time
 */
void CTower::SetAttackTimer(double t)
{
	mAttackTimer = t;
	mTimeUntilAttack = t;
}

/**
 * Updates towers
 * \param elapsed Time spent
 */
void CTower::Update(double elapsed)
{
	mTimeUntilAttack -= elapsed;
	if (mTimeUntilAttack <= 0)
	{
		mTimeUntilAttack += mAttackTimer;
		if (GetX() <= 1024)
		{
			Attack();
		}
	}
}
