/**
 * \file FishBeta.h
 *
 * \author Aidan Delfuoco
 *
 * Class that represents a Beta fish.
 */

#pragma once
#include "Fish.h"

 /**
  * Implements a Beta fish
  */
class CFishBeta : public CFish
{
public:
    CFishBeta::CFishBeta(CAquarium* aquarium);

    /// Default constructor (disabled)
    CFishBeta() = delete;

    /// Copy constructor (disabled)
    CFishBeta(const CFishBeta&) = delete;

    virtual std::shared_ptr<xmlnode::CXmlNode>
        XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
};

