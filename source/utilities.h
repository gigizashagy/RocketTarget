#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "glm/gtx/string_cast.hpp"
#include "EntityTypes.h"

template<typename... Args>
std::string string_format(const char* fmt, Args... args)
{
    size_t size = snprintf(nullptr, 0, fmt, args...);
    std::string buf;
    buf.reserve(size + 1);
    buf.resize(size);
    snprintf(&buf[0], size + 1, fmt, args...);
    return buf;
}

std::vector<std::string> split(const std::string& input, const char delimiter);

std::ostream& operator<<(std::ostream& os, const EntityParams& params);
std::ostream& operator<<(std::ostream& os, const RocketParams& params);

void ReadConsoleEntityParams(EntityParams& params);
void ReadConsoleRocketParams(RocketParams& params);

float Lerp(float a, float b, float t);

float Clamp(float v, float min, float max);