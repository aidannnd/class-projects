#include "pch.h"
#include "TileRoadCollector.h"

/// <summary>
/// Adds road object into vector
/// </summary>
/// <param name="road"> road object</param>
void CTileRoadCollector::VisitTileRoad(CTileRoad* road)
{
	mRoadCollection.push_back(road);
}
