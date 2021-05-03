/**
 * \file Dart.cpp
 *
 * \author Ryan Piotrowicz
 */

#include "pch.h"
#include "Dart.h"

 /// Dart filename
const std::wstring DartImageName = L"images/dart.png";

/// Dart speed (virtual pixels per second)
const double DartSpeed = 100;

/// Dart range (pixels)
const double DartRange = 90;

/**
 * Constructor
 * \param game The game this dart belongs to
 */
CDart::CDart(CGame* game) : CProjectile(game, DartImageName)
{
	SetSpeed(DartSpeed);
	SetMaxRange(DartRange);
}

