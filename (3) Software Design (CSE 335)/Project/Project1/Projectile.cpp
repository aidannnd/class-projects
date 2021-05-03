/**
 * \file Projectile.cpp
 *
 * \author Ryan Piotrowicz
 */

#include "pch.h"
#include "Projectile.h"

using namespace std;
using namespace Gdiplus;

/// Constant to covert radians to degrees.
const double RtoD = 57.2957795;

/**
 * Constructor
 * \param game The game this projectile belongs to
 * \param filename The image filename of the projectile
 */
CProjectile::CProjectile(CGame* game, const std::wstring& filename) : CItem(game, filename)
{
    mProjectileImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
    if (mProjectileImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += filename;
        AfxMessageBox(msg.c_str());
    }
}

void CProjectile::Update(double elapsed)
{
    mDistanceTraveled += elapsed * GetSpeed();
    if (mDistanceTraveled >= GetMaxRange())
    {
        GetGame()->AddToRemove(shared_from_this());
    }
    double a = GetAngle();
    double sn = sin(a);
    double cs = cos(a);

    double x = GetX() + cs * (elapsed * GetSpeed());
    double y = GetY() + sn * (elapsed * GetSpeed());

    SetLocation(x, y);

    for (auto item : GetGame()->GetItems())
    {
        if (item->GetType() == "Balloon")
        {
            double dx = item->GetX() - GetX();
            double dy = item->GetY() - GetY();
            double distance = sqrt((dx * dx) + (dy * dy));
            if (distance <= 30)
            {
                item->BalloonHit();
                GetGame()->AddToRemove(item);
                GetGame()->UpdateScore(10);
            }
        }
    }
}


/**
 * Draws projectiles
 * \param graphics Graphics
 */
void CProjectile::Draw(Gdiplus::Graphics* graphics)
{
    ProjectileDraw(graphics, 0, 0);
}

/**
 * Draw the rotated projectile. Rotation is determined by the member
 * variable mAngle, which is the rotation in radians.
 *
 * @param graphics The graphics context to draw on.
 * @param offsetX An X offset added to the position of the projectile.
 * @param offsetY A Y offset added to the position of the projectile.
 */
void CProjectile::ProjectileDraw(Gdiplus::Graphics* graphics, int offsetX, int offsetY)
{
    int wid = mProjectileImage->GetWidth();
    int hit = mProjectileImage->GetHeight();
    auto save = graphics->Save();
    graphics->TranslateTransform((REAL)(GetX() + offsetX),
        (REAL)(GetY() + offsetY));
    graphics->RotateTransform((REAL)(mAngle * RtoD));
    graphics->DrawImage(mProjectileImage.get(), 0, 0, wid, hit);
    graphics->Restore(save);
}