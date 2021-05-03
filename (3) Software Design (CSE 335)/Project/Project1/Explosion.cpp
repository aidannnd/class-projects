/**
 * \file Explosion.cpp
 *
 * \author Ryan Piotrowicz
 */

#include "pch.h"
#include "Explosion.h"

using namespace Gdiplus;

 /// Random filename because we aren't drawing an image
const std::wstring PlaceholderFile = L"images/tower-bomb.png";

/// Radius of explosion
const int RADIUS = 100;

/// Length of explosion cloud in seconds
const double TIMER = .25;

/**
 * Constructor
 * \param game The game this explosion belongs to
 */
CExplosion::CExplosion(CGame* game) : CItem(game, PlaceholderFile)
{
	SetRadius(RADIUS);
    SetTimer(TIMER);
}

void CExplosion::Update(double elapsed)
{
    mTimer -= elapsed;
    if (mTimer <= 0)
    {
        GetGame()->AddToRemove(shared_from_this());
    }
}

void CExplosion::Draw(Gdiplus::Graphics* graphics)
{
    Pen pen(Color(128, 0, 0), 3);
    SolidBrush brush(Color(128, 0, 0));
    graphics->DrawEllipse(&pen, GetX() - mRadius, GetY() - mRadius, mRadius * 2, mRadius * 2);
    graphics->FillEllipse(&brush, GetX() - mRadius, GetY() - mRadius, mRadius * 2, mRadius * 2);
}
