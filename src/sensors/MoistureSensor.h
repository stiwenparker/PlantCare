#pragma once

#include <chrono>
#include <mutex>
#include <set>
#include <random>

#include "WaterDeviceInterface.h"

class MoistureSensor {
	const std::chrono::seconds sleepTime;
	std::mutex& mtx;
	std::set<WaterDeviceInterface*> devices;

	const int min = 0;
	const int max = 100;
	const int threshold = 30;
public:
	MoistureSensor(const std::chrono::seconds sleepTime, std::mutex& mtx)
		: sleepTime{ sleepTime },
		mtx{ mtx }
	{

	}

	void subscribe(WaterDeviceInterface& device) {
		devices.insert(&device);
	}

	void operator()() {
		for (;;) {
			std::unique_lock<std::mutex> lock(mtx);

			if (isAirTooDry())
				for (auto p : devices)
					p->sprinkleWater();
			if (isSoilTooDry())
				for (auto p : devices)
					p->pourWater();

			lock.unlock();
			std::this_thread::sleep_for(sleepTime);
		}
	}
	void foo();

private:
	bool isAirTooDry() {
		return getAirMoisture() < threshold;
	}
	bool isSoilTooDry() {
		return getSoilMoisture() < threshold;
	}
	int getAirMoisture() {
		static std::mt19937 generator;
		return std::uniform_int_distribution<int>(min, max)(generator);
	}
	int getSoilMoisture() {
		static std::mt19937 generator;
		return std::uniform_int_distribution<int>(min, max)(generator);
	}
};