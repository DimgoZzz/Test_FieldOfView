#pragma once
#include <SFML/Graphics.hpp>
#include "QuadTree.h"





class ConsoleApp
{
public:
	ConsoleApp();
	~ConsoleApp();

	void Start();
private:
	QuadTree* quadTreePtr = nullptr;

#pragma region Render
private:
	sf::RenderWindow* windowptr = nullptr;
	std::vector<sf::RectangleShape> rects;
	std::vector<sf::CircleShape> agents;

	void CreateAppWindow();
	void AddBGQuadTreeToRenderData();
	void AddAgentsToRenderData();

#pragma endregion Render

};

