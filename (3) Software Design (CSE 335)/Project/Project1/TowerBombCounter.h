/**
 * \file TowerBombCounter.h
 *
 * \author Brian Kim
 *
 * Bomb tower counter class.
 */

#pragma once
#include "ItemVisitor.h"

 /**
  * Bomb tower counter class.
  */
class CTowerBombCounter :
    public CItemVisitor
{
public:
    /** Get the number of bomb towers
     * \returns Number of bomb towers */
    int GetTowerBombCount() const { return mTowerBombCount; }

    void VisitTowerBomb(CTowerBomb* bomb);

private:
    /// Bomb tower counter
    int mTowerBombCount = 0;
};

