/**
 * \file GoButton.h
 *
 * \author Aidan Delfuoco
 *
 * Class for the go button
 */

#pragma once
#include <memory>
#include <string>

 /**
  * Class for the go button
  */
class CGoButton
{
public:
	CGoButton();

	~CGoButton();

	void Draw(Gdiplus::Graphics* graphics);

	void CGoButton::SetLocation(double x, double y);

	bool HitTest(double x, double y);

	/** The X location of the button
	 * \returns X location in button */
	double GetX() const { return mPositionX; }

	/** The Y location of the item
	 * \returns Y location in pixels */
	double GetY() const { return mPositionY; }

	/** Gets button status
	 * \returns mShowGoButton */
	bool GetButtonStatus() { return mShowGoButton; }

	/** Sets button status
	 * \param b Bool we are setting */
	void SetButtonStatus(bool b) { mShowGoButton = b; }

private:
	/// Image of the button
	std::unique_ptr<Gdiplus::Bitmap> mButtonImage;

	/// Type of item
	std::string mType = "Button";

	/// The X position of the button
	double mPositionX = 0;

	/// The Y position of the button
	double mPositionY = 0;

	/// Bool to set GO button
	bool mShowGoButton = true;
};