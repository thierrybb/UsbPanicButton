/*
 * UsbDevice.cpp
 *
 *  Created on: 2013-01-02
 *  Author: thierry
 */

#include "UsbDevice.h"
#include <iostream>

UsbDevice::UsbDevice(libusb_device_handle *targetDeviceHandle) {
	deviceHandle = targetDeviceHandle;
}

UsbDevice::~UsbDevice() {
}

UsbDevice* UsbDevice::createFromConnectedDevice(u_int16_t vendorID,
		u_int16_t productID) {
	libusb_init(NULL);
	libusb_device_handle *targetDeviceHandle = libusb_open_device_with_vid_pid(
			NULL, vendorID, productID);

	if (targetDeviceHandle == NULL)
		return NULL;

	if (libusb_kernel_driver_active(targetDeviceHandle, 0) > 0)
		libusb_detach_kernel_driver(targetDeviceHandle, 0);

	int r = libusb_claim_interface(targetDeviceHandle, 0);

	if (r == LIBUSB_ERROR_ACCESS) {
		std::cerr << "Access error trying to claim device interface" << std::endl;
		return NULL;
	}

	return new UsbDevice(targetDeviceHandle);
}

bool UsbDevice::isConnected() {
	return deviceHandle != NULL;
}

bool UsbDevice::sendControlMsg(int rquestType, int request, int wValue,
		int wIndex, int timeout, unsigned char* data, int dataSize) {
	int result = libusb_control_transfer(deviceHandle, rquestType, request,
			wValue, wIndex, data, dataSize, timeout);

	if (result == -6) {
		deviceHandle = NULL;
	}

	return result == dataSize;
}

void UsbDevice::readData(unsigned char *data, int size, int timeout) {
	int transferred;
	libusb_interrupt_transfer(deviceHandle, LIBUSB_ENDPOINT_IN | 1, data, size,
			&transferred, timeout);
}

void UsbDevice::close() {
	libusb_release_interface(deviceHandle, 0);
	libusb_close(deviceHandle);
}
