#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

TaskHandle_t xtask_01, xtask_02, xtask_03;
const TickType_t xdelay = 300 / portTICK_PERIOD_MS;

void task_01(void *data)
{
    int count = 0;
    printf("task 1 suspended\n");
    vTaskSuspend(NULL);

    while(1) { 
        count++;
        
        if(count == 1000000) {
            printf("Inside task 1\n");
            for(int i = 0; i < 6; i++) {
                printf("task 2 getting resumed in %d\n", i+1);
            }
            vTaskResume(xtask_02);
            printf("TASK 2 RESUMED\n");
            count = 0;
            printf("task 1 suspended\n");
            vTaskSuspend(NULL);   
        }
    }
}

void task_02(void *data)
{
    int count = 0;
    printf("task 2 suspended\n");
    vTaskSuspend(NULL);   

    while(1) { 
        count++;
        
        if(count == 1000000) {
            printf("Inside task 2\n");
            for(int i = 0; i < 6; i++) {
                printf("task 3 getting resumed in %d\n", i+1);
            }
            vTaskResume(xtask_03);
            printf("TASK 3 RESUMED\n");
            count = 0;
            printf("task 2 Suspended\n");
            vTaskSuspend(NULL);    
        }
    }
}

void task_03(void *data)
{
    int count = 0;

    while(1) { 
        count++;
        
        if(count == 1000000) {
            printf("Inside task 3\n");
            for(int i = 0; i < 6; i++) {
                printf("task 1 getting resumed in %d\n", i+1);
            }
            vTaskResume(xtask_01);
            printf("TASK 1 RESUMED\n");
            count = 0; 
            printf("task 3 suspended\n");
            vTaskSuspend(xtask_03);   
        }
    }
}

void app_main(void)
{
    printf("Inside Main function\n");

    if((xTaskCreate(task_01, "task01", 2048, NULL, 8, &xtask_01)) == pdPASS) {
        printf("Task 1 created successfully\n");
    }

    if((xTaskCreate(task_02, "task02", 2048, NULL, 7, &xtask_02)) == pdPASS) {
        printf("Task 2 created successfully\n");
    }

    if((xTaskCreate(task_03, "task03", 2048, NULL, 9, &xtask_03)) == pdPASS) {
        printf("Task 3 created successfully\n");
    }

}