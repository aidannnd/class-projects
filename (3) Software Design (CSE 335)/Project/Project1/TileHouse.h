/**
* \file TileHouse.h
*
* \author Patrick Doyle
*
* Class for a house tile.
*/
#pragma once
#include "Tile.h"

/**
 * Class that implements a house tile.
 */
class CTileHouse :
    public CTile
{
public:
    CTileHouse(CGame* game, const std::wstring filename);

    ///  Default constructor (disabled)
    CTileHouse() = delete;

    ///  Copy constructor (disabled)
    CTileHouse(const CTileHouse&) = delete;


    ~CTileHouse();

    /** Accept a visitor
     * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTileHouse(this); }
};


