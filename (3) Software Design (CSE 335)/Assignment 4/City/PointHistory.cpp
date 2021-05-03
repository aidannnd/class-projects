/**
 * \file PointHistory.cpp
 *
 * \author Aidan Delfuoco
 */


#include "pch.h"
#include "PointHistory.h"


using namespace std;
using namespace Gdiplus;


/// the initial capacity of the points collection
const int InitialSize = 4;

/**
 * Constructor
 */
CPointHistory::CPointHistory()
{
    // See the random number generator
    std::random_device seeder;
    auto s = seeder();
    mRandInt.seed(seeder());

    // The collection of points initially has a capacity of 
    // four points.
    mPoints.resize(InitialSize);

    // There is only one location in the collection and 
    // it is availale to use.
    for (int i = 0; i < InitialSize; i++)
    {
        mAvailables.push_back(i);
    }

    // And shuffle them
    shuffle(mAvailables.begin(), mAvailables.end(), mRandInt);

    // Empty list
    mPointFirst = -1;
    mPointLast = -1;
}

/**
 * Destructor
 */
CPointHistory::~CPointHistory()
{
}

/**
 * Add a pointer to the collection of points.
 * \param p Point to add
 */
void CPointHistory::Add(Gdiplus::Point p)
{
    if (mAvailables.empty())
    {
        // There are no available locations. 
        // Make space by doubling the size of the array
        // and add that to available.
        auto currentSize = mPoints.size();
        mPoints.resize(currentSize * 2);
        for (auto i = currentSize; i < mPoints.size(); i++)
        {
            mAvailables.push_back(i);
        }

        // And shuffle them
        shuffle(mAvailables.begin(), mAvailables.end(), mRandInt);
    }

    // Remove an available location from the collection
    // of available locations.
    int point = mAvailables.back();
    mAvailables.pop_back();

    mPoints[point].mPoint = p;
    mPoints[point].mNext = -1;

    if (mPointFirst < 0)
    {
        // The list was previously empty. Make it a list of 
        // this one point.
        mPointFirst = point;
        mPointLast = point;
    }
    else
    {
        // Make previous last location point to this 
        // and make it the next last point
        mPoints[mPointLast].mNext = point;
        mPointLast = point;
    }

}