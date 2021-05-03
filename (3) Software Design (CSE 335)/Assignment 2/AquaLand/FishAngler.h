/**
 * \file FishAngler.h
 *
 * \author Aidan Delfuoco
 *
 * Class that represents a Angler fish.
 */

#pragma once
#include <memory>
#include "Item.h"

 /**
  * Implements a Angler fish
  */
class CFishAngler : public CItem
{
public:
    CFishAngler::CFishAngler(CAquarium* aquarium);

    /// Default constructor (disabled)
    CFishAngler() = delete;

    /// Copy constructor (disabled)
    CFishAngler(const CFishAngler&) = delete;

    virtual void Draw(Gdiplus::Graphics* graphics) override;

    bool CFishAngler::HitTest(int x, int y);

private:
    /// The fish on screen
    std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};

