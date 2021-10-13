#include "QuadTree.h"
#include "WinMin.h"

#pragma region StaticInit
uint32 QuadTree::lastID = 0;
QuadTree* QuadTree::rootPtr = nullptr;
bool QuadTree::isTreeReady = false;
std::queue<TreeAgent*> QuadTree::instertQueue = std::queue<TreeAgent*>();
std::unordered_map<uint32, TreeAgent> QuadTree::globalAgentMap = std::unordered_map<uint32, TreeAgent>();
#pragma endregion StaticInit

using UMPair = std::pair<uint32, TreeAgent>;

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
	if (levelOfQuadTree + 1 < maxLevel)
	{
		for (int8 i = 0; i < 4; ++i)
		{
			childTreesArray[i].BuildTree();
		}
	}
	else 
	for (int8 i = 0; i < 4; ++i)
	{
		childTreesArray[i].isFinalBranch = true;
	}
}

void QuadTree::UpdateTree()
{
	TreeAgent* agentref = nullptr;
	while (!instertQueue.empty())
	{
		agentref = instertQueue.front();
		bool succes = FeedAgentToTree(agentref);
		if (!succes) { CritErr("Cant Feed Agent to Tree"); }
		instertQueue.pop();
	}
	
}

void QuadTree::DoVisionChecks()
{
	
	for (auto& a1 : treeAgents)
	{	
		//Do checks with tree attached agents 
		for (auto& a2 : treeAgents)
		{
			a1->seeCount += a1->CanSeeAgent(a2);
		}
		//Do Checks with child trees agents
		for (auto& t1 : childTreesArray)
		{
			for (auto& a2 : t1.treeAgents)
			{
				a1->seeCount += a1->CanSeeAgent(a2);
			}
		}

	}
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

int getQuadrant(const TreeAgent nodeBox, const Box valueBox)
{
	auto center = nodeBox.agentLocation;
	// West
	if (valueBox.GetRight() < center.GetX())
	{
		// North West
		if (valueBox.GetBottom() < center.GetY())
			return 0;
		// South West
		else if (valueBox.top >= center.GetY())
			return 2;
		// Not contained in any quadrant
		else
			return -1;
	}
	// East
	else if (valueBox.left >= center.GetX())
	{
		// North East
		if (valueBox.GetBottom() < center.GetY())
			return 1;
		// South East
		else if (valueBox.top >= center.GetY())
			return 3;
		// Not contained in any quadrant
		else
			return -1;
	}
	// Not contained in any quadrant
	else
		return -1;
}

bool QuadTree::FeedAgentToTree(TreeAgent* agentPtr)
{
	if (isFinalBranch)
	//Insert
	{
		treeAgents.push_back(agentPtr);
		return true;
	}
	else
	//Find FinalBranch
	{
		int8 childcaneatagent = getQuadrant(*agentPtr, bounds);;
		//GetChildThatCanEatAgent()
		//for (int8 i=0; i<childTreesArray.size();++i)
		//{
		//	if (CanEatAgent(agentPtr)) { childcaneatagent = i; break; }
		//}

		//FeedAgentToChile
		if (childcaneatagent != -1)
		{
			if (childTreesArray[childcaneatagent].FeedAgentToTree(agentPtr)) { return true; }
			else { CritErr("uhh"); };
		}
		//IfNoChildCanEat
		//Attach to self
		treeAgents.push_back(agentPtr);
		
		return true;
	}

	return false;
}

bool QuadTree::CanEatAgent(TreeAgent* agentPtr)
{
	return	(bounds.left< agentPtr->GetLeftBound())&& (bounds.GetRight() > agentPtr->GetLeftBound())&&
			(bounds.top < agentPtr->GetLeftBound())&& (bounds.GetBottom() > agentPtr->GetLeftBound());
}



