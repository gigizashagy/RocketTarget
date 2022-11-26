#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

#include "glm/glm.hpp"
#include "utilities.h"
#include "Entities.h"

static float g_DeltaTime = 0.1f;
static const float g_MaxSimulationTime = 10.f;
static const std::chrono::milliseconds g_Delay(25);

//#define NO_INPUT

int main(int argc, char* argv[])
{
    std::vector<std::shared_ptr<Entity>> Entities;
    EntityParams targetParams;
    RocketParams rocketParams;
#ifdef NO_INPUT
    targetParams.position = glm::vec2(0, 5);
    targetParams.direction = glm::vec2(1, 0);
    targetParams.speed = 3.5f;

    std::cout << "Target:\n";
    std::cout << targetParams << std::endl;

    rocketParams.position = glm::vec2(0, 0);
    rocketParams.direction = glm::vec2(1, 1);
    rocketParams.speed = 4.0f;
    rocketParams.radius = 0.5f;

    std::cout << "Rocket:\n";
    std::cout << rocketParams << std::endl;
#else
    float globalDelta;
    std::cout << "Input global delta time\n";
    std::cin >> globalDelta;
    if (globalDelta > 0.f)
    {
        g_DeltaTime = globalDelta;
    }
    std::cin.ignore();

    std::cout << "Input Target params:" << std::endl;
    ReadConsoleEntityParams(targetParams);
    std::cout << "Target:\n";
    std::cout << targetParams << std::endl;


    std::cout << "Input Rocket params:\n";
    ReadConsoleRocketParams(rocketParams);
    std::cout << "Rocket:\n";
    std::cout << rocketParams << std::endl;

#endif // NO_INPUT

    std::shared_ptr<Entity> target = Entities.emplace_back(std::make_unique<Entity>(targetParams));
    std::shared_ptr<Rocket> rocket = std::static_pointer_cast<Rocket>(Entities.emplace_back(std::make_unique<Rocket>(rocketParams)));
    rocket->SetTarget(target);

    bool bSimulate = true;
    float simulationTime = 0.f;
    while (bSimulate && g_MaxSimulationTime > simulationTime)
    {
        std::cout << "TimeStep: "<< std::setw(3) << simulationTime << " Distance: " << glm::distance(Entities[0]->getPosition(), Entities[1]->getPosition()) << '\n';
        for (auto entity : Entities)
        {
            std::cout << "TimeStep: "<< std::setw(3) << simulationTime << " " << entity->ToString() << '\n';
            entity->Update(g_DeltaTime);
        }

        if (rocket->IsTargetOverlap())
        {
            std::cout << "TimeStep: "<< std::setw(3) << simulationTime << " BTOOM!\n";
            bSimulate = false;
        }
        std::cout << std::endl;
        simulationTime += g_DeltaTime;
        
        std::this_thread::sleep_for(g_Delay);
    }

    if (g_MaxSimulationTime < simulationTime)
        std::cout << "Time over!\n";

    return 0;
}
