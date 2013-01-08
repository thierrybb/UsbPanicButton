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
		cout << "No panic button detected\n";
		return 0;
	}

	ButtonState lastButtonState = UNKNOWN;

	while (pButton->isConnected()) {
		ButtonState currentButtonState = pButton->getButtonState();

		if (currentButtonState == DOWN && lastButtonState == UP) {
			cout << "Panic button pressed\n";
		}

		lastButtonState = currentButtonState;
		usleep(100 * 1000);
	}
	pButton->close();
	delete pButton;
	return 0;
}
