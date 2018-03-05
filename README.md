# mips-project

## Details
A larger project within IS1200 Computer Hardware Engineering to create a program for our PIC32 ChipKit.    
Jointly developed by Justin Lex and Petr Kocian.

## Features
* A page-based UI, using button interrupts
* Shows a page that shows the current longitude/latitude, height and horizontal accuracy.
* Shows a date/time page that tells the current date and time and shows an analog clock
* Shows a page with the current ECEF coordinates
* Shows a page with the current distance to a landmark
* Shows a meter that shows how many satellites are connected using the LEDs

## Code Features
* Able to read and write to UART bus
* Able to interpret UBX-NAV-PVT and UBX-NAV-POSECEF packets from the u-Blox GPS module
* Able to tell time from the GPS, using either a RTC or GPS synchronization
* Able to convert 32x32 bitmaps into the image format used by display_image()
* Able to rotate images by a specified amount of radians

