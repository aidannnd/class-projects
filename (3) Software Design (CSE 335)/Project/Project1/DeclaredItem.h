/**
 * \file DeclaredItem.h
 *
 * \author Patrick Doyle
 *
 * Class for an item in the declarations XML section.
 */


#pragma once
#include "XmlNode.h"

 /**
  * Class for an item in the declarations XML section.
  */
class CDeclaredItem
{
public:
    CDeclaredItem(std::shared_ptr<xmlnode::CXmlNode> node);

    /**  The id of the item
    * \returns mId  */
    std::wstring GetId() { return mId; }

    /**  The image of the item
    * \returns mImage  */
    std::wstring GetImage() { return mImage; }

    /**  The type of the item
    * \returns mType  */
    std::wstring GetType() { return mType; }

    /// Updates CDeclaredItem
    /// \param elapsed Time
    void Update(double elapsed) {}

private:
    /// The ID for this definition
    std::wstring mId;

    /// The image for this definition
    std::wstring mImage;

    /// The type for this definition
    std::wstring mType;

};


