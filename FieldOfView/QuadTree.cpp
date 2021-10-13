#include "QuadTree.h"
#include "WinMin.h"

uint32 QuadTree::lastID = 0;
QuadTree* QuadTree::rootPtr = nullptr;
bool QuadTree::isTreeReady = false;
std::queue<TreeAgent*> QuadTree::instertQueue = std::queue<TreeAgent*>();
std::unordered_map<uint32, TreeAgent> QuadTree::globalAgentMap = std::unordered_map<uint32, TreeAgent>();

using UMPair = std::pair<uint32,TreeAgent>;

QuadTree::QuadTree(Box inbounds, int8 level) : bounds(inbounds)
{
	levelOfQuadTree = level;
}

QuadTree* QuadTree::MakeNewRoot()
{
	if (rootPtr)
	{
		CritErr("QuadTree Root Already Created");
	}

	rootPtr = new QuadTree(Box(0, 0, AppSettings::WorldSize, AppSettings::WorldSize),0);
	return rootPtr;
}

QuadTree* QuadTree::GetRoot()
{
	if (!rootPtr) { CritErr("CantGet RootPtr");  }

	return rootPtr;
}

void QuadTree::BuildTree()
{
	//NW
	childTreesArray.push_back(QuadTree(Box(	bounds.left, bounds.top,
											bounds.width / 2.f, bounds.height / 2.f), levelOfQuadTree+1));
	//NE
	childTreesArray.push_back(QuadTree(Box(	bounds.left + bounds.width / 2.f, bounds.top,
											bounds.width / 2.f, bounds.height / 2.f), levelOfQuadTree + 1));
	//SW
	childTreesArray.push_back(QuadTree(Box(	bounds.left, bounds.top + bounds.height / 2.f,
											bounds.width / 2.f,bounds.height / 2.f), levelOfQuadTree + 1));
	//SE
	childTreesArray.push_back(QuadTree(Box(	bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f,
											bounds.width / 2.f,bounds.height / 2.f), levelOfQuadTree + 1));

	if (levelOfQuadTree + 1 < maxLevel) { childTreesArray[0].BuildTree(); }
	if (levelOfQuadTree + 1 < maxLevel) { childTreesArray[1].BuildTree(); }
	if (levelOfQuadTree + 1 < maxLevel) { childTreesArray[2].BuildTree(); }
	if (levelOfQuadTree + 1 < maxLevel) { childTreesArray[3].BuildTree(); }
}

void QuadTree::UpdateTree()
{
}

void QuadTree::AddAgent(TreeAgent agent)
{
	//insert agent data to global map
	agent.SetID(lastID);
	globalAgentMap.insert(UMPair(lastID, agent));
	//add ptr to agent in map to queue for insertion in tree
	instertQueue.push(&(globalAgentMap.at(lastID)));
	++lastID;
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




