/**
 * \file TileOpen.h
 *
 * \author Brian Kim
 *
 * Class for an open tile.
 */

#pragma once

#include "Tile.h"


 /**
  * Class for an open tile.
  */
class CTileOpen :
    public CTile
{
public:
    CTileOpen(CGame* game, const std::wstring filename);

    ///  Default constructor (disabled)
    CTileOpen() = delete;

    ///  Copy constructor (disabled)
    CTileOpen(const CTileOpen&) = delete;

    ~CTileOpen();

   
    ///  Gets type
    /// \returns mType
    std::string GetType() { return mType; }
    
    bool HitTest(double x, double y) override final;

    bool MoveTower(std::shared_ptr<CItem> tower);

    bool CheckStatus(std::shared_ptr<CItem> tower);

    /** Accept a visitor
     * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTileOpen(this); }


private:
    /// type of the object
    std::string mType = "Open";

    /// tower set to null
    std::shared_ptr<CItem> mTower = nullptr;
};


