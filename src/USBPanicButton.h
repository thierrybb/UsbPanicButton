/*
 * USBPanicButton.h
 *
 *  Created on: 2013-01-02
 *      Author: thierry
 */

#ifndef USB_PANIC_BUTTON_H
#define	USB_PANIC_BUTTON_H

#include "UsbDevice.h"

#define ID_VENDOR 0x1d34
#define ID_PRODUCT 0x000d

class USBPanicButton {
public:
	static USBPanicButton* createFromConnectedDevice();

	USBPanicButton(UsbDevice* panicButtonDevice);
    bool isConnected();
	bool buttonIsPressed();
    void close();
private:
    bool requestButtonState();
    UsbDevice* panicButtonDevice;
};

#endif
