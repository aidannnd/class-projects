/**
 * \file FishBeta.h
 *
 * \author Aidan Delfuoco
 *
 * Class that represents a Beta fish.
 */

#pragma once
#include <memory>
#include "Item.h"

/**
 * Implements a Beta fish
 */
class CFishBeta : public CItem
{
public:
    CFishBeta::CFishBeta(CAquarium *aquarium);

    /// Default constructor (disabled)
    CFishBeta() = delete;

    /// Copy constructor (disabled)
    CFishBeta(const CFishBeta &) = delete;

    virtual void Draw(Gdiplus::Graphics* graphics) override;

    bool CFishBeta::HitTest(int x, int y);

private:
    /// The fish on screen
    std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};

