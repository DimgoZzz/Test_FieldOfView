#include "QuadTree.h"
#include "WinMin.h"

#pragma region StaticInit
uint32 QuadTree::lastID = 0;
QuadTree* QuadTree::rootPtr = nullptr;
std::queue<TreeAgent*> QuadTree::instertQueue = std::queue<TreeAgent*>();
std::unordered_map<uint32, TreeAgent> QuadTree::globalAgentMap = std::unordered_map<uint32, TreeAgent>();
#pragma endregion StaticInit

using UAPair = std::pair<uint32, TreeAgent>;

QuadTree::QuadTree(Box box, int8 dlvl, QuadTree* parent) : bounds(box)
{
	depthLevel = dlvl;
}

QuadTree::~QuadTree()
{
	if (depthLevel==0) { ClearStaticData(); }
}

QuadTree* QuadTree::MakeRoot()
{
	if (rootPtr)
	{
		CritErr("QuadTree Root Already Created");
	}

	rootPtr = new QuadTree(Box(0, 0, AppSettings::WorldSize, AppSettings::WorldSize), 0, nullptr);
	return rootPtr;
}

QuadTree* QuadTree::GetRoot()
{
	if (!rootPtr) { CritErr("CantGet RootPtr");  }

	return rootPtr;
}

void QuadTree::AddAgent(TreeAgent agent)
{
	uint32 id = NextID();
	//insert agent data to global map
	agent.SetID(id);
	globalAgentMap.insert(UAPair(id, agent));
	//add ptr to agent in map to queue for insertion in tree
	instertQueue.push(&(globalAgentMap.at(id)));
}

void QuadTree::BuildTree()
{
	//NW
	childTreesArray.push_back(QuadTree(Box(bounds.left, bounds.top,
		bounds.width / 2.f, bounds.height / 2.f), depthLevel + 1, this));
	//NE
	childTreesArray.push_back(QuadTree(Box(bounds.left + bounds.width / 2.f, bounds.top,
		bounds.width / 2.f, bounds.height / 2.f), depthLevel + 1, this));
	//SW
	childTreesArray.push_back(QuadTree(Box(bounds.left, bounds.top + bounds.height / 2.f,
		bounds.width / 2.f, bounds.height / 2.f), depthLevel + 1, this));
	//SE
	childTreesArray.push_back(QuadTree(Box(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f,
		bounds.width / 2.f, bounds.height / 2.f), depthLevel + 1, this));
	if ((depthLevel + 1) < maxLevel)
	{
		for (int8 i = 0; i < 4; ++i)
		{
			childTreesArray[i].BuildTree();
		}
	}
}


//ToDo
void QuadTree::UpdateTree()
{
	TreeAgent* agentref = nullptr;
	while (!instertQueue.empty())
	{
	//	agentref = instertQueue.front();
	//	bool succes = FeedAgentToTree(agentref);
	//	if (!succes) { CritErr("Cant Feed Agent to Tree"); }
	//	instertQueue.pop();
	}

}
//
//void QuadTree::PerformVisionChecks()
//{
//
//	for (auto& a1 : treeAgents)
//	{
//		//Do checks with tree attached agents 
//		for (auto& a2 : treeAgents)
//		{
//			a1->seeCount += a1->CanSeeAgent(a2);
//		}
//		//Do Checks with child trees agents
//		for (auto& t1 : childTreesArray)
//		{
//			for (auto& a2 : t1.treeAgents)
//			{
//				a1->seeCount += a1->CanSeeAgent(a2);
//			}
//		}
//
//	}
//}

#pragma region Private

uint32 QuadTree::NextID()
{
	return (++lastID);
}

void QuadTree::ClearStaticData()
{
	globalAgentMap.clear();
	lastID = 0;
	while (!instertQueue.empty())
	{
		instertQueue.pop();
	}
	rootPtr = nullptr;
}



////ToDo
//bool QuadTree::FeedAgentToTree(TreeAgent* agentPtr)
//{
//	if (isFinalBranch)
//		//Insert
//	{
//		treeAgents.push_back(agentPtr);
//		return true;
//	}
//	else
//		//Find FinalBranch
//	{
//		int8 childcaneatagent = getQuadrant(*agentPtr, bounds);;
//		//GetChildThatCanEatAgent()
//		//for (int8 i=0; i<childTreesArray.size();++i)
//		//{
//		//	if (CanEatAgent(agentPtr)) { childcaneatagent = i; break; }
//		//}
//
//		//FeedAgentToChile
//		if (childcaneatagent != -1)
//		{
//			if (childTreesArray[childcaneatagent].FeedAgentToTree(agentPtr)) { return true; }
//			else { CritErr("uhh"); };
//		}
//		//IfNoChildCanEat
//		//Attach to self
//		treeAgents.push_back(agentPtr);
//
//		return true;
//	}
//
//	return false;
//}
//
//bool QuadTree::CanEatAgent(TreeAgent* agentPtr)
//{
//	return	(bounds.left < agentPtr->GetLeftBound()) && (bounds.GetRight() > agentPtr->GetLeftBound()) &&
//		(bounds.top < agentPtr->GetLeftBound()) && (bounds.GetBottom() > agentPtr->GetLeftBound());
//}

#pragma endregion Private





