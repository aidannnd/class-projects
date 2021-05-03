/**
 * \file TileOpen.cpp
 *
 * \author Brian Kim, Patrick Doyle
 */

#include "pch.h"
#include "TileOpen.h"

using namespace std;
using namespace Gdiplus;


/** Constructor
* \param game The game this is a member of
* \param filename The image of the tile
*/
CTileOpen::CTileOpen(CGame* game, const std::wstring filename) : CTile(game, filename)
{
    SetImage(filename);
}

/**
*  Destructor
*/
CTileOpen::~CTileOpen()
{
}


/**
 * Hit test for CTileOpen
 * \param x X location
 * \param y Y location
 * \returns bool
 */
bool CTileOpen::HitTest(double x, double y)
{
    bool checkX = abs(x - GetX()) <= .75;
    bool checkY = abs(y - GetY()) <= .75;
    return (checkX && checkY);
}


/**
 * Checks if tower has been moved
 * \param tower Tower being used
 * \returns bool
 */
bool CTileOpen::MoveTower(std::shared_ptr<CItem> tower)
{
    bool result = CheckStatus(tower);
    if (result == false)
    {
        double x = GetX();
        double y = GetY();
        tower->SetLocation(x * 64 + 32, y * 64 + 32);
        mTower = tower;
    }
    return result;
}


/**
 * Checks status of tile with tower
 * \param tower Tower
 * \returns bool
 */
bool CTileOpen::CheckStatus(std::shared_ptr<CItem> tower)
{
    if (mTower != nullptr)
    {
        // checks if there is a tower on the tile
        if ((mTower->GetX() - 32)/64 == GetX() && (mTower->GetY() - 32) / 64 == GetY())
        {
            if (mTower != tower)
            {
                return true;
            }
        }
    }
    return false;
}
