#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

TaskHandle_t xtask_01, xtask_02;
const TickType_t xdelay = 500 / portTICK_PERIOD_MS;

void task_01(void *data)
{
    UBaseType_t t01;
    t01 = uxTaskPriorityGet(xtask_01);

    while(1) {
    printf("Inside task 01\n");
    printf("task_01 priority = %d\n", t01);
    vTaskDelay(xdelay);
    }
}

void task_02(void *data)
{
    UBaseType_t t02;
    t02 = uxTaskPriorityGet(xtask_02);

    while(1) {
    printf("Inside task 02\n");
    printf("task_02 priority = %d\n", t02);
    vTaskDelay(xdelay);
    }
}

void app_main(void)
{
    printf("Inside Main function\n");

    if((xTaskCreate(task_01, "task01", 2048, NULL, 8, &xtask_01)) == pdPASS) {
        printf("Task_01 created successfully\n");
    }

    if((xTaskCreate(task_02, "task02", 2048, NULL, 8, &xtask_02)) == pdPASS) {
        printf("Task_02 created successfully\n");
    }

    /*
    If two task has same priorites they act in a round robin fashion
    */

}
