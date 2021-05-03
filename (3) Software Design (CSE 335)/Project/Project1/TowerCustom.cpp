/**
 * \file TowerCustom.cpp
 *
 * \author Aidan Delfuoco
 */

#include "pch.h"
#include <string>
#include "TowerCustom.h"

using namespace std;
using namespace Gdiplus;

 /// TowerCustom filename
const std::wstring TowerCustomImageName = L"images/tower-sparty.png";

/**
 * Constructor
 * \param game The game this tower belongs to
 */
CTowerCustom::CTowerCustom(CGame* game) : CTower(game, TowerCustomImageName)
{
    mTowerImage = unique_ptr<Bitmap>(Bitmap::FromFile(TowerCustomImageName.c_str()));
    if (mTowerImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += TowerCustomImageName;
        AfxMessageBox(msg.c_str());
    }
	SetAttackTimer(2);
}

/**
 * Hit test for CTowerCustom
 * \param x X coord
 * \param y Y coord
 * \returns bool
 */
bool CTowerCustom::HitTest(double x, double y)
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

/*
 * Targeted laser attack
 * Sparty finds the nearest balloon and shoots a laser at it
 */
void CTowerCustom::Attack()
{   
    double closest = 1200;
    double ClosestX = 512;
    double ClosestY = 512;

    for(auto item : GetGame()->GetItems())
    {
        if(item->GetType() == "Balloon")
        {
            double dx = item->GetX() - GetX();
            double dy = item->GetY() - GetY();
            double distance = sqrt((dx * dx) + (dy * dy));
            if(distance < closest)
            {
                ClosestX = item->GetX();
                ClosestY = item->GetY();
                closest = distance;
            }
                       
        }
    }
    double angle = atan2((ClosestY - GetY()), (ClosestX - GetX()));
    auto laser = std::make_shared<CLaser>(GetGame());
    laser->SetLocation(GetX() + 10 * cos(angle), GetY() + 10 * sin(angle));
    laser->SetAngle(angle);
    GetGame()->AddToAdd(laser);
  
}