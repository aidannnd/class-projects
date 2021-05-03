/**
 * \file FishMagikarp.h
 *
 * \author Aidan Delfuoco
 *
 * Class that represents a Magikarp fish.
 */

#pragma once
#include <memory>
#include "Item.h"

 /**
  * Implements a Magikarp fish
  */
class CFishMagikarp : public CItem
{
public:
    CFishMagikarp::CFishMagikarp(CAquarium* aquarium);

    /// Default constructor (disabled)
    CFishMagikarp() = delete;

    /// Copy constructor (disabled)
    CFishMagikarp(const CFishMagikarp&) = delete;

    virtual void Draw(Gdiplus::Graphics* graphics) override;

    bool CFishMagikarp::HitTest(int x, int y);

private:
    /// The fish on screen
    std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};

