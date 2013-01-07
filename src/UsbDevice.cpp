/*
 * UsbDevice.cpp
 *
 *  Created on: 2013-01-02
 *      Author: thierry
 */

#include "UsbDevice.h"

UsbDevice::UsbDevice(usb_dev_handle *targetDeviceHandle) {
	deviceHandle = targetDeviceHandle;
}

UsbDevice::~UsbDevice() {
}

UsbDevice* UsbDevice::createFromConnectedDevice(u_int16_t vendorID,
		u_int16_t productID) {
	usb_dev_handle *targetDeviceHandle = NULL;
	usb_init();
	usb_find_busses();
	usb_find_devices();

	struct usb_bus *bus = usb_get_busses();

	while (targetDeviceHandle == NULL && (bus = bus->next)) {
		struct usb_device *dev = bus->devices;

		while (targetDeviceHandle == NULL && (dev = dev->next)) {
			if (dev->descriptor.idVendor == vendorID
					&& dev->descriptor.idProduct == productID) {
				targetDeviceHandle = usb_open(dev);
				usb_detach_kernel_driver_np(targetDeviceHandle, 0);
				usb_claim_interface(targetDeviceHandle, 0);
			}
		}
	}

	return targetDeviceHandle != NULL ? new UsbDevice(targetDeviceHandle) : NULL;
}

bool UsbDevice::isConnected() {
	return deviceHandle != NULL;
}

bool UsbDevice::sendControlMsg(int rquestType, int request, int wValue,
		int wIndex, int timeout, char* data, int dataSize) {
	int result = usb_control_msg(deviceHandle, rquestType, request, wValue,
			wIndex, data, dataSize, timeout);

	if (result == -6) {
		deviceHandle = NULL;
	}

	return result == dataSize;
}

void UsbDevice::readData(char *data, int size, int timeout) {
	usb_interrupt_read(deviceHandle, USB_ENDPOINT_IN | 1, data,
			size, timeout);
}

void UsbDevice::close() {
	usb_release_interface(deviceHandle, 0);
	usb_close(deviceHandle);
}
