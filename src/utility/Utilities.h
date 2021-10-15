#pragma once

#include <string>
#include <time.h>

std::string getCurrentTime() {
    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);

    std::string result = "[";

    auto hour = newtime.tm_hour;
    if(hour < 10)
        result += '0' + std::to_string(newtime.tm_hour);
    else 
        result += std::to_string(newtime.tm_hour);

    result += ":";

    auto minute = newtime.tm_min;
    if (minute < 10)
        result += '0' + std::to_string(newtime.tm_min);
    else
        result += std::to_string(newtime.tm_min);

    result += ":";

    auto second = newtime.tm_sec;
    if (second < 10)
        result += '0' + std::to_string(newtime.tm_sec);
    else
        result += std::to_string(newtime.tm_sec);

    result += "]";

    return result;
}