/*
 * UsbDevice.h
 *
 *  Created on: 2013-01-02
 *      Author: thierry
 */

#ifndef USBDEVICE_H_
#define USBDEVICE_H_

#include <usb.h>

class UsbDevice {
public:
	static UsbDevice* createFromConnectedDevice(u_int16_t vendorID,
			u_int16_t productID);

	UsbDevice(usb_dev_handle *targetDeviceHandle);

	bool sendControlMsg(int rquestType, int request, int wValue, int wIndex,
			int timeout, char* data, int dataSize);
	void readData(char *data, int size, int timout = 500);
	virtual ~UsbDevice();

	bool isConnected();
	void close();

private:
	struct usb_dev_handle *deviceHandle;
};

#endif /* USBDEVICE_H_ */
