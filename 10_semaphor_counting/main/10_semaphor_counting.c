#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

TaskHandle_t        task1_handle, task2_handle, task3_handle, task4_handle;
SemaphoreHandle_t   counting_sem;
static int          taskcore = 1;

void task_1(void *data)
{
    printf("Task 1 : Started\n");
    xSemaphoreTake(counting_sem, pdMS_TO_TICKS(20000));
    printf("Task 1 : Got the Semaphore\n");
    vTaskDelay(pdMS_TO_TICKS(10000));
    xSemaphoreGive(counting_sem);
    printf("Task 1 : Released the Semaphore\n");
    vTaskDelete(NULL);
}

void task_2(void *data)
{
    printf("Task 2 : Started\n");
    xSemaphoreTake(counting_sem, pdMS_TO_TICKS(20000));
    printf("Task 2 : Got the Semaphore\n");
    vTaskDelay(pdMS_TO_TICKS(16000));
    xSemaphoreGive(counting_sem);
    printf("Task 2 : Released the Semaphore\n");
    vTaskDelete(NULL); 
}

void task_3(void *data)
{   
    printf("Task 3 : Started\n");
    xSemaphoreTake(counting_sem, pdMS_TO_TICKS(20000));
    printf("Task 3 : Got the Semaphore\n");
    vTaskDelay(pdMS_TO_TICKS(5000));
    xSemaphoreGive(counting_sem);
    printf("Task 3 : Released the Semaphore\n");
    vTaskDelete(NULL);
}

void task_4(void *data)
{
    printf("Task 4 : Started\n");
    xSemaphoreTake(counting_sem, pdMS_TO_TICKS(20000));
    printf("Task 4 : Got the Semaphore\n");
    vTaskDelay(pdMS_TO_TICKS(000));
    xSemaphoreGive(counting_sem);
    printf("Task 4 : Released the Semaphore\n");
    vTaskDelete(NULL);
}

void app_main(void)
{
    printf("Main Task : Started\n");
    counting_sem = xSemaphoreCreateCounting(2, 2);
    xTaskCreatePinnedToCore(task_1, "task1", 2048, NULL, 8, &task1_handle, taskcore);
    xTaskCreatePinnedToCore(task_2, "task2", 2048, NULL, 8, &task2_handle, taskcore);
    xTaskCreatePinnedToCore(task_3, "task3", 2048, NULL, 8, &task3_handle, taskcore);
    xTaskCreatePinnedToCore(task_4, "task4", 2048, NULL, 8, &task4_handle, taskcore);
}
