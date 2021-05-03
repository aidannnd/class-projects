/**
 * \file FishMagikarp.h
 *
 * \author Aidan Delfuoco
 *
 * Class that represents a Magikarp fish.
 */

#pragma once
#include "Fish.h"

 /**
  * Implements a Magikarp fish
  */
class CFishMagikarp : public CFish
{
public:
    CFishMagikarp::CFishMagikarp(CAquarium* aquarium);

    /// Default constructor (disabled)
    CFishMagikarp() = delete;

    /// Copy constructor (disabled)
    CFishMagikarp(const CFishMagikarp&) = delete;

    virtual std::shared_ptr<xmlnode::CXmlNode>
        XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
};

