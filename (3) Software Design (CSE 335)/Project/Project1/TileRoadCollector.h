/**
 * \file TileRoadCollector.h
 *
 * \author Brandon Byiringiro
 *
 *  Collects all road tiles
 */

#pragma once
#include <vector>
#include <memory>
#include "ItemVisitor.h"
#include "Item.h"

/// <summary>
/// Collects all road tiles
/// </summary>
class CTileRoadCollector :
    public CItemVisitor
{
public:
    /** Get the number of bomb towers
     * \returns Number of bomb towers */
    std::vector<CTileRoad*> GetRoadCollection() const { return mRoadCollection; }

    void VisitTileRoad(CTileRoad* road);

private:
    /// Collection of road tiles
    std::vector<CTileRoad*> mRoadCollection;

};

