#pragma once
#include <SFML/Graphics.hpp>

#include "DataClasses.h"
#include "QuadTree.h"


class Renderer
{
public:
	Renderer();
	~Renderer();

	void Init(QuadTree** qt);
	void DoFrame();

	sf::RenderWindow* GetWindowPtr();

	void CreateAppWindow();
	void CollectTreeGridData(QuadTree* quadTreePtr);
	void CollectTreeAgentsData(QuadTree* quadTreePtr);
private:
	QuadTree** quadTreePP;
	sf::RenderWindow* windowPtr = nullptr;
	std::vector<sf::RectangleShape> rects;
	std::vector<sf::CircleShape> agents;

};

