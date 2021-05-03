/**
 * \file FishGoldeen.h
 *
 * \author Aidan Delfuoco
 *
 * Class that represents a Goldeen fish.
 */

#pragma once
#include <memory>
#include "Item.h"

 /**
  * Implements a Goldeen fish
  */
class CFishGoldeen : public CItem
{
public:
    CFishGoldeen::CFishGoldeen(CAquarium* aquarium);

    /// Default constructor (disabled)
    CFishGoldeen() = delete;

    /// Copy constructor (disabled)
    CFishGoldeen(const CFishGoldeen&) = delete;

    virtual void Draw(Gdiplus::Graphics* graphics) override;

    bool CFishGoldeen::HitTest(int x, int y);

private:
    /// The fish on screen
    std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};

