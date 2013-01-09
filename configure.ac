AC_INIT([UsbPanicButton], [0.1], [tbb@sherpa-solution.com], [panic-button], [https://github.com/thierrybb/UsbPanicButton])
AC_PREREQ([2.59])
AM_INIT_AUTOMAKE([1.10 no-define foreign])
AC_CONFIG_HEADERS([config.h])
AC_PROG_CXX

# Checks for libraries.
AH_TEMPLATE([HAVE_LIBUSB_1_0],
            [Define if USB support is enabled via libusb 1.0])
AC_CHECK_LIB([usb-1.0], [libusb_init], [have_libusb_1_0=yes])
if test x$have_libusb_1_0 = xyes; then
   case $target in
       *-*-darwin*)
               LIBUSB_1_0="-lusb-1.0 -framework CoreFoundation -framework IOKit"
               ;;
       *)
               LIBUSB_1_0="-lusb-1.0"
               ;;
   esac
   AC_DEFINE([HAVE_LIBUSB_1_0])
   AC_CHECK_HEADERS([libusb-1.0/libusb.h])
   AC_CHECK_HEADERS([libusb.h])
fi
AH_TEMPLATE([HAVE_LIBUSB_1_0],
            [Define if USB support is enabled via a libusb-1.0 compatible libusb])
AC_CHECK_LIB([usb], [libusb_init], [have_libusb_1_0=yes])
if test x$have_libusb_1_0 = xyes; then
   case $target in
       *-*-freebsd*)
               # FreeBSD 8+ has a native libusb-1.0 API compatible
               # library offered by -lusb (which is also libusb-0.1
               # compatible).  FreeBSD <8 does not have a libusb-1.0
               # at all so probing will fail but we do not have to
               # special-case that.
               LIBUSB_1_0="-lusb"
               ;;
       *)
               LIBUSB_1_0="-lusb-1.0"
               ;;
   esac
   AC_DEFINE([HAVE_LIBUSB_1_0])
   AC_CHECK_HEADERS([libusb.h])
fi
AC_SUBST(LIBUSB_1_0, $LIBUSB_1_0)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

if test x$have_libusb = x; then
   echo "DON'T HAVE libusb-1.0"
   echo "# sudo apt-get install libusb-1.0-0-dev"
fi


