#pragma once

#include "../interface/WindowDeviceInterface.h"
#include "../utility/Utilities.h"

// example of a case for a plant that doesn't need its own water caretaker (like a cactus)

class OtherPlantCaretaker : public WindowDeviceInterface {
	private:
		bool areWindowBlindsOpened = true;

	public:
		void closeWindowBlinds() override {
			if (areWindowBlindsOpened) {
				areWindowBlindsOpened = false;
				std::cout << getFormattedCurrentTime() << " opened window blinds for plant2\n";
			}
		}

		void openWindowBlinds() override {
			if (!areWindowBlindsOpened) {
				areWindowBlindsOpened = true;
				std::cout << getFormattedCurrentTime() << " closed window blinds for plant2\n";
			}
		}
};