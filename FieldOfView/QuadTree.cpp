#include "QuadTree.h"
#include "WinMin.h"

#pragma region StaticInit
uint32 QuadTree::lastID = -1;
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
		agentref = instertQueue.front();
		bool succes = InsertAgentToTree(agentref);
		if (!succes) { CritErr("Cant Feed Agent to Tree"); }
		instertQueue.pop();
	}
}

void QuadTree::PerformVisionChecks()
{
	static std::vector<TreeAgent*> bordercollisionguys;
	bordercollisionguys.reserve(AppSettings::MaxUnits);
	//If last branch - calculate all agent of tree
	if (depthLevel == maxLevel)
	{
		for (auto& a1 : treeAgents)
		{
		for (auto& a2 : treeAgents)
		{
			a1->seeCount += a1->CanSeeAgent(a2);
		}
		}
	}
	////////////////////////////////////////////////////
	else
	{
		for (auto& a1 : treeAgents)
		{
			bordercollisionguys.push_back(a1);
		}
		for (auto& t : childTreesArray)
		{
			t.PerformVisionChecks();
		}
	}
	if (depthLevel == 0)
	{
		for (auto& a1 : bordercollisionguys)
		{
			for (auto& a2 : globalAgentMap)
			{
				a1->CanSeeAgent(&(a2.second));
			}
		}
	}
}

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

bool QuadTree::InsertAgentToTree (TreeAgent* agentPtr)
{
	if (!(depthLevel == maxLevel))
	{
		//Get Agent Pos Region
		TreeDirection childRegion = GetQuadrant(agentPtr, &bounds);
		
		// Add the value in a child if the value is entirely contained in it
		bool intersects = IntersectBounds(agentPtr, bounds);

		//If intesects throw back, if not root
		if (intersects)
		{
			if (depthLevel == 0)
			{
				treeAgents.push_back(agentPtr);
				return true;
			}
			else
			{
				return false;
			}
		}
		//If No intersects
		else
		{
			if (childRegion == TreeDirection::None)
			{
				treeAgents.push_back(agentPtr); 
				return true; 
			}

			bool succ = childTreesArray[static_cast<int8>(childRegion)].InsertAgentToTree(agentPtr);
			if (succ) { return succ; }
			else 
			{
				treeAgents.push_back(agentPtr);
				return true;
			}
		}
	}
	else 
	{
		treeAgents.push_back(agentPtr);
		return true;
	}
}

