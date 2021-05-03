/**
* \file BuildingCounter.h
*
* \author Aidan Delfuoco
*
* Class that handles counting buildings
*/

#pragma once
#include "TileVisitor.h"

/**
 * Class that handles counting buildings
 */
class CBuildingCounter :
    public CTileVisitor
{
public:
    /** Get the number of buildings
     * \returns Number of buildings */
    int GetNumBuildings() const { return mNumBuildings; }

    /** Visit a CTileBuilding object
     * \param building Building we are visiting */
    void CBuildingCounter::VisitBuilding(CTileBuilding* building)
    {
        mNumBuildings++;
    }

private:
    /// Buildings counter
    int mNumBuildings = 0;
};

