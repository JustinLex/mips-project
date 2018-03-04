# mips-project

## Details
A larger project within IS1200 Computer Hardware Engineering to create a program for our PIC32 ChipKit.    
Jointly developed by Justin Lex and Petr Kocian.

## Features
* A page-based UI, using button interrupts
* Shows a page that shows the current longitude/latitude and height.
* Shows a date/time page that tells the current date and time
* Shows a meter that shows how many satellites are connected using the LEDs
* Shows a humorous spinner page that shows a spinning arrow

# Code Features
* Able to read and write to UART bus
* Able to interpret UBX-NAV-PVT packets from GPS
* Able to tell time from the GPS, using either a RTC or GPS synchronization
* Able to convert 32x32 bitmaps into the image format used by display_image()
* Able to rotate images by a specified amount of radians

