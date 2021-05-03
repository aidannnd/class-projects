#include "pch.h"
#include "PanelScore.h"

using namespace std;
using namespace Gdiplus;


/// Constructs score panel object
CPanelScore::CPanelScore()
{
}


/// Destroys score panel object
CPanelScore::~CPanelScore()
{
}

/// Increases or decreases the score by a certain amount
/// <param name="newAmount"> number to increase or decrease score</param>
void CPanelScore::UpdateScore(int newAmount)
{
	mScore = mScore + newAmount;
}


/// Grabs the score
/// <returns> int value score </returns>
int CPanelScore::GetScore()
{
	return mScore;
}

/**
 * Draw the score
 * \param graphics The GDI+ graphics context to draw on
 */
void CPanelScore::Draw(Gdiplus::Graphics* graphics)
{
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 16);
	PointF origin(1062, 450);
	SolidBrush white(Color(255, 100, 50));

	graphics->DrawString(L"Score",  // String to draw
		-1,         // String length, -1 so it figures it out on its own
		&font,      // The font to use
		origin,		// Where to draw (top left corner)
		&white);    // The brush to draw the text with



	auto convertedString = to_wstring(mScore);
	graphics->DrawString(convertedString.c_str(),  // String to draw
		-1,         // String length, -1 so it figures it out on its own
		&font,      // The font to use
		PointF(1110, 500),   // Where to draw (top left corner)
		&white);    // The brush to draw the text with

}