#pragma once

#include "../interface/WaterDeviceInterface.h"
#include "../interface/WindowDeviceInterface.h"
#include "../utility/Utilities.h"

class PlantCaretaker : public WaterDeviceInterface, public WindowDeviceInterface {
	bool areWindowBlindsOpened = true;
public:
	void pourWater() override {
		std::cout << getCurrentTime() << " pouring water on plant1\n";
	}

	void sprinkleWater() override {
		std::cout << getCurrentTime() << " sprinkling water on plant1\n";
	}

	void closeWindowBlinds() override {
		if (areWindowBlindsOpened) {
			areWindowBlindsOpened = false;
			std::cout << getCurrentTime() << " opened window blinds for plant1\n";
		}
	}

	void openWindowBlinds() override {
		if (!areWindowBlindsOpened) {
			areWindowBlindsOpened = true;
			std::cout << getCurrentTime() << " closed window blinds for plant1\n";
		}
	}

};