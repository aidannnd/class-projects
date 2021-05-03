/**
 * \file TileRoad.cpp
 *
 * \author Patrick Doyle
 */

#include "pch.h"
#include "TileRoad.h"

using namespace std;
using namespace Gdiplus;

/** Constructor
* \param game The game this is a member of
* \param filename The image of the tile
* \param type The type of road
*/
CTileRoad::CTileRoad(CGame* game, const std::wstring filename, const std::wstring type) : CTile(game, filename)
{
	SetImage(filename);
    SetType(type);
}

/**
*  Destructor
*/
CTileRoad::~CTileRoad()
{
}


/**
 * Sets type for CTileRoad
 * \param type mType
 */
void CTileRoad::SetType(std::wstring type)
{
    mType = type;
}


/**
 * Hit test for CTileRoad
 * \param x X coord
 * \param y Y coord
 * \returns bool
 */
bool CTileRoad::HitTest(double x, double y)
{
    bool checkX = abs(x - GetX()) <= .60;
    bool checkY = abs(y - GetY()) <= .60;
    return (checkX && checkY);
}


