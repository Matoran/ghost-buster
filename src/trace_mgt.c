
/*
 * Description: trace management using UART
 * Created on : 23.3.2017
 * Author     : VP
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <traces_ref.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "uart.h"

/* Description: write a trace to a memory buffer. Note that this function is
 *              automatically called by FreeRTOS in privileged mode.
 *
 * Parameters: trace_id: trace ID. Usually the task number in FreeRTOS.
 *             val: 1 if task becomes active, 0 otherwise
 */
void write_trace(uint8_t trace_id, short val)
{
	write_trace_ref(trace_id, val);		// to be replaced by your own implementation
}



/*void vApplicationIdleHook( void )
{
	while (1)
	{
		// implement trace sending here after having set configUSE_IDLE_HOOK to 1 in FreeRTOSConfig.h
		taskYIELD();		// force changement de contexte
	}
}*/


