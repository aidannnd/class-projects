/**
 * \file Tile.h
 *
 * \author Brian Kim, Patrick Doyle
 *
 * Base class for a tile object.
 */

#pragma once

#include <memory>
#include <string>
#include "XmlNode.h"
#include "Item.h"

class CGame;
 /**
  * Base class for a tile object.
  */
class CTile : public CItem
{
public:
    /// How much we offset drawing the tile to the left of the center
    const static int OffsetLeft = 32;

    /// How much we offset drawing the tile above the center
    const static int OffsetDown = 32;

    /** The directory were the images are stored */
    static const std::wstring ImagesDirectory;

    ///  Default constructor (disabled)
    CTile() = delete;

    ///  Copy constructor (disabled)
    CTile(const CTile&) = delete;

    virtual ~CTile();

    void SetImage(const std::wstring& file);

    virtual void Draw(Gdiplus::Graphics* graphics) override;

    ///  Get the city this item is in
    /// \returns City pointer
    CGame* GetGame() { return mGame; }


    /**  The id of the tile
    * \returns mId  */
    std::wstring GetId() const { return mId; };

    /**  The image of the tile
    * \returns mItemImage  */
    virtual std::unique_ptr<Gdiplus::Bitmap>& GetImage() { return mItemImage; }

protected:
    CTile(CGame* game, const std::wstring& filename);

private:
    ///  The game this tile is contained in
    CGame* mGame;

    ///  The image of this tile
    std::unique_ptr<Gdiplus::Bitmap> mItemImage;
    ///  The id of this tile
    std::wstring mId;

    ///  The file for this item
    std::wstring mFile;
};
