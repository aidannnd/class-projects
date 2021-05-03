#pragma once
#include "Item.h"

 /**
  * Implements a Castle decor
  */
class CDecorCastle : public CItem
{
public:
    CDecorCastle::CDecorCastle(CAquarium* aquarium);

    /// Default constructor (disabled)
    CDecorCastle() = delete;

    /// Copy constructor (disabled)
    CDecorCastle(const CDecorCastle&) = delete;

    /// Save the XML
    virtual std::shared_ptr<xmlnode::CXmlNode>
        XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
};

