#pragma once

// abstract interface for water sensor
class WaterDeviceInterface {
	public:
		virtual ~WaterDeviceInterface() = default;
		virtual void pourWater() = 0;
		virtual void sprinkleWater() = 0;
};