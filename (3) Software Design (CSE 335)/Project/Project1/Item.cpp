#include "pch.h"
#include "Item.h"

using namespace std;
using namespace Gdiplus;

/**
 * Constructor
 * \param game The game this tower belongs to
 * \param filename The image filename of the tower
 */
CItem::CItem(CGame* game, const std::wstring& filename) :
    mGame(game)
{
    mItemImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
    if (mItemImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += filename;
        AfxMessageBox(msg.c_str());
    }
}

/** Set the tower location
 * \param x X location
 * \param y Y location
 */
void CItem::SetLocation(double x, double y)
{
    mPositionX = x;
    mPositionY = y;
}

void CItem::Draw(Gdiplus::Graphics* graphics)
{
    double wid = mItemImage->GetWidth();
    double hit = mItemImage->GetHeight();
    graphics->DrawImage(mItemImage.get(),
        float(GetX() - wid / 2), float(GetY() - hit / 2),
        (float)mItemImage->GetWidth(), (float)mItemImage->GetHeight());
}