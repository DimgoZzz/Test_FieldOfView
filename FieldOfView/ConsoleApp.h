#pragma once
#include "Renderer.h"
#include "WinMin.h"
#include <cstdlib>

#include "QuadTree.h"


class ConsoleApp
{
public:
	ConsoleApp();
	~ConsoleApp();

	void Start();
private:
	void LoadRandWorld();
	bool SaveWorldToFile();
	bool LoadFileWorld();

	QuadTree* quadTreePtr;
	Renderer renderer;


	////////////ExtraFuntionsAndData////////////
private:
	void BuildTree();
	void FillRandomTree();
	void UpdateTree();
	void VisionCheck();
	void PrintStat();
	
	DogFW::HighResClock clock;
	double secInit, secFill, secVisionCheck;
};

