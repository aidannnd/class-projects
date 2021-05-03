/**
 * \file TowerBombCounter.cpp
 *
 * \author Brian Kim
 */

#include "pch.h"
#include "TowerBombCounter.h"

 /** Visit a CTowerBomb object
 * \param bomb Bomb tower we are visiting */
void CTowerBombCounter::VisitTowerBomb(CTowerBomb* bomb)
{
    mTowerBombCount++;
}