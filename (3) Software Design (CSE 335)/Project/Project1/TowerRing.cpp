/**
 * \file TowerRing.cpp
 *
 * \author Ryan Piotrowicz
 */

#include "pch.h"
#include <string>
#include "TowerRing.h"

using namespace std;
using namespace Gdiplus;

/// TowerRing filename
const std::wstring TowerRingImageName = L"images/tower-rings.png";

/**
 * Constructor
 * \param game The game this tower belongs to
 */
CTowerRing::CTowerRing(CGame* game) : CTower(game, TowerRingImageName)
{
    mTowerImage = unique_ptr<Bitmap>(Bitmap::FromFile(TowerRingImageName.c_str()));
    if (mTowerImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += TowerRingImageName;
        AfxMessageBox(msg.c_str());
    }
    SetAttackTimer(5);
}


/**
 * Hit test for CTowerRing
 * \param x X coord
 * \param y Y coord
 * \returns bool
 */
bool CTowerRing::HitTest(double x, double y)
{
    double wid = mTowerImage->GetWidth();
    double hit = mTowerImage->GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to theimage top corner
    double testX = x - GetX() + wid / 2;
    double testY = y - GetY() + hit / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    auto format = mTowerImage->GetPixelFormat();
    if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
    {
        // This image has an alpha map, which implements the 
        // transparency. If so, we should check to see if we
        // clicked on a pixel where alpha is not zero, meaning
        // the pixel shows on the screen.
        Color color;
        mTowerImage->GetPixel((int)testX, (int)testY, &color);
        return color.GetAlpha() != 0;
    }
    else {
        return true;
    }
}


/**
 * Attack class for CTowerRing
 */
void CTowerRing::Attack()
{
    auto ring = std::make_shared<CRing>(GetGame());
    ring->SetLocation(GetX(), GetY());
    GetGame()->AddToAdd(ring);
}