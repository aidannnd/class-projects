/**
 * \file FishMagikarp.cpp
 *
 * \author Aidan Delfuoco
 */

#include "pch.h"
#include "FishMagikarp.h"
#include <string>

using namespace Gdiplus;
using namespace std;


/// Fish filename 
const wstring FishMagikarpImageName = L"images/Magikarp.png";

/** Constructor
 * \param aquarium The aquarium this is a member of
 */
CFishMagikarp::CFishMagikarp(CAquarium* aquarium) :
    CFish(aquarium, FishMagikarpImageName)
{
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 * \return itemNode
 */
std::shared_ptr<xmlnode::CXmlNode>
CFishMagikarp::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CItem::XmlSave(node);
    itemNode->SetAttribute(L"type", L"magikarp");

    return itemNode;
}