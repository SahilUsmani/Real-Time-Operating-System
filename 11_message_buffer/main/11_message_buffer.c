#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/message_buffer.h"

TaskHandle_t            task1_handle, task2_handle;
MessageBufferHandle_t   msgbuff;

static int              taskcore = 1;

void task_1(void *data)
{
    printf("Task 1 : Started\n");
    xMessageBufferSend(msgbuff, "First Message", 15, pdMS_TO_TICKS(10000));
    xMessageBufferSend(msgbuff, "Second Message", 15, pdMS_TO_TICKS(10000));
    xMessageBufferSend(msgbuff, "Third Message", 15, pdMS_TO_TICKS(10000));
    printf("Task 1 : Data sent to Task 2\n");
    printf("Task 1 : Deleted\n");
    vTaskDelete(NULL);
}

void task_2(void *data)
{
    printf("Task 2 : Started\n");
    unsigned char recbuff[200];
    for(int count = 0; count < 3; count++)
    {
        xMessageBufferReceive(msgbuff, &recbuff, 200, pdMS_TO_TICKS(1000));
        printf("Task 2 : Data Received is %s\n", recbuff);
    }
    printf("Task 2 : Deleted");
    vTaskDelete(NULL);
}

void app_main(void)
{
    printf("Main Task : Started\n");
    msgbuff = xMessageBufferCreate(200);
    xTaskCreatePinnedToCore(task_1, "task1", 2048, NULL, 8, &task1_handle, taskcore);
    xTaskCreatePinnedToCore(task_2, "task2", 2048, NULL, 8, &task2_handle, taskcore);
}
