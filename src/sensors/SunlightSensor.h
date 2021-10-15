#pragma once

#include <chrono>
#include <set>
#include <optional>
#include <mutex>
#include <iostream>

#include "../interface/WindowDeviceInterface.h"
#include "../utility/Utilities.h"

class SunlightSensor {
    using TimePoint = decltype(std::chrono::system_clock::now());

    const std::chrono::seconds sleepTime;
    std::mutex& mtx;
    std::set<WindowDeviceInterface*> devices;

    std::optional<TimePoint> sunlightOnFrom;
    std::optional<TimePoint> sunlightOffFrom;

    const int threshold = 2;
    bool sensorOn = true;

public:
    SunlightSensor(const std::chrono::seconds sleepTime, std::mutex& mtx)
        : sleepTime{ sleepTime }
        , mtx{ mtx }
    {
    }

    void subscribe(WindowDeviceInterface& device) {
        devices.insert(&device);
    }
    void operator()() {
        for (;;) {
            std::unique_lock<std::mutex> lock(mtx);
            const auto sunlight = isSunlight();
            updateState(sunlight);
            std::cout << getCurrentTime() << " Sun shines: " << std::boolalpha << sunlight << std::endl;

            if (isTooMuchSunlight(sunlight)) {
                for (auto p : devices)
                    p->closeWindowBlinds();
                sensorOn = false;
            }
            else if (isTooLittleSunlight(sunlight)) {
                for (auto p : devices)
                    p->openWindowBlinds();
                sensorOn = true;
            }

            lock.unlock();
            std::this_thread::sleep_for(sleepTime);
        }
    }

private:
    void updateState(const bool sunlight) {
        const auto currentTime = std::chrono::system_clock::now();
        if (sunlight and sensorOn) {
            sunlightOnFrom = sunlightOnFrom ? *sunlightOnFrom : currentTime;
            sunlightOffFrom = std::nullopt;
        }
        else if (not sunlight) {
            sunlightOffFrom = sunlightOffFrom ? *sunlightOffFrom : currentTime;
            sunlightOnFrom = std::nullopt;
        }
    }
    bool isTooMuchSunlight(const bool sunlight) {
        if (sunlight) {
            const auto timeNow = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsedSeconds = timeNow - (*sunlightOnFrom);
            return elapsedSeconds.count() > threshold;
        }
        return false;
    }
    bool isTooLittleSunlight(const bool sunlight) {
        if (not sunlight) {
            const auto timeNow = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsedSeconds = timeNow - (*sunlightOffFrom);
            return elapsedSeconds.count() > threshold;
        }
        return false;
    }
    bool isSunlight() const {
        static bool sunShines = false;
        static std::mt19937 generator;
        auto prob = std::uniform_int_distribution<int>(1, 100)(generator);
        if (prob >= 80)
            sunShines = !sunShines;
        return sunShines;
    }
};
