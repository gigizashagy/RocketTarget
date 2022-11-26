#include "utilities.h"
#include <sstream>

std::vector<std::string> split(const std::string& input, const char delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss(input);
    std::string item;

    while (std::getline(ss, item, delimiter))
    {
        result.push_back(item);
    }

    if (result.empty())
    {
        result.push_back(input);
    }

    return result;
}

std::ostream& operator<<(std::ostream& os, const EntityParams& params)
{
    os << "\tPosition: [" << glm::to_string(params.position) << "]\n"
        << "\tDirection: [" << glm::to_string(params.direction) << "]\n"
        << "\tVelocity: [" << params.speed << "]\n";
    return os;
}

std::ostream& operator<<(std::ostream& os, const RocketParams& params)
{
    os << static_cast<EntityParams>(params)
        << "\tRadius: [" << params.radius << "]\n";
    return os;
}

void ReadConsoleEntityParams(EntityParams& params)
{
    std::string inputStr;
    const char splitter = ',';

    std::cout << "Input location x,y\n";
    std::getline(std::cin, inputStr);
    // Read position
    if (!inputStr.empty())
    {
        auto positions = split(inputStr, splitter);
        if (positions.size() > 1)
        {
            params.position.x = std::stof(positions[0]);
            params.position.y = std::stof(positions[1]);
        }
    }

    std::cout << "Input direction x,y\n";
    std::getline(std::cin, inputStr);

    // Read direction
    if (!inputStr.empty())
    {
        auto direction = split(inputStr, splitter);
        if (direction.size() > 1)
        {
            params.direction.x = std::stof(direction[0]);
            params.direction.y = std::stof(direction[1]);
        }
    }

    std::cout << "Input speed v\n";
    std::getline(std::cin, inputStr);

    if (!inputStr.empty())
    {
        params.speed = std::stof(inputStr);
    }
}

void ReadConsoleRocketParams(RocketParams& params)
{
    ReadConsoleEntityParams(params);

    std::string inputStr;
    std::cout << "Input radius r\n";
    std::getline(std::cin, inputStr);

    if (!inputStr.empty())
    {
        params.radius = std::stof(inputStr);
    }
}

float Lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

float Clamp(float v, float min, float max)
{
    return v < min ? min : v < max ? v : max;
}
