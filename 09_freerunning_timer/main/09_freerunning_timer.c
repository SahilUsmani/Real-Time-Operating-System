#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>

TaskHandle_t    task01_handle;
TimerHandle_t   timer_handle;

void Timer_Callback(TimerHandle_t timer_handle)
{
    printf("Free Running / Auto Reload Timer : Fired\n");
}

void task_01(void *data)
{
    
    printf("Task 1 : Started\n");
    timer_handle = xTimerCreate("FreeRunning", pdMS_TO_TICKS(5000), pdTRUE, NULL, Timer_Callback);
    printf("Free Running / Auto Reload Timer : Going to start for 5 secs\n");
    xTimerStart(timer_handle, 0);
    printf("Task 01 : Deleted\n");
    vTaskDelete(NULL);
    
}



void app_main(void)
{
    xTaskCreate(task_01, "task01", 2048, NULL, 8, &task01_handle);
}


