//============================================================================
// Name        : UsbPanicButton.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <libusb-1.0/libusb.h>
#include <stdlib.h>
#include "USBPanicButton.h"
using namespace std;

int main(int argc, char **argv) {
	USBPanicButton* pButton = USBPanicButton::createFromConnectedDevice();

	if (pButton == NULL) {
		cout << "No panic button detected\n";
		return 0;
	}

	ButtonState lastButtonState = UNKNOWN;

	while (pButton->isConnected()) {
		ButtonState currentButtonState = pButton->getButtonState();

		if (currentButtonState == DOWN && lastButtonState == UP) {
			if (argc > 1)
				system(argv[1]);
			else
				system("xdg-open http://xkcd.com/898/");
		}

		lastButtonState = currentButtonState;
		usleep(100 * 1000);
	}
	pButton->close();
	delete pButton;
	return 0;
}
