#include "ConsoleApp.h"
#include "WinMin.h"
#include <cstdlib>

ConsoleApp::ConsoleApp()
{
    renderer.Init(&quadTreePtr);
    quadTreePtr = QuadTree::MakeRoot();

    DogFW::HighResClock clock;
    double secInit, secFill, secVisionCheck;

    ///////////////TreeInit
    clock.Measure();
   
    quadTreePtr->BuildTree();
    secInit = clock.StopMeasure();
    
    ///////////////TreeFilling
    clock.Measure();

    //Fill Tree Randomly
    srand(4541);
    for (int32 i = 0; i < AppSettings::MaxUnits; ++i)
    {
        quadTreePtr->AddAgent(TreeAgent((rand() % 400) / 10.f, (rand() % 400) / 10.f, (rand() % 10) / 10.f, (rand() % 10) / 10.f));
    }
    quadTreePtr->UpdateTree();
    secFill = clock.StopMeasure();
    
    ///////////////AgentsVisionCheck
    clock.Measure();
    quadTreePtr->PerformVisionChecks();
    secVisionCheck = clock.StopMeasure();


    for (int32 i = 0; i < AppSettings::MaxUnits; ++i)
    {
        std::cout <<"Agent "<< i<<" see " << quadTreePtr->globalAgentMap.at(i).seeCount <<" Agents " << std::endl;
    }
    int64 t = 0;
    for (int32 i = 0; i < AppSettings::MaxUnits; ++i)
    {
        t+= quadTreePtr->globalAgentMap.at(i).seeCount;
    }

    std::cout << "QuadTree Init taked: " << secInit << " ms" << std::endl;
    std::cout << "QuadTree Filling taked: " << secFill << " ms" << std::endl;
    std::cout << "Vision Checks taked: " << secVisionCheck << " ms" << std::endl;
    std::cout << "Total Intersections : " << t << std::endl;
    std::cout << "Total CanSee Calls :" << TreeAgent::countCall << std::endl;
    
}

ConsoleApp::~ConsoleApp()
{
    if (quadTreePtr)    { delete quadTreePtr; }
}

void ConsoleApp::Start()
{
    renderer.DoFrame();
    while (renderer.GetWindowPtr()->isOpen())
    {
        sf::Event event;
        while (renderer.GetWindowPtr()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                renderer.GetWindowPtr()->close();
        }
       // renderer.DoFrame();
    }
}
