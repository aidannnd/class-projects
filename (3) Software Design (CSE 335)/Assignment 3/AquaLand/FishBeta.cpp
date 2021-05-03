/**
 * \file FishBeta.cpp
 *
 * \author Aidan Delfuoco
 */

#include "pch.h"
#include "FishBeta.h"
#include <string>

using namespace Gdiplus;
using namespace std;


/// Fish filename 
const wstring FishBetaImageName = L"images/beta.png";

/** Constructor
 * \param aquarium The aquarium this is a member of
 */
CFishBeta::CFishBeta(CAquarium* aquarium) :
    CFish(aquarium, FishBetaImageName)
{
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 * \return itemNode
 */
std::shared_ptr<xmlnode::CXmlNode>
CFishBeta::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CItem::XmlSave(node);
    itemNode->SetAttribute(L"type", L"beta");

    return itemNode;
}