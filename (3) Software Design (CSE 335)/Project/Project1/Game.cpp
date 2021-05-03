/**
 * \file Game.cpp
 *
 * \author Patrick Doyle
 */
#include "pch.h"
#include "Game.h"
#include "Tile.h"
#include "TileHouse.h"
#include "TileOpen.h"
#include "TileRoad.h"
#include "TileTrees.h"
#include "TowerRing.h"
#include "TowerEight.h"
#include "TowerBomb.h"
#include "TowerCustom.h"
#include "DeclaredItem.h"
#include "Level.h"

using namespace std;
using namespace Gdiplus;
using namespace xmlnode;

/**
* Game constructor
*/
CGame::CGame()
{
    mLevel = make_shared<CLevel>(this, 1);
}

/**
 * Draw the game area
 * \param graphics The GDI+ graphics context to draw on
 * \param width Width of the client window
 * \param height Height of the client window
 */
void CGame::OnDraw(Gdiplus::Graphics* graphics, int width, int height)
{
    // Fill the background with black
    SolidBrush brush(Color::Black);
    graphics->FillRectangle(&brush, 0, 0, width, height);

    //
    // Automatic Scaling
    //
    float scaleX = float(width) / float(Width);
    float scaleY = float(height) / float(Height);
    mScale = min(scaleX, scaleY);

    // Ensure it is centered horizontally
    mXOffset = (float)((width - Width * mScale) / 2);

    // Ensure it is centered vertically
    mYOffset = (float)((height - Height * mScale) / 2);

    //mScore.Draw(graphics, mXOffset, mYOffset);

    graphics->TranslateTransform(mXOffset, mYOffset);
    graphics->ScaleTransform(mScale, mScale);

    auto TowerRing = std::make_shared<CTowerRing>(this);
    TowerRing->SetLocation(1125, 100);
    TowerRing->Draw(graphics);

    auto TowerEight = std::make_shared<CTowerEight>(this);
    TowerEight->SetLocation(1125, 200);
    TowerEight->Draw(graphics);

    auto TowerBomb = std::make_shared<CTowerBomb>(this, 1);
    TowerBomb->SetLocation(1125, 300);
    TowerBomb->Draw(graphics);

    auto TowerCustom = std::make_shared<CTowerCustom>(this);
    TowerCustom->SetLocation(1125, 400);
    TowerCustom->Draw(graphics);

    if (mInitialzed == false)
    {
        Add(TowerRing);
        Add(TowerBomb);
        Add(TowerCustom);
        Add(TowerEight);
        mInitialzed = true;
    }

    mPanelScore.Draw(graphics);

    if (mGoButton.GetButtonStatus())
    {
        mGoButton.SetLocation(1125, 500);
        mGoButton.Draw(graphics);
        mGoActivated = true;
    }
    else if (mCurrBalloons != 30)
    {
        if (mPrevBalloon != nullptr)
        {
            int xval;
            int yval;
            if (mBalloonX == 0)
            {
                xval = abs(mPrevBalloon->GetX() - (mBalloonX * 64));
                yval = abs(mPrevBalloon->GetY() - (mBalloonY * 64 + 32));
            }
            else
            {
                xval = abs(mPrevBalloon->GetX() - (mBalloonX * 64 + 32));
                yval = abs(mPrevBalloon->GetY() - (mBalloonY * 64));
            }
           
            if (xval > 42 || yval > 42)
            {
                auto balloon = std::make_shared<CBalloon>(this, L"red-balloon.png");
                balloon->Reinitialize();
                if (mBalloonX == 0)
                {
                    balloon->SetLocation(mBalloonX * 64, mBalloonY * 64 + 32); // Offset to fit in middle of road
                }
                else
                {
                    balloon->SetLocation(mBalloonX * 64 + 32, mBalloonY * 64); // Offset to fit in middle of road
                }
                
                balloon->Draw(graphics);
                Add(balloon);
                mCurrBalloons += 1;
                mPrevBalloon = balloon;
            }
            else
            {
                CBalloonCount visitor;
                this->Accept(&visitor);
                if (visitor.GetBalloonCount() == 0)
                {
                    auto balloon = std::make_shared<CBalloon>(this, L"red-balloon.png");
                    balloon->Reinitialize();
                    if (mBalloonX == 0)
                    {
                        balloon->SetLocation(mBalloonX * 64, mBalloonY * 64 + 32); // Offset to fit in middle of road
                    }
                    else
                    {
                        balloon->SetLocation(mBalloonX * 64 + 32, mBalloonY * 64); // Offset to fit in middle of road
                    }
                    balloon->Draw(graphics);
                    Add(balloon);
                    mCurrBalloons += 1;
                    mPrevBalloon = balloon;
                }
            }
        }
        else
        {
            auto balloon = std::make_shared<CBalloon>(this, L"red-balloon.png");
            balloon->Reinitialize();
            if (mBalloonX == 0)
            {
                balloon->SetLocation(mBalloonX * 64, mBalloonY * 64 + 32); // Offset to fit in middle of road
            }
            else
            {
                balloon->SetLocation(mBalloonX * 64 + 32, mBalloonY * 64); // Offset to fit in middle of road
            }
            balloon->Draw(graphics);
            Add(balloon);
            mCurrBalloons += 1;
            mPrevBalloon = balloon;
        }
    }

    this->UpdateTiles(graphics);

    if (mCurrBalloons == 30)
    {
        CBalloonCount visitor;
        this->Accept(&visitor);
        if (visitor.GetBalloonCount() == 0)
        {
            auto numLevel = mLevel->GetCurLevel();
            if (numLevel != 3)
            {
                mTimer = 0;
                mLevel = make_shared<CLevel>(this, numLevel + 1);
                ShowButton();
                ResetBalloons();
            }
            else
            {
                mTimer = 0;
                mLevel = make_shared<CLevel>(this, 3);
                ShowButton();
                ResetBalloons();
            }
        }
    }
}


