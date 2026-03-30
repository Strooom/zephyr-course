# Note to IOMICO reviewer
I read a lot about West Workspaces and how they could and should be used with Zephyr.  
I've decided to set up 2 template repo's :
1 a workspace repo - called the 'top dir' in zephyr docs.
2 a template for the so-called 'manifest repository', ie. the application and all its dependencies, found in a '/app' subfolder of the workspace

I think there should be a separate repo for ```west workspace``` (1) and ```zephyr project``` (2) :
* workspace repo will normally not change / project repo will change a lot
* developer willing to work on (2) may have their own, different workspaces

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
