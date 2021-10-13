#pragma once
#include <list>
#include <queue>
#include <unordered_map>

#include "DataClasses.h"
#include "FunctionLibrary.h"
#include "Box.h"
#include "TreeAgent.h"



class QuadTree
{
#pragma region Static 
public:
	static QuadTree* MakeRoot();
	static QuadTree* GetRoot();
private:
	static uint32 NextID();
	static uint32 lastID;

	//ClearStaticData For TreeRestart
	static void ClearStaticData();

	//Array Global Agent-ID
	static std::unordered_map<uint32, TreeAgent> globalAgentMap;
	//GlobalQueueForNewAgentsToInsert
	static std::queue<TreeAgent*> instertQueue;


	static const int8	numChilds = 4;
	static const int8	maxLevel = 2;
	static QuadTree*	rootPtr;

#pragma endregion Static 
public:
	QuadTree(Box box, int8 dlvl = 0, QuadTree* parent = nullptr);
	~QuadTree();

	void BuildTree();
	void UpdateTree();
	//void PerformVisionChecks();

	void AddAgent(TreeAgent agent);
private:
	//bool FeedAgentToTree(TreeAgent* agentPtr);
	//bool CanEatAgent(TreeAgent* agentPtr);

	//Tree Bounding Box
	Box bounds;
	//List Of Agents Under This Tree
	std::list<TreeAgent*> treeAgents;
	//Vector of Child Tree Branches
	std::vector<QuadTree> childTreesArray;
	
	QuadTree* parentTreePtr = nullptr;
	//Params
	int8 depthLevel = -1;
	



///////////////////////////////////////
	//For Rendering
	friend class Renderer;
	friend class ConsoleApp;
///////////////////////////////////////
};
