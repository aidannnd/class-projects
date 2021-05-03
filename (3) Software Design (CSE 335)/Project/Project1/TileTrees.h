/**
* \file TileTrees.h
*
* \author Patrick Doyle
*
* Class for a tree tile.
*/
#pragma once
#include "Tile.h"

/**
 * Class that implements a tree tile.
 */
class CTileTrees :
    public CTile
{
public:
    CTileTrees(CGame* game, const std::wstring filename);

    ///  Default constructor (disabled)
    CTileTrees() = delete;

    ///  Copy constructor (disabled)
    CTileTrees(const CTileTrees&) = delete;

    ~CTileTrees();
   
    /** Accept a visitor
     * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTileTrees(this); }
};
