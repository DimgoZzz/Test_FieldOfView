#include "ConsoleApp.h"
#include "WinMin.h"
#include <cstdlib>


ConsoleApp::ConsoleApp()
{
    renderer.Init(&quadTreePtr);
    quadTreePtr = QuadTree::MakeRoot();

    DogFW::HighResClock clock;

    ///////////////TreeInit
    clock.Measure();
   
    quadTreePtr->BuildTree();

    std::cout << "QuadTree Init taked: " << clock.StopMeasure() << " ms" << std::endl;
    ///////////////
    
    ///////////////TreeFilling
    clock.Measure();

    //Fill Tree Randomly
    srand(4541);
    for (int32 i = 0; i < 10000; ++i)
    {
        quadTreePtr->AddAgent(TreeAgent((rand() % 4000) / 10.f, (rand() % 4000) / 10.f, (rand() % 10) / 10.f, (rand() % 10) / 10.f));
    }
    quadTreePtr->UpdateTree();

    std::cout << "QuadTree Filling taked: " << clock.StopMeasure() << " ms" << std::endl;
    ///////////////
    
    ///////////////AgentsVisionCheck
    //clock.Measure();
    //for (auto& agent : quadTreePtr->treeAgents)
    //{
    //   // for ()
    //}
    //for (int64 i = 0; i < 10000; ++i)
    //{
    //    //quadTreePtr->childTreesArray
    //}
    //std::cout << "Vision Checks taked: " << clock.StopMeasure() << " ms" << std::endl;
    ///////////////

}

ConsoleApp::~ConsoleApp()
{
    if (quadTreePtr)    { delete quadTreePtr; }
}

void ConsoleApp::Start()
{
    while (renderer.GetWindowPtr()->isOpen())
    {
        sf::Event event;
        while (renderer.GetWindowPtr()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                renderer.GetWindowPtr()->close();
        }
        renderer.DoFrame();
    }
}
