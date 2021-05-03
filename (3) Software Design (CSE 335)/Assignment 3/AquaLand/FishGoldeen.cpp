/**
 * \file FishGoldeen.cpp
 *
 * \author Aidan Delfuoco
 */

#include "pch.h"
#include "FishGoldeen.h"
#include <string>

using namespace Gdiplus;
using namespace std;


/// Fish filename 
const wstring FishGoldeenImageName = L"images/Goldeen.png";

/** Constructor
 * \param aquarium The aquarium this is a member of
 */
CFishGoldeen::CFishGoldeen(CAquarium* aquarium) :
    CFish(aquarium, FishGoldeenImageName)
{
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 * \return itemNode
 */
std::shared_ptr<xmlnode::CXmlNode>
CFishGoldeen::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CItem::XmlSave(node);
    itemNode->SetAttribute(L"type", L"goldeen");

    return itemNode;
}