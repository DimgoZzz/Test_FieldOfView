#include "ConsoleApp.h"
#include "WinMin.h"
#include <cstdlib>


ConsoleApp::ConsoleApp()
{
    CreateAppWindow();
    quadTreePtr = QuadTree::MakeNewRoot();
    quadTreePtr->BuildTree();
    quadTreePtr->AddAgent(TreeAgent(1.f, 1.f));
    quadTreePtr->AddAgent(TreeAgent(1.f, 2.f));
    quadTreePtr->AddAgent(TreeAgent(5.f, 1.f));
    quadTreePtr->AddAgent(TreeAgent(3.f, 12.f));
    quadTreePtr->AddAgent(TreeAgent(53.f, 23.f));
    quadTreePtr->AddAgent(TreeAgent(53.f, 22.f));
}

ConsoleApp::~ConsoleApp()
{
	if (windowptr)      { delete windowptr; }
    if (quadTreePtr)    { delete quadTreePtr; }
}

void ConsoleApp::Start()
{
    AddBGQuadTreeToRenderData();
    while (windowptr->isOpen())
    {
        sf::Event event;
        while (windowptr->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                windowptr->close();
        }

        windowptr->clear(sf::Color::Black);

        AddAgentsToRenderData();
        
        for(int64 i = rects.size()-1;i>-1;--i)
        {
            windowptr->draw(rects[i]);
        }
        for (int64 i = agents.size() - 1; i > -1; --i)
        {
            windowptr->draw(agents[i]);
        }
        
        windowptr->display();
    }
}

/////////////////////////////Render/////////////////////////////
void ConsoleApp::CreateAppWindow()
{
    windowptr = new sf::RenderWindow(sf::VideoMode(800, 800), "SFML works!", sf::Style::Titlebar | sf::Style::Close);
}

void ConsoleApp::AddBGQuadTreeToRenderData()
{
    rects.clear();
    int32 i = 0;
   //Main Frame, Zero Level
    rects.emplace_back(sf::Vector2f(quadTreePtr->bounds.width*2-2, quadTreePtr->bounds.height*2 - 2));
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

void ConsoleApp::AddAgentsToRenderData()
{
    agents.clear();
    for (auto& element : quadTreePtr->globalAgentMap)
    {
        sf::CircleShape temp(1);
        
        temp.setPosition(element.second.agentLocation.GetX()*2, element.second.agentLocation.GetY()*2);
        temp.setOutlineColor(sf::Color::White);
        temp.setFillColor(sf::Color::Cyan);
        temp.setOutlineThickness(1.f);
        agents.push_back(temp);
    }
}
