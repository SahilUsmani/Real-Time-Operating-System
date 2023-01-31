#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

TaskHandle_t xtask_01, xtask_02, xtask_03;
const TickType_t xdelay = 1000 / portTICK_PERIOD_MS;

void task_01(void *data)
{
    int count = 0;
    
    while(1) {
       vTaskSuspend(NULL); 
        count++;
        
        if(count == 10) {
            printf("Inside task 1\n");
            for(int i = 0; i < 6; i++) {
                printf("task 2 getting resumed in %d\n", i+1);
            }
            vTaskResume(xtask_02);
            printf("TASK 2 RESUMED\n");
            count = 0;  
        }

    }
    //vTaskDelay(xdelay);
}

void task_02(void *data)
{
    int count = 0;   

    while(1) {
        vTaskSuspend(NULL); 
        count++;
        
        if(count == 10) {
            printf("Inside task 2\n");
            for(int i = 0; i < 6; i++) {
                printf("task 3 getting resumed in %d\n", i+1);
            }
            count = 0;
            vTaskResume(xtask_03);
            printf("TASK 3 RESUMED\n");    
        }
    }
}

void task_03(void *data)
{
    int count = 0;

    while(1) {
        vTaskSuspend(NULL);
        count++;
        if(count == 10) {
            printf("Inside task 3\n");
            for(int i = 0; i < 6; i++) {
                printf("task 1 getting resumed in %d\n", i+1);
            }
            count = 0;
            vTaskResume(xtask_01);
            printf("TASK 1 RESUMED\n"); 
            printf("task 3 suspended\n");       
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
        vTaskResume(xtask_03);
    }
}