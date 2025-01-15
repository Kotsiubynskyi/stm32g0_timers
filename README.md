The repository demonstrates different modes of ***STM32G0F6P6*** timers 

## How to build and flash (for Ubuntu)

1. Install needed ARM development toolchain and other utilities:
    ```bash
    apt update; apt install -y cmake git usbutils ninja-build gcc-arm-none-eabi stlink-tools
    ```
1. Clone the project:
    ```bash
    git clone https://github.com/Kotsiubynskyi/stm32g0_timers.git stm32g0_timers_demo
    ```
1. Generate build files:
    ```bash
    cd stm32g0_timers_demo
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
    st-flash erase && st-flash --reset write timers_demo.bin 0x8000000
    ```
