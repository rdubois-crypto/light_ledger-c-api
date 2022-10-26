# light_ledger-c-api

This folder is a minimal extraction of project https://github.com/LedgerHQ/btchip-c-api enabling communication from labtop to ledger device
via usb link.

Build with GNU make (needs libusb 1.0 development APIs for Makefile.libusb or HID API from Signal 11 for Makefile.hidapi, such as the libhidapi-dev package), each command is described below. It may be necessary to install the following packages:
* sudo apt install libhidapi-dev
* sudo apt install libusb-1.0-0-dev
* sudo apt install libconfig-dev

Description of apdu's to communicate with ledger are on Ledger developper site. Raw command using the web client REPL are available thourgh the web client:
https://repl.ledger.tools/
