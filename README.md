Instructions written for Ubuntu (Debian) of simple blink project for STM32G0F6P6 with LED on pin ***PA4***

## How to build and flash

1. Install needed ARM development toolchain and other utilities:
    ```bash
    apt update; apt install -y cmake git usbutils ninja-build gcc-arm-none-eabi stlink-tools
    ```
1. Important: current repository uses submodules so please clone the project ***recursively***:
    ```bash
    git clone --recursive https://github.com/Kotsiubynskyi/stm32_g0_blink_cmake.git blink
    ```
1. Generate build files:
    ```bash
    cd blink
    mkdir build
    cd build
    cmake .. -G Ninja
    ```
1. Build project from ***build*** folder:
    ```bash
    ninja
    ```
1. Insert ST-LINK programmer USB stick and make sure it's visible by OS:
    ```bash
    lsusb|grep STMicroelectronics
    ```
1. Upload built firmware to MCU:
    ```bash
    st-flash erase && st-flash --reset write blink.bin 0x8000000
    ```
