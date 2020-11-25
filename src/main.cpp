#include <FreeRTOS.h>
#include <task.h>
#include <stm32f1xx_hal.h>
#include <main.h>

extern "C" void StartDefaultTask(void *argument) {

    for(;;) {
        vTaskDelay(pdMS_TO_TICKS(100));
        HAL_GPIO_TogglePin(TestLED_GPIO_Port, TestLED_Pin);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}