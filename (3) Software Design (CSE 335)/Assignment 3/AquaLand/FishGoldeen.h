/**
 * \file FishGoldeen.h
 *
 * \author Aidan Delfuoco
 *
 * Class that represents a Goldeen fish.
 */

#pragma once
#include "Fish.h"

 /**
  * Implements a Goldeen fish
  */
class CFishGoldeen : public CFish
{
public:
    CFishGoldeen::CFishGoldeen(CAquarium* aquarium);

    /// Default constructor (disabled)
    CFishGoldeen() = delete;

    /// Copy constructor (disabled)
    CFishGoldeen(const CFishGoldeen&) = delete;

    virtual std::shared_ptr<xmlnode::CXmlNode>
        XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
};

