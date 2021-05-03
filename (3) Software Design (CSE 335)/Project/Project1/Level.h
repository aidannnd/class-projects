/**
 * \file Level.h
 *
 * \author Brian Kim
 *
 * Class that implements a level with tiles
 */

#pragma once

#include <memory>
#include <vector>
#include "Item.h"
#include "Game.h"



 /**
  * Class for a level
  */
class CLevel
{
public:
    CLevel(CGame* game, int number);
    virtual ~CLevel();

    void Load(CGame* game, int number);

    /** The current level
     * \returns int level number */
    int GetCurLevel() { return mCurLevel; }

    /** Set the current level
     * \param curLevel Level to be set */
    void SetCurLevel(int curLevel) { mCurLevel = curLevel; }

    /** Whether the level was previously loaded
     * \returns bool true if level was previously loaded */
    bool GetJustLoaded() { return mLoaded; }

    /** Set the previously loaded status
     * \param loaded Bool to be set */
    void SetJustLoaded(bool loaded) { mLoaded = loaded; }

private:
    /// The game this level is a part of
    CGame* mGame;

    /// Level 0
    std::wstring mLevel0 = L"levels/level0.xml";

    /// Level 1
    std::wstring mLevel1 = L"levels/level1.xml";

    /// Level 2
    std::wstring mLevel2 = L"levels/level2.xml";

    /// Level 3
    std::wstring mLevel3 = L"levels/level3.xml";

    /// The current level
    int mCurLevel = 0;

    /// If the level was just loaded
    bool mLoaded = false;
};
