/**
 * \file BalloonCount.h
 *
 * \author Brandon Byiringiro
 *
 * Balloon tile counter class.
 */

#pragma once
#include "ItemVisitor.h"


/**
 * Class for CBalloonCount
 * Counts the balloons
 */
class CBalloonCount :
    public CItemVisitor
{
public:
    /** Get the number of balloon towers
     * \returns Number of balloon towers */
    int GetBalloonCount() const { return mBalloonCount; }

    void VisitBalloon(CBalloon* balloon);

private:
    /// Balloon counter
    int mBalloonCount = 0;

};

