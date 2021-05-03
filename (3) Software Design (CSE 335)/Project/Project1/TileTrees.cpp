/**
 * \file TileTrees.cpp
 *
 * \author Patrick Doyle
 */

#include "pch.h"
#include "TileTrees.h"

using namespace std;
using namespace Gdiplus;

/** Constructor
* \param game The game this is a member of
* \param filename The image of the tile
*/
CTileTrees::CTileTrees(CGame* game, const std::wstring filename) : CTile(game, filename)
{
    SetImage(filename);
}

/**
*  Destructor
*/
CTileTrees::~CTileTrees()
{
}


