# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)
set(FREERTOS_KERNEL_PATH "C:/users/Joao/FreeRTOS-Kernel")
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)
project(Enchente C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
include_directories(${CMAKE_SOURCE_DIR}/lib)
add_executable(Enchente Enchente.c lib/ssd1306.c)

pico_set_program_name(Enchente "Enchente")
pico_set_program_version(Enchente "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Enchente 1)
pico_enable_stdio_usb(Enchente 1)

# Add the standard library to the build
target_link_libraries(Enchente
        pico_stdlib
        FreeRTOS-Kernel         # Kernel do FreeRTOS
        FreeRTOS-Kernel-Heap4   # Gerenciador de memoria
        hardware_pio
        hardware_pwm
        hardware_i2c
        hardware_adc)

# Add the standard include files to the build
target_include_directories(Enchente PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(Enchente)

