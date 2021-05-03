/**
 * \file Game.h
 *
 * \author Patrick Doyle
 *
 * Class that creates the game.
 */

#pragma once
#include <vector>
#include <memory>
#include <utility>
#include <tuple>

#include "XmlNode.h"
#include "PanelScore.h"
#include "Tile.h"
#include "Item.h"
#include "Tower.h"
#include "DeclaredItem.h"
#include "Balloon.h"
#include "GoButton.h"
#include "ItemVisitor.h"
#include "TileRoadCollector.h"
#include "BalloonCount.h"

class CLevel;
class CTower;

 /**
  * Main game class
  */
class CGame
{
public:
	CGame();
	
	void OnDraw(Gdiplus::Graphics* graphics, int width, int height);

	/// Hit test for item
	std::shared_ptr<CItem> HitTest(int x, int y);

	/// Hit test for Open tile
	std::shared_ptr<CItem> HitTestForOpenTile(int x, int y);

	/// Moves item to front of vector
	void MoveToFront(std::shared_ptr<CItem> item);

	std::shared_ptr<CItem> OnLButtonDown(int x, int y);

	std:: tuple<double, double> OnLButtonUp(double x, double y);

	void Update(double elapsed);

	void Load(const std::wstring& filename);

	void ClearTiles();

	void ClearItems();

	/// Gets items from mTiles
	/// \returns mTiles
	std::vector<std::shared_ptr<CItem>> GetItems() { return mTiles; }

	void UpdateScore(int score);

	void ResetScore();

	void Add(std::shared_ptr<CItem> item);

	void AddToAdd(std::shared_ptr<CItem> item);

	void AddToRemove(std::shared_ptr<CItem> item);

	void Add2(std::shared_ptr<CDeclaredItem> item);

	/// Creates road tile
	void XmlRoad(const std::shared_ptr<xmlnode::CXmlNode>& node);
	
	/// Creates open tile
	void XmlOpen(const std::shared_ptr<xmlnode::CXmlNode>& node);
	
	/// Creates trees tile
	void XmlTrees(const std::shared_ptr<xmlnode::CXmlNode>& node);
	
	/// Creates house tile
	void XmlHouse(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/// Updates tiles
	void UpdateTiles(Gdiplus::Graphics* graphics);
	
	/// Level getter
	/// \return mLevel
	std::shared_ptr<CLevel> GetLevel() const { return mLevel; }

	void DeleteItem(std::shared_ptr<CItem> item);

	CItem* HitTestForRoad(int x, int y);

	bool HitTestForButton(double x, double y);

	/// Removes button
	void RemoveButton() { mGoButton.SetButtonStatus(false); }

	/// Turns button on to be shown
	void ShowButton() { mGoButton.SetButtonStatus(true); }

	/// Gets button status
	/// \returns mGoButton.GetButtonStatus()
	bool GetButtonStatus() { return mGoButton.GetButtonStatus(); }

	/// Resets balloon count
	void ResetBalloons() { mCurrBalloons = 0; }

	void Accept(CItemVisitor* visitor);

	void DrawLevelStart(Gdiplus::Graphics* graphics, int level);

	/// Adds s to timer
	/// \param s Time
	void SetTimer(double s) { mTimer += s; }
	
	/// Gets timer
	/// \returns mTimer
	double GetTimer() { return mTimer; }

	/// Sets timer to zero
	void SetTimerToZero() { mTimer = 0; }

private:

	/// Game area width in virtual pixels
	const static int Width = 1224;

	/// Game area height in virtual pixels
	const static int Height = 1024;

	/// Scale for virtual pixels
	float mScale = 0;

	/// X offset for virtual pixels
	float mXOffset = 0;
	
	/// Y offset for virtual pixels
	float mYOffset = 0;

	/// For items section of Xml
	void XmlTile(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/// For declarations section of Xml
	void XmlTile2(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/// All of the tiles that make up our game
	std::vector<std::shared_ptr<CItem> > mTiles;

	/// Holds items that store images and types
	std::vector<std::shared_ptr<CDeclaredItem> > mItems;

	/// Vector of items to add after iteration
	std::vector<std::shared_ptr<CItem> > mToAdd;

	/// Vector of items to remove after iteration
	std::vector<std::shared_ptr<CItem> > mToRemove;

	/// Previous ballon used to initialize a new ballon at 42 balloon
	std::shared_ptr<CItem> mPrevBalloon = nullptr;

	/// The level
	std::shared_ptr<CLevel> mLevel;

	/// The score
	CPanelScore mPanelScore;

	/// checks if tower vector is already initialized
	bool mInitialzed = false;

	/// start x for balloon
	double mBalloonX = 0;

	/// start y for balloon
	double mBalloonY = 0;

	/// denies the various items from updating
	bool mGoActivated = false;

	/// GO button for game
	CGoButton mGoButton;

	/// Current balloon count
	int mCurrBalloons = 0;

	/// timer for the game level message
	double mTimer = 0;
};
