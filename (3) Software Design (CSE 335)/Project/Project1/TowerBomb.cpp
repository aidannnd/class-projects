/**
 * \file TowerBomb.cpp
 *
 * \author Ryan Piotrowicz
 */

#include "pch.h"
#include <string>
#include "TowerBomb.h"

using namespace std;
using namespace Gdiplus;

/// TowerBomb filename
const std::wstring TowerBombImageName = L"images/tower-bomb.png";

/// TowerBomb explosion radius
const int RADIUS = 100;

/**
 * Constructor
 * \param game The game this tower belongs to
 * \param bombNum What number bomb tower this is
 */
CTowerBomb::CTowerBomb(CGame* game, int bombNum) : CTower(game, TowerBombImageName)
{
    mTowerImage = unique_ptr<Bitmap>(Bitmap::FromFile(TowerBombImageName.c_str()));
    if (mTowerImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += TowerBombImageName;
        AfxMessageBox(msg.c_str());
    }
	SetAttackTimer(3.0 * bombNum);
}

/**
 * Hit test for CTowerBomb
 * \param x X coord
 * \param y Y coord
 * \returns bool
 */
bool CTowerBomb::HitTest(double x, double y)
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
 * Attack class for CTowerBomb
 */
void CTowerBomb::Attack()
{
    auto explosion = std::make_shared<CExplosion>(GetGame());
    explosion->SetLocation(GetX(), GetY());
    GetGame()->AddToAdd(explosion);
    
    for (auto item : GetGame()->GetItems())
    {
        if (item->GetType() == "Balloon")
        {
            double dx = item->GetX() - GetX();
            double dy = item->GetY() - GetY();
            double distance = sqrt((dx * dx) + (dy * dy));
            if (distance <= RADIUS + 24.0)
            {
                GetGame()->AddToRemove(item);
                GetGame()->UpdateScore(2);
            }
        }
    }
 
    GetGame()->AddToRemove(shared_from_this());

}
