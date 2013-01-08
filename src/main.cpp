//============================================================================
// Name        : UsbPanicButton.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <usb.h>
#include "USBPanicButton.h"
using namespace std;

int main() {
	USBPanicButton* pButton = USBPanicButton::createFromConnectedDevice();

	if (pButton == NULL) {
		cout << "No panic button detected";
		return 0;
	}

	while (pButton->isConnected()) {
		if (pButton->isPressed()) {
			cout << "Button pressed\n";
		}

		usleep(100*1000);
	}
	pButton->close();
	delete pButton;
	return 0;
}
