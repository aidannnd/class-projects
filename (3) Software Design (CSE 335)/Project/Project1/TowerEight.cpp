/**
 * \file TowerEight.cpp
 *
 * \author Ryan Piotrowicz
 */

#include "pch.h"
#include "TowerEight.h"

using namespace std;
using namespace Gdiplus;

/// TowerEight filename
const std::wstring TowerEightImageName = L"images/tower8.png";

/// Pi
const double PI = 3.1415926;

/**
 * Constructor
 * \param game The game this tower belongs to
 */
CTowerEight::CTowerEight(CGame* game) : CTower(game, TowerEightImageName)
{
    mTowerImage = unique_ptr<Bitmap>(Bitmap::FromFile(TowerEightImageName.c_str()));
    if (mTowerImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += TowerEightImageName;
        AfxMessageBox(msg.c_str());
    }
    SetAttackTimer(5);
}

/**
 * Hit test for CTowerEight
 * \param x X coord
 * \param y Y coord
 * \returns bool
 */
bool CTowerEight::HitTest(double x, double y)
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
 * Attack class for CTowerEight
 */
void CTowerEight::Attack()
{
    for (int i = 0; i < 8; i++)
    {
        auto dart = std::make_shared<CDart>(GetGame());
        dart->SetLocation(GetX() + 10 * cos(i * PI/4), GetY() + 10 * sin(i * PI/4));
        dart->SetAngle(i * PI / 4);
        GetGame()->AddToAdd(dart);
    }
}
