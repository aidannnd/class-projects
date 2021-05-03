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

	void CAquarium::Save(const std::wstring& filename);

	void CAquarium::Load(const std::wstring& filename);

	void CAquarium::Clear();

	void CAquarium::Update(double elapsed);

	/// Get the width of the aquarium
	/// \returns Aquarium width
	int GetWidth() const { return mBackground->GetWidth(); }

	/// Get the height of the aquarium
	/// \returns Aquarium height
	int GetHeight() const { return mBackground->GetHeight(); }

private:
	std::unique_ptr<Gdiplus::Bitmap> mBackground; ///< Background image
	/// All of the items to populate our aquarium
	std::vector<std::shared_ptr<CItem> > mItems;

	void CAquarium::XmlItem(const std::shared_ptr<xmlnode::CXmlNode>& node);

};

