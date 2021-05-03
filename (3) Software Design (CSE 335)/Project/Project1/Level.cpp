/**
 * \file Level.cpp
 *
 * \author Brian Kim
 */

#include "pch.h"
#include "Level.h"

using namespace std;

/**
*  Constructor
* \param game The main game
* \param number The level we are loading
*/
CLevel::CLevel(CGame* game, int number)
{
    mGame = game;
    mCurLevel = number;

    switch (number)
    {
    case 0:
        mGame->Load(mLevel0);
        break;

    case 1:
        mGame->Load(mLevel1);
        break;

    case 2:
        mGame->Load(mLevel2);
        break;

    case 3:
        mGame->Load(mLevel3);
        break;
    }
    mLoaded = true;
}

/**
*  Destructor
*/
CLevel::~CLevel()
{
}

/**
*  Dedicated load function
* \param game The main game
* \param number The level we are loading
*/
void CLevel::Load(CGame* game, int number)
{
    mGame = game;
    mCurLevel = number;

    switch (number)
    {
    case 0:
        mGame->Load(mLevel0);
        break;

    case 1:
        mGame->Load(mLevel1);
        break;

    case 2:
        mGame->Load(mLevel2);
        break;

    case 3:
        mGame->Load(mLevel3);
        break;
    }
    mLoaded = true;

}