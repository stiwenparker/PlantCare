#pragma once

#include "../interface/WindowDeviceInterface.h"
#include "../utility/Utilities.h"

//example for a plant that doesn't need care about water changes like cactus

class OtherPlantCaretaker : public WindowDeviceInterface {
	bool areWindowBlindsOpened = true;
public:
	void closeWindowBlinds() override {
		if (areWindowBlindsOpened) {
			areWindowBlindsOpened = false;
			std::cout << getCurrentTime() << " opened window blinds for plant2\n";
		}
	}

	void openWindowBlinds() override {
		if (!areWindowBlindsOpened) {
			areWindowBlindsOpened = true;
			std::cout << getCurrentTime() << " closed window blinds for plant2\n";
		}
	}
};