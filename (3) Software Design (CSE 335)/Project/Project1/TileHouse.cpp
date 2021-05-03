/**
 * \file TileRoad.cpp
 *
 * \author Patrick Doyle
 */

#include "pch.h"
#include "TileHouse.h"

using namespace std;
using namespace Gdiplus;

/** Constructor
* \param game The game this is a member of
* \param filename The image of the tile
*/
CTileHouse::CTileHouse(CGame* game, const std::wstring filename) : CTile(game, filename)
{
    SetImage(filename);
}

/**
 *  Destructor
 */
CTileHouse::~CTileHouse()
{
}
