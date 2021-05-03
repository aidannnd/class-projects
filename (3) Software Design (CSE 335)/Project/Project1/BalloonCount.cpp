#include "pch.h"
#include "BalloonCount.h"

/** Visit a CBalloon object
* \param balloon Balloon tile we are visiting */
void CBalloonCount::VisitBalloon(CBalloon* balloon)
{
	mBalloonCount += 1;
}
