#pragma once

#include "Renderer.h"
#include "QuadTree.h"





class ConsoleApp
{
public:
	ConsoleApp();
	~ConsoleApp();

	void Start();
private:
	QuadTree* quadTreePtr = nullptr;
	Renderer renderer;
};

