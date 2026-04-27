# Note to IOMICO reviewer - Homework Lesson 4
For this homework I decided to try a different board : the M5Stack AtomS3. Instead of blinking LEDs, I decided to try RGB ledStrips (WS2812 leds). In Zephyr there are a few different ways to drive them, I decided to try the SPI-driver first. This requires the app.overlay to contain the definitions on which pins to transmit the MOSI, and some timing parameters. Also the length of the led-strip (in number of leds/pixels) is set in the DTS overlay file. Some applicaction timing parameter is defined in Kconfig.  
Changes :  
* upgraded west.yml to zephyr 4.4 and adding espressif hal.
* added an 'rgb' library to do calculations on rgb colors.
* added app.overlay to include/enable the external hw. (SPI3 is used because SPI2 is used for the display and I may want to use both at the same time in a future project).
* added Kconfig with parameters needed for the ledstrip driver.
* some other libraries are under 'lib', they are for future use.

# Note to IOMICO reviewer - Homework Lesson 3
I made a variant of the homework : a Kconfig fragment for a 'breathing led' library.  
When the library is enabled, you can 
* choose the breathing speed, in a range.  
* select which hw mechanism to choose :
    * fading using PWM on normal LED
    * fading using a WS2818 led
* When you select the WS2818 led, an extra option appears where you can choose the color of the led from a list

I will implement the library and related DTS for the Lesson 4 homework.


# Note to IOMICO reviewer - Homework Lesson 2
I read a lot about West Workspaces and how they could and should be used with Zephyr.  
I've decided to set up 2 template repo's :
1 a workspace repo - called the 'top dir' in zephyr docs.
2 a template for the so-called 'manifest repository', ie. the application and all its dependencies, found in a '/app' subfolder of the workspace

I think there should be a separate repo for ```west workspace``` (1) and ```zephyr project``` (2) :
* workspace repo will normally not change / project repo will change a lot
* developer willing to work on (2) may have their own, different workspaces
* note that having the top directory as .git repo is NOT supported / recommended by zephyr https://docs.zephyrproject.org/latest/develop/west/workspaces.html#not-supported-workspace-topdir-as-git-repository

The Iomico repo is a template for a zephyr project (not zephyr workspace), so it's contents should be cloned under /app of the workspace. However, this repo already contains an app folder itself... confusing. So I decided to reorganize it, and move all app folders up one level.

Other improvements done : 
* CMakeLists.txt : ```find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})``` io. ```find_package(Zephyr REQUIRED)```
* prj.conf : added ```CONFIG_CPP=y``` As main.cpp indicates development will be in C++, might as well activate this in KConfig as it will be needed in libraries.
* src/main.cpp : several cleanups   
    * use ```static constexpr uint32_t sleepTimeInMs{1000};``` io ```#define SLEEP_TIME_MS 1000``` as it will result in a symbol in the debugger and thus makes the code more readible
    * also made gpio_dt_spec constexpr io const
    * move ```LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);``` to top.
* better .gitignore file
* .clang_format file for automatic code formatting

# Zephyr Training Environment

Welcome to the Zephyr RTOS training! This repository includes a ready-to-use
development environment based on Zephyr 4.3.0, which you can set up in one of
three ways:

---

## Manual Zephyr Setup

Follow the following guide:
- [Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html#).

Make sure to select appropriate OS and to perform all steps till
[Build the Blinky Sample](https://docs.zephyrproject.org/latest/develop/getting_started/index.html#build-the-blinky-sample).
