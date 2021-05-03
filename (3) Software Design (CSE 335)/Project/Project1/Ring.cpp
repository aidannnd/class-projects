/**
 * \file Ring.cpp
 *
 * \author Ryan Piotrowicz
 */

#include "pch.h"
#include "Ring.h"

using namespace Gdiplus;

/// Random filename because we aren't drawing an image
const std::wstring PlaceholderFile = L"images/tower-bomb.png";

/// Minimum radius of the circle (pixels)
const int MIN_RADIUS = 10;

/// Maximum radius of the circle (pixels)
const int MAX_RADIUS = 100;

/// Speed the ring expands at (pixels/second)
const double EXPANSION_SPEED = 100;

/**
 * Constructor
 * \param game The game this explosion belongs to
 */
CRing::CRing(CGame* game) : CItem(game, PlaceholderFile)
{
	SetRadius(MIN_RADIUS);
	SetSpeed(EXPANSION_SPEED);
}


/**
 * Updates for CRing
 * \param elapsed Time
 */
void CRing::Update(double elapsed)
{
	mRadius += elapsed * mSpeed;
	if (mRadius > MAX_RADIUS)
	{   
        mRadius = MAX_RADIUS;
        GetGame()->AddToRemove(shared_from_this());
	}
    for (auto item : GetGame()->GetItems())
    {
        if (item->GetType() == "Balloon")
        {
            double dx = item->GetX() - GetX();
            double dy = item->GetY() - GetY();
            double distance = sqrt((dx * dx) + (dy * dy));
            if (distance <= mRadius + 24.0 && distance >= mRadius - 24.0)
            {
                GetGame()->AddToRemove(item);
                GetGame()->UpdateScore(3);
            }
        }
    }
}


/**
 * Draws ring
 * \param graphics Graphics
 */
void CRing::Draw(Gdiplus::Graphics* graphics)
{
    Pen pen(Color(128, 0, 0), 3);
    graphics->DrawEllipse(&pen, GetX() - mRadius, GetY() - mRadius, mRadius * 2, mRadius * 2);
}
