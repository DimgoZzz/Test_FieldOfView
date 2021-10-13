#pragma once
#include <list>
#include <queue>
#include <unordered_map>

#include "DataClasses.h"
#include "Box.h"
#include "TreeAgent.h"

enum class TreeDirection :uint8
{
	NorthWest = 0,
	NorthEast = 1,
	SouthWest = 2,
	SouthEast = 3
};

class QuadTree
{
public:
	QuadTree(Box inbounds, int8 currLevel);
	static QuadTree* MakeNewRoot();
	static QuadTree* GetRoot();

	void BuildTree();
	void UpdateTree();

	void AddAgent(TreeAgent agent);

	~QuadTree();

private:
	static void ClearStaticData();

	static std::unordered_map<uint32, TreeAgent> globalAgentMap;
	static uint32 lastID;
	//GlobalQueueForNewAgents
	static std::queue<TreeAgent*> instertQueue;
	//List Of Units Under This Tree
	std::list<TreeAgent*> treeAgents;

	//Tree Bounding Box
	Box bounds;
	QuadTree* parentTreePtr = nullptr;
	//Vector of Child Tree Branches
	std::vector<QuadTree> childTreesArray;

	//Params
	static const int8	numChilds = 4;

	bool isFinalBranch = false;
	bool isRoot = false;

	static QuadTree* rootPtr;

	static bool isTreeReady;

	int8 levelOfQuadTree = 0;

	static const int8 maxLevel = 2;

	//For Rendering
	friend class ConsoleApp;
};
