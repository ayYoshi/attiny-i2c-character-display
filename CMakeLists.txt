cmake_minimum_required(VERSION 3.13.4)

project(attiny-lcd)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

set(USB_PATH "/dev/ttyUSB0")
set(AVR_INC_PATH "/usr/lib/avr/include/")
set(ATTINY_I2C_INC_PATH "${CMAKE_SOURCE_DIR}/include/usitwislave/")
set(SHIFT_INC_PATH "${CMAKE_SOURCE_DIR}/include/my-shiftreg-lib/")
set(BAUD 19200)

file(GLOB SRC src/*.c)
file(GLOB ATTINY_I2C_SRC ${ATTINY_I2C_INC_PATH}/*.c ${ATTINY_I2C_INC_PATH}/*.cpp)
file(GLOB SHIFT_SRC ${SHIFT_INC_PATH}/*.c ${SHIFT_INC_PATH}/*.cpp)

#avr-gcc -Os -mmcu=attiny85 main.c -o main -DF_CPU=8000000ul
#avr-objcopy -O ihex -R .eeprom main main.hex
#avrdude -F -V -c avrisp -p t85 -P /dev/ttyUSB0 -b 19200 -U flash:w:main.hex


set(CPU_FREQ 8000000ul)
set(MMCU "attiny85")
set(MMCU_BURN "t85")
set(PROGRAMMER_ID "avrisp")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} ${SRC} ${ATTINY_I2C_SRC} ${SHIFT_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${AVR_INC_PATH} ${ATTINY_I2C_INC_PATH} ${SHIFT_INC_PATH})

set(CMAKE_C_FLAGS "-Os -DF_CPU=${CPU_FREQ} -mmcu=${MMCU}") 
set(CMAKE_CXX_FLAGS "-Os -DF_CPU=${CPU_FREQ} -mmcu=${MMCU}") 

add_custom_target(hex avr-objcopy -O ihex -R .eeprom "${PROJECT_NAME}" "${PROJECT_NAME}.hex" DEPENDS ${PROJECT_NAME})
add_custom_target(burn avrdude -F -V -c ${PROGRAMMER_ID} -p "${MMCU_BURN}" -P "${USB_PATH}" -b "${BAUD}" -U flash:w:"${PROJECT_NAME}.hex" DEPENDS hex)
