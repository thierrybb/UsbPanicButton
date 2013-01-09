# set the include path found by configure
INCLUDES = $(all_includes)

.cpp.o:
	@CXXCOMPILE@ $@ $<

bin_PROGRAMS = panicbutton
panicbutton_SOURCES = src/main.cpp  src/UsbDevice.cpp  src/UsbDevice.h  src/USBPanicButton.cpp  src/USBPanicButton.h
panicbutton_LDADD  = @LIBUSB_1_0@ -lm
