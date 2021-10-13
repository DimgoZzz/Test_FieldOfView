#include "QuadTree.h"
#include "WinMin.h"

uint32 QuadTree::lastID = 0;
QuadTree* QuadTree::rootPtr = nullptr;
bool QuadTree::isTreeReady = false;

using UMPair = std::pair<uint32,TreeAgent>;

QuadTree::QuadTree(Box inbounds) : bounds(inbounds)
{

}

QuadTree* QuadTree::MakeNewRoot()
{
	if (rootPtr)
	{
		CritErr("QuadTree Root Already Created");
	}

	rootPtr = new QuadTree(Box(-(AppSettings::WorldSize / 2.f), (AppSettings::WorldSize / 2.f), AppSettings::WorldSize, AppSettings::WorldSize));
	return rootPtr;
}

QuadTree* QuadTree::GetRoot()
{
	if (rootPtr) { return rootPtr; }
	else { (CritErr("CantGet RootPtr")); }
}

void QuadTree::BuildTree()
{
	//NW
	childTreesArray.push_back(QuadTree(Box(	bounds.left, bounds.top,
											bounds.width / 2.f, bounds.height / 2.f)));
	//NE
	childTreesArray.push_back(QuadTree(Box(	bounds.left + bounds.width / 2.f, bounds.top,
											bounds.width / 2.f, bounds.height / 2.f)));
	//SW
	childTreesArray.push_back(QuadTree(Box(	bounds.left, bounds.top - bounds.height / 2.f, bounds.width / 2.f,
											bounds.height / 2.f)));
	//SE
	childTreesArray.push_back(QuadTree(Box(	bounds.left + bounds.width, bounds.top - bounds.height, bounds.width / 2.f,
											bounds.height / 2.f)));
}

void QuadTree::UpdateTree()
{
}

void QuadTree::AddAgent(TreeAgent agent)
{
	//insert agent data to global map
	agent.SetID(lastID);
	globalAgentMap.insert(UMPair(lastID++, agent));
	//add ptr to agent in map to queue for insertion in tree
	instertQueue.push(&(globalAgentMap.at(lastID - 1)));
	isTreeReady = false;
}

QuadTree::~QuadTree()
{
	if (isRoot) { ClearStaticData(); }
}

void QuadTree::ClearStaticData()
{
	globalAgentMap.clear();
	lastID = 0;
	while (!instertQueue.empty())
	{
		instertQueue.pop();
	}
	
}




