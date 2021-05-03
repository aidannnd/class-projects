/**
* \file TileRoad.h
*
* \author Patrick Doyle
*
* Class for a road tile.
*/
#pragma once
#include "Tile.h"

/**
 * Class that implements a road tile.
 */
class CTileRoad :
    public CTile
{
public:
    CTileRoad(CGame* game, const std::wstring filename, const std::wstring type);

    ///  Default constructor (disabled)
    CTileRoad() = delete;

    ///  Copy constructor (disabled)
    CTileRoad(const CTileRoad&) = delete;


    ~CTileRoad();
  

    ///  Sets mType
    void SetType(std::wstring type);

    ///  Gets mType
    /// \returns mType
    std::wstring GetRoadType() { return mType; }

    bool HitTest(double x, double y) override final;

    /** Accept a visitor
     * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTileRoad(this); }

private:
    ///  Type of road
    std::wstring mType;
};

