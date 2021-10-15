#include "./src/sensors/MoistureSensor.h"
#include "./src/sensors/SunlightSensor.h"
#include "./src/caretaker/PlantCaretaker.h"
#include "./src/caretaker/OtherPlantCaretaker.h"

#include <thread>


void run() {
    std::mutex sensorsMutex;

    auto sunlightSensor = SunlightSensor(std::chrono::seconds(2), sensorsMutex);
    auto moistureSensor = MoistureSensor(std::chrono::seconds(3), sensorsMutex);

    PlantCaretaker plantCaretaker;
    moistureSensor.subscribe(plantCaretaker);
    sunlightSensor.subscribe(plantCaretaker);

    OtherPlantCaretaker oplantCaretaker;
    sunlightSensor.subscribe(oplantCaretaker);

    std::thread sunlightSensorThread(sunlightSensor);
    std::thread moistureSensorThread(moistureSensor);

    sunlightSensorThread.join();
    moistureSensorThread.join();
}

int main(int argc, char* argv[]) {
    run();
	return 0;
}