/**
 * Class that updates tiles
 * \param graphics Graphics
 */
void CGame::UpdateTiles(Gdiplus::Graphics* graphics)
{
    for (auto i = mTiles.begin(); i != mTiles.end(); i++)
    {
            (*i)->Draw(graphics);
    }
}

/** Accept a visitor for the collection
 * \param visitor The visitor for the collection
 */
void CGame::Accept(CItemVisitor* visitor)
{
    for (auto tile : mTiles)
    {
        tile->Accept(visitor);
    }
}

/**
 *  Hit test for items
 * \param x X coord
 * \param y Y coord
 * \returns tile
 */
std::shared_ptr<CItem> CGame::HitTest(int x, int y)
{
    for (auto i = mTiles.begin(); i != mTiles.end(); i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
}


/**
 * Hit test for open tiles
 * \param x X coord
 * \param y Y coord
 * \returns open tile
 */
std::shared_ptr<CItem> CGame::HitTestForOpenTile(int x, int y)
{
    double oX = ((x - mXOffset) / mScale)/64;
    double oY = ((y - mYOffset) / mScale)/64;
    for (auto i = mTiles.begin(); i != mTiles.end(); i++)
    {
        if ((*i)->GetType() == "Open")
        {
            if ((*i)->HitTest(oX, oY))
            {
                return *i;
            }
        }
    }

    return  nullptr;
}

/**  Delete an item from the aquarium
*
* \param item The item to delete.
*/
void CGame::DeleteItem(std::shared_ptr<CItem> item)
{
    auto loc = find(::begin(mTiles), ::end(mTiles), item);
    if (loc != ::end(mTiles))
    {
        mTiles.erase(loc);
    }
}


/**
 * Hit test for road
 * \param x X coord
 * \param y Y cpprd
 * \returns CItem item
 */
CItem* CGame::HitTestForRoad(int x, int y)
{
    if (mScale != 0)
    {
        double oX = x / 64;
        double oY = y / 64;
        CTileRoadCollector visitor;
        this->Accept(&visitor);
        auto list = visitor.GetRoadCollection();
        for (auto i = list.begin(); i != list.end(); i++)
        {
            if ((*i)->HitTest(oX, oY))
            {
                return *i;
            }
        }
    }
    return  nullptr;
}



/**
 * Hit test for button in game
 * \param x X coord
 * \param y Y coord
 * \returns bool
 */
bool CGame::HitTestForButton(double x, double y)
{
    double oX = ((x - mXOffset) / mScale) / 64;
    double oY = ((y - mYOffset) / mScale) / 64;
    return mGoButton.HitTest(oX, oY);
}

/**  Move an item to the front of the list of items.
*
* Removes item from the list and adds it to the end so it
* will display last.
* \param item The item to move
*/
void CGame::MoveToFront(std::shared_ptr<CItem> item)
{
    auto loc = find(::begin(mTiles), ::end(mTiles), item);
    if (loc != ::end(mTiles))
    {
        mTiles.erase(loc);
    }

    mTiles.push_back(item);
}


/**
* Handles left button down events.
* Changes coordinates to virtual pixels.
* \param x X coordinate.
* \param y Y coordinate.
* \return the object clicked on, or nullptr
*/
std::shared_ptr<CItem> CGame::OnLButtonDown(int x, int y)
{
    double oX = (x - mXOffset) / mScale;
    double oY = (y - mYOffset) / mScale;
    return this->HitTest(oX, oY);
}

/**
* Handles left button up events.
* Changes coordinates to virtual pixels.
* \param x X coordinate.
* \param y Y coordinate.
* \return converted XY coordinates
*/
tuple<double, double> CGame::OnLButtonUp(double x, double y)
{
    double oX = (x - mXOffset) / mScale;
    double oY = (y - mYOffset) / mScale;
    return tuple<double, double>(oX, oY);
}

/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CGame::Update(double elapsed)
{
    for (auto item : mTiles)
    {
        if (item != nullptr)
        {
            item->Update(elapsed);
            // balloon exited the game
            if (item->ScoreUpdatedByBalloon() == true && item->GetHitStatus() == false)
            {
                DeleteItem(item);
                mPanelScore.UpdateScore(-1);
            }
        }
    }
    if (mGoActivated)
    {
        for (auto item : mToAdd)
        {
            Add(item);
        }
        mToAdd.empty();

        for (auto item : mToRemove)
        {
            DeleteItem(item);
        }
        mToRemove.empty();

    }
}

/**  Add a tile to the game
* \param tile New tile to add
*/
void CGame::Add(std::shared_ptr<CItem> tile)
{
    mTiles.push_back(tile);
}

/** Stage an item to be added after an iteration
 * \param item New item to add
 */
void CGame::AddToAdd(std::shared_ptr<CItem> item)
{
    mToAdd.push_back(item);
}

/** Stage an item to be deleted after an iteration
 * \param item The item to be deleted
 */
void CGame::AddToRemove(std::shared_ptr<CItem> item)
{
    mToRemove.push_back(item);
}

/**  Add a declaredItem to the game
* \param item New item to add
*/
void CGame::Add2(std::shared_ptr<CDeclaredItem> item)
{
    mItems.push_back(item);
}

/** Update the score
 *  \param score Score to be updated by
 */
void CGame::UpdateScore(int score)
{
    mPanelScore.UpdateScore(score);
}

/** Resets the score */
void CGame::ResetScore()
{
    mPanelScore.ResetScore();
}


/**  Load the game from a XML file.
*
* Opens the XML file and reads the nodes, creating items as appropriate.
*
* \param filename The filename of the file to load the game from.
*/
void CGame::Load(const std::wstring& filename)
{
    // We surround with a try/catch to handle errors
    try
    {
        // Reinitialize the panel
        mInitialzed = false;

        // Open the document to read
        shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

        // Once we know it is open, clear the existing data
        ClearTiles();
        ClearItems();

        // start for x
        mBalloonX = root->GetAttributeDoubleValue(L"start-x", 0);

        // start for y
        mBalloonY = root->GetAttributeDoubleValue(L"start-y", 0);

        //
        // Traverse the children of the root
        // node of the XML document in memory!!!!
        //
        for (auto node : root->GetChildren())
        {
            if (node->GetType() == NODE_ELEMENT && node->GetName() == L"items")
            {
                XmlTile(node);
            }
            else if (node->GetType() == NODE_ELEMENT && node->GetName() == L"declarations")
            {
                XmlTile2(node);
            }
        }

    }
    catch (CXmlNode::Exception ex)
    {
        AfxMessageBox(ex.Message().c_str());
    }

}

/**
*  Handle a tile node.
* \param node Pointer to XML node we are handling
*/
void CGame::XmlTile(const std::shared_ptr<CXmlNode>& node)
{
    
    // A pointer for the item we are loading
    shared_ptr<CItem> item;

    for (auto node : node->GetChildren())
    {
        if (node->GetType() == NODE_ELEMENT)
        {
            // We have an item. What type?
            wstring type = node->GetName();
            if (node->GetName() == L"road")
            {
                XmlRoad(node);
            }
            else if (node->GetName() == L"house")
            {
                XmlHouse(node);
            }
            else if (node->GetName() == L"open")
            {
                XmlOpen(node);
            }
            else if (node->GetName() == L"trees")
            {
                XmlTrees(node);
            }

        }
        
        
    }
}


/**
*  Handle a declared item node.
* \param node Pointer to XML node we are handling
*/
void CGame::XmlTile2(const std::shared_ptr<CXmlNode>& node)
{
    // A pointer for the item we are loading
    shared_ptr<CDeclaredItem> item;

    for (auto node : node->GetChildren())
    {
        if (node->GetType() == NODE_ELEMENT)
        {
            // We have an item. What type?
            wstring type = node->GetName();
            if (node->GetName() == L"road")
            {
                item = make_shared<CDeclaredItem>(node);
            }
            else if (node->GetName() == L"house")
            {
                item = make_shared<CDeclaredItem>(node);
            }
            else if (node->GetName() == L"open")
            {
                item = make_shared<CDeclaredItem>(node);
            }
            else if (node->GetName() == L"trees")
            {
                item = make_shared<CDeclaredItem>(node);
            }

            if (item != nullptr)
            {
                Add2(item);
            }
        }
    }
    
}


/**
*  Clear the game data.
*
* Deletes all known items in the game.
*/
void CGame::ClearTiles()
{
    mTiles.clear();
}

/**
*  Clear the items data.
*
* Deletes all known declared items.
*/
void CGame::ClearItems()
{
    mItems.clear();
}


/**
*  Handle a road tile item.
* \param node Pointer to XML node we are handling
*/
void CGame::XmlRoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    double x = node->GetAttributeDoubleValue(L"x", 0);
    double y = node->GetAttributeDoubleValue(L"y", 0);
    std::wstring id = node->GetAttributeValue(L"id", L"");

    for (auto item : mItems)
    {
        wstring itemId = item->GetId();
       
        if (itemId == id)
        {
            std::wstring type = item->GetType();
            wstring image = item->GetImage();
            image = L"images/" + image;
            shared_ptr<CItem> newItem;
            newItem = make_shared<CTileRoad>(this, image, type);
            newItem->SetLocation(x, y);
            if (x == 2 && y == 6 && type == L"NS")
            {
                int x = 5;
            }
            Add(newItem);
        }
    }
}

