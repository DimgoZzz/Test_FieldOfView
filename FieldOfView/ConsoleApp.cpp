#include "ConsoleApp.h"




ConsoleApp::ConsoleApp()
{
    renderer.Init(&quadTreePtr);
    quadTreePtr = QuadTree::MakeRoot();

    int answer = -1;
    std::cout << "Print what to do: " <<
        "\n1 - Load Random World" <<
        "\n2 - Load Random World and Save it to file    //not implemented" <<
        "\n3 - Load World From file                     //not implemented" <<
        "\n:";
    std::cin >> answer;
    switch (answer)
    {
    case 1:case 2: case 3:
        {
            LoadRandWorld();
            break;
        }
       /* case 2:
        {
            LoadRandWorld();
            SaveWorldToFile();
            break;
        }
        case 3:
        {
            LoadFileWorld();
            break;
        }*/
        default:
        {
            CritErr("Cant Read Answer");
        }
    }

        
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


void ConsoleApp::LoadRandWorld()
{
    BuildTree();
    FillRandomTree();
    
    UpdateTree();
    VisionCheck();

    PrintStat();
}


//TO DO
bool ConsoleApp::SaveWorldToFile()
{
    return false;
}

//TO DO
bool ConsoleApp::LoadFileWorld()
{
    BuildTree();

    //ReadDataInstead
    //FillRandomTree();

    UpdateTree();
    VisionCheck();

    PrintStat();
    return true;
}


void ConsoleApp::BuildTree()
{
    ///////////////TreeInit
    clock.Measure();

    quadTreePtr->BuildTree();
    secInit = clock.StopMeasure();
}

void ConsoleApp::FillRandomTree()
{
    //Fill Tree Randomly
    srand(4541);
    for (int32 i = 0; i < AppSettings::MaxUnits; ++i)
    {
        quadTreePtr->AddAgent(TreeAgent((rand() % 4000) / 10.f, (rand() % 4000) / 10.f, (rand() % 10) / 10.f, (rand() % 10) / 10.f));
    }
}

void ConsoleApp::UpdateTree()
{
    ///////////////Updating
    clock.Measure();
    quadTreePtr->UpdateTree();
    secFill = clock.StopMeasure();
}

void ConsoleApp::VisionCheck()
{
    ///////////////AgentsVisionCheck
    clock.Measure();
    quadTreePtr->PerformVisionChecks();
    secVisionCheck = clock.StopMeasure();

}

void ConsoleApp::PrintStat()
{
    int64 t = 0;
    for (int32 i = 0; i < AppSettings::MaxUnits; ++i)
    {
        t += quadTreePtr->globalAgentMap.at(i).seeCount;
        std::cout << "Agent " << i << " see " << quadTreePtr->globalAgentMap.at(i).seeCount << " Agents " << std::endl;
    }

    std::cout << "QuadTree Init taked: " << secInit << " ms" << std::endl;
    std::cout << "QuadTree Update taked: " << secFill << " ms" << std::endl;
    std::cout << "Vision Checks taked: " << secVisionCheck << " ms" << std::endl;
    std::cout << "Total Intersections : " << t << std::endl;
    std::cout << "Total CanSee Calls :" << TreeAgent::countCall << std::endl;
}
