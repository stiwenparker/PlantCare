#pragma once

class WindowDeviceInterface {
public:
	virtual ~WindowDeviceInterface() = default;

	virtual void openWindowBlinds() = 0;
	virtual void closeWindowBlinds() = 0;
};