/**
*  Handle an open tile item.
* \param node Pointer to XML node we are handling
*/
void CGame::XmlOpen(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    double x = node->GetAttributeDoubleValue(L"x", 0);
    double y = node->GetAttributeDoubleValue(L"y", 0);
    std::wstring id = node->GetAttributeValue(L"id", L"");

    for (auto item : mItems)
    {
        wstring itemId = item->GetId();
        if (itemId == id)
        {
            wstring image = item->GetImage();
            image = L"images/" + image;
            shared_ptr<CItem> newItem;
            newItem = make_shared<CTileOpen>(this, image);
            newItem->SetLocation(x, y);
            Add(newItem);
        }
    }
}


/**
*  Handle a tree tile item.
* \param node Pointer to XML node we are handling
*/
void CGame::XmlTrees(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    double x = node->GetAttributeDoubleValue(L"x", 0);
    double y = node->GetAttributeDoubleValue(L"y", 0);
    std::wstring id = node->GetAttributeValue(L"id", L"");

    for (auto item : mItems)
    {
        wstring itemId = item->GetId();
        if (itemId == id)
        {
            wstring image = item->GetImage();
            image = L"images/" + image;
            shared_ptr<CItem> newItem;
            newItem = make_shared<CTileTrees>(this, image);
            newItem->SetLocation(x, y);
            Add(newItem);
        }
    }
}

