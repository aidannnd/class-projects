/**
 * \file Balloon.cpp
 *
 * \author Aidan Delfuoco
 */

#include "pch.h"
#include "Balloon.h"

using namespace std;
using namespace Gdiplus;

/// Balloon filename
const std::wstring BalloonImageName = L"images/red-balloon.png";

/// Balloon speed (pixels/second)
const double SPEED = 128;

/** 
 * Default constructor
 * \param game Main game
 * \param filename File of image
 */
CBalloon::CBalloon(CGame* game, const std::wstring& filename) : CItem(game, BalloonImageName)
{
    SetSpeed(SPEED);
}


/**
 * Updates balloons
 * \param elapsed Time elapsed
 */
void CBalloon::Update(double elapsed)
{
    auto game = GetGame();
    auto currRoad = game->HitTestForRoad(GetX(), GetY());
    if (currRoad != nullptr)
    {
        auto type = currRoad->GetRoadType();
        if (type == L"EW")
        {
            if (mSetBy.find("right") != std::string::npos)
            {
                // balloon moving right on EW tile
                mXMultiplier = 1;
                mYMultiplier = 0;
            }
            else if (mSetBy.find("left") != std::string::npos)
            {
                // balloon moving left on EW tile
                mXMultiplier = -1;
                mYMultiplier = 0;
            }
        }
        else if (type == L"NS")
        {
            if (mSetBy.find("up") != std::string::npos)
            {
                // balloon moving up on EW tile
                mXMultiplier = 0;
                mYMultiplier = -1;
            }
            else if (mSetBy.find("down") != std::string::npos)
            {
                // balloon moving down on EW tile
                mXMultiplier = 0;
                mYMultiplier = 1;
            }
        }
        else if (type == L"NW")
        {
            if (mYMultiplier == 0 && mSetBy != "NW left")
            {
                // checking if the balloon is in the middle of NW title
                if (GetX() >= (currRoad->GetX() + .5) * 64)
                {
                    // balloon moving up on NW tile
                    mXMultiplier = 0;
                    mYMultiplier = -1;
                    mSetBy = "NW up";
                }
            }
            else if (mYMultiplier != 0 && mSetBy != "NW up")
            {
                // checking if the balloon is in the middle of NW title
                if (GetY() >= (currRoad->GetY() + .5) * 64)
                {
                    // balloon moving left on NW tile
                    mXMultiplier = -1;
                    mYMultiplier = 0;
                    mSetBy = "NW left";
                }
            }
        }
        else if (type == L"SE")
        {
            if (mYMultiplier != 0 && mSetBy != "SE down")
            {
                // checking if the balloon is in the middle of SE title
                if (GetY() <= (currRoad->GetY() + .5) * 64)
                {
                    // balloon moving right on SE tile
                    mXMultiplier = 1;
                    mYMultiplier = 0;
                    mSetBy = "SE right";
                }
            }
            else if (mYMultiplier == 0 && mSetBy != "SE right")
            {
                // checking if the balloon is in the middle of SE title
                if (GetX() <= (currRoad->GetX() + .5) * 64)
                {
                    // balloon moving down on SE tile
                    mXMultiplier = 0;
                    mYMultiplier = 1;
                    mSetBy = "SE down";
                }
            }
        }
        else if (type == L"SW")
        {
            if (mYMultiplier != 0 && mSetBy != "SW down")
            {
                // checking if the balloon is in the middle of SW title
                if (GetY() <= (currRoad->GetY() + .5) * 64)
                {
                    // balloon moving left on SE tile
                    mXMultiplier = -1;
                    mYMultiplier = 0;
                    mSetBy = "SW left";
                }
            }
            else if (mYMultiplier == 0 && mSetBy != "SW left")
            {
                // checking if the balloon is in the middle of SW title
                if (GetX() >= (currRoad->GetX() + .5) * 64)
                {
                    // balloon moving down on SE tile
                    mXMultiplier = 0;
                    mYMultiplier = 1;
                    mSetBy = "SW down";
                }
            }
        }
        else if (type == L"NE")
        {
            if (mYMultiplier != 0 && mSetBy != "NE up")
            {
                // checking if the balloon is in the middle of NE title
                if (GetY() >= (currRoad->GetY() + .5) * 64)
                {
                    // balloon moving right on NE tile
                    mXMultiplier = 1;
                    mYMultiplier = 0;
                    mSetBy = "NE right";
                }
            }
            else if (mYMultiplier == 0 && mSetBy != "NE right")
            {
                // checking if the balloon is in the middle of NE title
                if (GetX() <= (currRoad->GetX() + .5) * 64)
                {
                    // balloon moving up on NE tile
                    mXMultiplier = 0;
                    mYMultiplier = -1;
                    mSetBy = "NE up";
                }
            }
        }
        SetLocation(GetX() + (mSpeed * mXMultiplier )* elapsed, GetY() + (mSpeed * mYMultiplier) * elapsed);
    }
    else
    {
        if (mScoreUpdated == false)
        {
            mScoreUpdated = true;
        }
    }
}