/**
 * \file DeclaredItem.cpp
 *
 * \author Patrick Doyle
 */


#include "pch.h"
#include <iostream>
#include "DeclaredItem.h"

using namespace std;

/**
 * Constructor
 * @param node the Xml node for this declare
 */
CDeclaredItem::CDeclaredItem(std::shared_ptr<xmlnode::CXmlNode> node)
{
    mId = node->GetAttributeValue(L"id", L"");
    mImage = node->GetAttributeValue(L"image", L"");
    mType = node->GetAttributeValue(L"type", L"");
}

