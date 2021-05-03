/**
 * \file PanelScore.h
 *
 * \author Brandon Byiringiro / Granny Smith
 *
 * 
 */

#pragma once

#include <string>
#include <memory>

/// <summary>
/// Keeps track or and displays the score of the game
/// </summary>
class CPanelScore
{
public:
	CPanelScore();

	~CPanelScore();

	void UpdateScore(int newAmount);

	/// Resets the score to 0
	void ResetScore() { mScore = 0; }

	int GetScore();

	void Draw(Gdiplus::Graphics* graphics);

private:
	/// <summary>
	/// score of the game
	/// </summary>
	int mScore = 0;
};

