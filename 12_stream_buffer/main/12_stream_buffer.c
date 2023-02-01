#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/stream_buffer.h"

TaskHandle_t            task1_handle, task2_handle;
StreamBufferHandle_t   stream_buff;

static int              taskcore = 1;

void task_1(void *data)
{
    printf("Task 1 : Started\n");
    xStreamBufferSend(stream_buff, "First Message\n", 14, pdMS_TO_TICKS(10000));
    xStreamBufferSend(stream_buff, "Second Message\n", 15, pdMS_TO_TICKS(10000));
    xStreamBufferSend(stream_buff, "Third Message\n", 14, pdMS_TO_TICKS(10000));
    printf("Task 1 : Data sent to Task 2\n");
    printf("Task 1 : Deleted\n");
    vTaskDelete(NULL);
}

void task_2(void *data)
{
    printf("Task 2 : Started\n");
    unsigned char recbuff[200];
    size_t rsize;
    
    rsize = xStreamBufferReceive(stream_buff, &recbuff, 200, pdMS_TO_TICKS(10000));
    printf("Task 2 : Data size = %d :: Data Received = %s \n", rsize, recbuff);
    printf("Task 2 : Deleted");
    vTaskDelete(NULL);
}

void app_main(void)
{
    printf("Main Task : Started\n");
    stream_buff = xStreamBufferCreate(200, 18);
    xTaskCreatePinnedToCore(task_1, "task1", 2048, NULL, 8, &task1_handle, taskcore);
    xTaskCreatePinnedToCore(task_2, "task2", 2048, NULL, 5, &task2_handle, taskcore);
}
