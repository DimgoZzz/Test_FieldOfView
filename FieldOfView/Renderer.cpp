#include "Renderer.h"


Renderer::Renderer()
{
    CreateAppWindow();
}

Renderer::~Renderer()
{
    if (windowPtr) { delete windowPtr; }
}

void Renderer::Init(QuadTree** qt)
{
    quadTreePP = qt;
}

void Renderer::DoFrame()
{
    if (rects.empty()) { CollectTreeGridData(*quadTreePP);   }
    if (agents.empty()) { CollectTreeAgentsData(*quadTreePP); }

    windowPtr->clear(sf::Color::Black);

    for (int64 i = rects.size() - 1; i > -1; --i)
    {
        windowPtr->draw(rects[i]);
    }
    for (int64 i = agents.size() - 1; i > -1; --i)
    {
        windowPtr->draw(agents[i]);
    }

    windowPtr->display();

}

sf::RenderWindow* Renderer::GetWindowPtr()
{
    return windowPtr;
}

void Renderer::CreateAppWindow()
{
    windowPtr = new sf::RenderWindow(sf::VideoMode(800, 800), "SFML works!", sf::Style::Titlebar | sf::Style::Close);
}

void Renderer::CollectTreeGridData(QuadTree* quadTreePtr)
{
    rects.clear();
    int32 i = 0;
    //Main Frame, Zero Level
    rects.emplace_back(sf::Vector2f(quadTreePtr->bounds.width * 2 - 2, quadTreePtr->bounds.height * 2 - 2));
    rects.back().setPosition(1, 1);
    rects[0].setOutlineColor(sf::Color::Blue);
    rects[0].setFillColor(sf::Color::Transparent);
    rects[0].setOutlineThickness(2.f);
    ++i;
    //First Level
    for (auto& element : quadTreePtr->childTreesArray)
    {

        rects.emplace_back(sf::Vector2f(element.bounds.width * 2, element.bounds.height * 2));
        rects.back().setPosition(element.bounds.left * 2, element.bounds.top * 2);
        rects[i].setOutlineColor(sf::Color::Red);
        rects[i].setFillColor(sf::Color::Transparent);
        rects[i].setOutlineThickness(1.f);
        ++i;
        //Second Level
        for (auto& elem2 : element.childTreesArray)
        {
            rects.emplace_back(sf::Vector2f(elem2.bounds.width * 2, elem2.bounds.height * 2));
            rects.back().setPosition(elem2.bounds.left * 2, elem2.bounds.top * 2);
            rects[i].setOutlineColor(sf::Color::Green);
            rects[i].setFillColor(sf::Color::Transparent);
            rects[i].setOutlineThickness(1.f);
            ++i;
        }
    }
}

void Renderer::CollectTreeAgentsData(QuadTree* quadTreePtr)
{
    agents.clear();
    for (auto& element : quadTreePtr->globalAgentMap)
    {
        sf::CircleShape temp(1);

        temp.setPosition(element.second.agentLocation.GetX() * 2, element.second.agentLocation.GetY() * 2);
        temp.setOutlineColor(sf::Color::White);
        temp.setFillColor(sf::Color::Cyan);
        temp.setOutlineThickness(1.f);
        agents.push_back(temp);
    }
}