/**
*  Handle a house tile item.
* \param node Pointer to XML node we are handling
*/
void CGame::XmlHouse(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    double x = node->GetAttributeDoubleValue(L"x", 0);
    double y = node->GetAttributeDoubleValue(L"y", 0);
    std::wstring id = node->GetAttributeValue(L"id", L"");

    for (auto item : mItems)
    {
        wstring itemId = item->GetId();
        if (itemId == id)
        {
            wstring image = item->GetImage();
            image = L"images/" + image;
            shared_ptr<CItem> newItem;
            newItem = make_shared<CTileHouse>(this, image);
            newItem->SetLocation(x, y);
            Add(newItem);
        }
    }
}

/**
 * Draw the level start text
 * \param graphics The GDI+ graphics context to draw on
 * \param level Level number
 */
void CGame::DrawLevelStart(Gdiplus::Graphics* graphics, int level)
{
    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, 80, FontStyleBold);
    PointF origin(150, 400);
    SolidBrush red(Color(255, 0, 0));

    auto LevelString = L"Level " + to_wstring(level) + L" Begin";
    graphics->DrawString(LevelString.c_str(),  // String to draw
        -1,         // String length, -1 so it figures it out on its own
        &font,      // The font to use
        origin,		// Where to draw (top left corner)
        &red);    // The brush to draw the text with

    mLevel->SetJustLoaded(false);
}