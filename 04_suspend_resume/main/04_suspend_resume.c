#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

TaskHandle_t xtask_01, xtask_02;
const TickType_t xdelay = 600 / portTICK_PERIOD_MS;

void task_01(void *data)
{
    printf("task_01 getting suspended\n");
    vTaskSuspend(xtask_01);

    UBaseType_t t01;
    t01 = uxTaskPriorityGet(xtask_01);

    while(1) {
        printf("Inside task 01\n");
        printf("task_01 priority = %d\n", t01);
        //vTaskDelete(xtask_01);

        vTaskDelay(xdelay);
    }
}

void task_02(void *data)
{
    printf("task_02 getting suspended\n");
    vTaskSuspend(NULL); //Suspend ourselves

    UBaseType_t t02;
    t02 = uxTaskPriorityGet(xtask_02);

    while(1) {
        printf("Inside task 02\n");
        printf("task_02 priority = %d\n", t02);
        //vTaskDelete(NULL); //Passing NULL will cause the calling task to be deleted
        vTaskDelay(xdelay);
    }
}

void app_main(void)
{
    printf("Inside Main function\n");

    if((xTaskCreate(task_01, "task01", 2048, NULL, 5, &xtask_01)) == pdPASS) {
        printf("Task_01 created successfully\n");
    }
    //printf("task_01 deleted\n");

    printf("task_01 getting resumed\n");
    vTaskResume(xtask_01);

    if((xTaskCreate(task_02, "task02", 2048, NULL, 8, &xtask_02)) == pdPASS) {
        printf("Task_02 created successfully\n");
    }
    //printf("task_02 deleted\n");

    printf("task_02 getting resumed\n");
    vTaskResume(xtask_02);
    
}

