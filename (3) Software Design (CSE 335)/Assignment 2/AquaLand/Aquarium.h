/**
 * \file Aquarium.h
 *
 * \author Aidan Delfuoco
 *
 * Class that represents an aquarium.
 */

#pragma once

#include <memory>
#include <vector>

#include "Item.h"

 /**
  * The aquarium class.
  */
class CAquarium
{
public:
	void OnDraw(Gdiplus::Graphics* graphics);

	CAquarium::CAquarium();

	void CAquarium::Add(std::shared_ptr<CItem> item);

	std::shared_ptr<CItem> CAquarium::HitTest(int x, int y);

	void CAquarium::MoveToEnd(std::shared_ptr<CItem> item);

private:
	std::unique_ptr<Gdiplus::Bitmap> mBackground; ///< Background image
	/// All of the items to populate our aquarium
	std::vector<std::shared_ptr<CItem> > mItems;
};

