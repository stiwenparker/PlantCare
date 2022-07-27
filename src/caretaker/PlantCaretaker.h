#pragma once

#include "../interface/WaterDeviceInterface.h"
#include "../interface/WindowDeviceInterface.h"
#include "../utility/Utilities.h"

// a caretaker for a standard plants that need to be taken care in terms of water and sunlight

class PlantCaretaker : public WaterDeviceInterface, public WindowDeviceInterface {
	private:
		bool areWindowBlindsOpened = true;

	public:
		void pourWater() override {
			std::cout << getFormattedCurrentTime() << " pouring water on plant1\n";
		}

		void sprinkleWater() override {
			std::cout << getFormattedCurrentTime() << " sprinkling water on plant1\n";
		}

		void closeWindowBlinds() override {
			if (areWindowBlindsOpened) {
				areWindowBlindsOpened = false;
				std::cout << getFormattedCurrentTime() << " opened window blinds for plant1\n";
			}
		}

		void openWindowBlinds() override {
			if (!areWindowBlindsOpened) {
				areWindowBlindsOpened = true;
				std::cout << getFormattedCurrentTime() << " closed window blinds for plant1\n";
			}
		}
};