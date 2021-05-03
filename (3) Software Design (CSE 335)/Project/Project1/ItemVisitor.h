/**
 * \file ItemVisitor.h
 *
 * \author Brian Kim
 *
 * Item visitor base class.
 */

#pragma once

 /// Forward references to all item types
class CBalloon;
class CDart;
class CExplosion;
class CLaser;
class CRing;
class CTileHouse;
class CTileOpen;
class CTileRoad;
class CTileTrees;
class CTowerBomb;
class CTowerCustom;
class CTowerEight;
class CTowerRing;

/** Item visitor base class */
class CItemVisitor
{
public:
    virtual ~CItemVisitor() {}

    /** Visit a CBalloon object
     * \param balloon Balloon we are visiting */
    virtual void VisitBalloon(CBalloon* balloon) {}

    /** Visit a CDart object
     * \param dart Dart we are visiting */
    virtual void VisitDart(CDart* dart) {}

    /** Visit a CExplosion object
     * \param explosion Explosion we are visiting */
    virtual void VisitExplosion(CExplosion* explosion) {}

    /** Visit a CLaser object
     * \param laser Laser we are visiting */
    virtual void VisitLaser(CLaser* laser) {}
    
    /** Visit a CRing object
     * \param ring Ring we are visiting */
    virtual void VisitRing(CRing* ring) {}

    /** Visit a CTileHouse object
     * \param house House tile we are visiting */
    virtual void VisitTileHouse(CTileHouse* house) {}

    /** Visit a CTileOpen object
     * \param open Open tile we are visiting */
    virtual void VisitTileOpen(CTileOpen* open) {}

    /** Visit a CTileRoad object
     * \param road Road tile we are visiting */
    virtual void VisitTileRoad(CTileRoad* road) {}

    /** Visit a CTileTrees object
     * \param trees Trees we are visiting */
    virtual void VisitTileTrees(CTileTrees* trees) {}

    /** Visit a CTowerBomb object
     * \param bomb Bomb tower we are visiting */
    virtual void VisitTowerBomb(CTowerBomb* bomb) {}

    /** Visit a CTowerCustom object
     * \param custom Custom tower we are visiting */
    virtual void VisitTowerCustom(CTowerCustom* custom) {}

    /** Visit a CTowerEight object
     * \param eight Eight tower we are visiting */
    virtual void VisitTowerEight(CTowerEight* eight) {}

    /** Visit a CTowerRing object
     * \param ring Ring tower we are visiting */
    virtual void VisitTowerRing(CTowerRing* ring) {}
};