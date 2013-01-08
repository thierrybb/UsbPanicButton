/*
 * USBPanicButton.cpp
 *
 *  Created on: 2013-01-02
 *      Author: thierry
 */
#include "USBPanicButton.h"

USBPanicButton::USBPanicButton(UsbDevice* panicButtonDevice) {
	this->panicButtonDevice = panicButtonDevice;
}

USBPanicButton* USBPanicButton::createFromConnectedDevice() {
	UsbDevice* targetDevice = UsbDevice::createFromConnectedDevice(ID_VENDOR, ID_PRODUCT);

	return targetDevice == NULL ? NULL : new USBPanicButton(targetDevice);
}

ButtonState USBPanicButton::requestButtonState() {
	char bytes[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02 };
	int requesttype = 0x21;
	int request = 0x9;
	int value = 0x200;
	int index = 0x00;
	int timeout = 500;
	int size = sizeof(bytes);

	if (!panicButtonDevice->sendControlMsg(requesttype, request, value, index,
			timeout, bytes, size))
		return UNKNOWN;

	char *usbDeviceData = new char[8];
	panicButtonDevice->readData(usbDeviceData, 8, 500);
	int receivedFirstByteValue = usbDeviceData[0];
	delete usbDeviceData;
	return receivedFirstByteValue == 22 ? DOWN : UP;
}

bool USBPanicButton::isConnected() {
	return panicButtonDevice->isConnected();
}

bool USBPanicButton::isPressed() {
	return requestButtonState() == DOWN;
}

void USBPanicButton::close() {
	panicButtonDevice->close();
	delete panicButtonDevice;
}
