/**
 * \file Tile.cpp
 *
 * \author Brian Kim, Patrick Doyle
 */

#include "pch.h"
#include "Tile.h"
#include "Game.h"

using namespace std;
using namespace Gdiplus;


/// The directory containing the file images
const std::wstring CTile::ImagesDirectory = L"images/";

/// Distance from center for inside of tiles
const int InsideTolerance = 64;

/**  Constructor
 * \param game The game this tile is a member of
 * \param filename The file for the tile image
 */
CTile::CTile(CGame* game, const std::wstring& filename) : CItem(game, filename)
{
}

/**
*  Destructor
*/
CTile::~CTile()
{
}

/**
 *  Set the image file to draw
 * \param file The base filename. Blank files are allowed
 */
void CTile::SetImage(const std::wstring& file)
{
    if (!file.empty())
    {
        wstring filename = file;
        mItemImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
        if (mItemImage->GetLastStatus() != Ok)
        {
            wstring msg(L"Failed to open ");
            msg += filename;
            AfxMessageBox(msg.c_str());
            return;
        }
    }
    else
    {
        mItemImage.release();
    }

    mFile = file;
}

/**
 *  Draw this tile
 * \param graphics The graphics context to draw on
 */
void CTile::Draw(Gdiplus::Graphics* graphics)
{
    if (mItemImage != nullptr)
    {
        int wid = 64;
        int hit = 64;

        graphics->DrawImage(mItemImage.get(),
            static_cast<int>(GetX())*64, static_cast<int>(GetY()) *64,
            wid + 1, hit + 1);
    }

}


