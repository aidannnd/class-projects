/**
 * \file GoButton.cpp
 *
 * \author Aidan Delfuoco
 */

#include "pch.h"
#include "GoButton.h"

using namespace std;
using namespace Gdiplus;
#include <string>

 /// GoButton filename
const std::wstring GoButtonImageName = L"images/button-go.png";

/// Constructs button object
CGoButton::CGoButton()
{
    mButtonImage = unique_ptr<Bitmap>(Bitmap::FromFile(GoButtonImageName.c_str()));
    if (mButtonImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += GoButtonImageName;
        AfxMessageBox(msg.c_str());
    }
}

/// Destroys button object
CGoButton::~CGoButton()
{
}

/**
 * Draw the score
 * \param graphics The GDI+ graphics context to draw on
 */
void CGoButton::Draw(Gdiplus::Graphics* graphics)
{
        double wid = mButtonImage->GetWidth();
        double hit = mButtonImage->GetHeight();
        graphics->DrawImage(mButtonImage.get(),
            float(1050), float(600),
            (float)mButtonImage->GetWidth(), (float)mButtonImage->GetHeight());

}

/** Set the button location
 * \param x X location
 * \param y Y location
 */
void CGoButton::SetLocation(double x, double y)
{
    mPositionX = x;
    mPositionY = y;
}


/**
 * Hit Test for CGoButton
 * \param x X coord
 * \param y Y coord
 * \returns bool
 */
bool CGoButton::HitTest(double x, double y)
{
    int middleX = 17;
    int middleY = 10;
    bool checkX = abs(x - middleX) <= 2;
    bool checkY = abs(y - middleY) <= 2;
    return (checkX && checkY);
}
