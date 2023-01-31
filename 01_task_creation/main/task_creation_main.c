
#include <stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
// #include "esp_chip_info.h"
// #include "esp_flash.h"

#define INFINITE_LOOP_BEGIN		while(1){
#define INFINITE_LOOP_END		}
#define FUNCTION_TASK(function_name, argument) 		void function_name(void *argument)

TaskHandle_t serial_task_handle;
TaskHandle_t eth_task_handle;

FUNCTION_TASK(serial_task, data)
{
	const TickType_t xDelay = 100 / portTICK_PERIOD_MS;

	INFINITE_LOOP_BEGIN
		printf("serialtask\n");
		vTaskDelay(xDelay);
	INFINITE_LOOP_END
	
	//printf("Inside serialtask\n");
	//vTaskDelete(serial_task_handle);

}

FUNCTION_TASK(eth_task, data)
{
	INFINITE_LOOP_BEGIN
        printf("ethtask\n");
	INFINITE_LOOP_END
    //printf("Inside ethtask\n");
	//vTaskDelete(eth_task_handle);

}



void app_main()
{
	printf("Inside main\n");
	BaseType_t stask_ret;
	BaseType_t ethtask_ret;

 	stask_ret = xTaskCreate(serial_task, "serialtask", 2048, NULL, 5, &serial_task_handle);
	if(stask_ret == pdPASS) {
	 	printf("serial task completed successfully\n");
	}

	ethtask_ret = xTaskCreate(eth_task, "ethtask", 2048, NULL, 8, &eth_task_handle);
	if(ethtask_ret == pdPASS) {
        printf("eth task completed successfully\n");
    }

	//esp_restart();

}
