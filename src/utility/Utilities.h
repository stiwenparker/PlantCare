#pragma once

#include <string>
#include <time.h>
#include <iostream>

std::string getCurrentTime() {
    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);

    std::string result = "[" + std::to_string(newtime.tm_hour);
    result += ":" + std::to_string(newtime.tm_min);
    result += ":" + std::to_string(newtime.tm_sec) + "]";

    return result;
}