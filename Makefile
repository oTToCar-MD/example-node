TARGET  := example-node
RTOS    := freertos
DEVICE  := stm32f103re

UAVCAN_STM32_TIMER_NUMBER   := 7
UAVCAN_STM32_NUM_IFACES     := 1

STM32_PCLK1     := 42000000
STM32_TIMCLK1   := 84000000

INCDIRS         := include/
SOURCES         := src/main.cpp

# Actual build engine
include uavcan-stm32-cubehal-base/include.mk