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
#include "traces_ref.h"

buffer_trace buffer;

/* Description: write a trace to a memory buffer. Note that this function is
 *              automatically called by FreeRTOS in privileged mode.
 *
 * Parameters: trace_id: trace ID. Usually the task number in FreeRTOS.
 *             val: 1 if task becomes active, 0 otherwise
 */
void write_trace(uint8_t trace_id, short val) {
	buffer.trace[buffer.write_pos].time = LPC_TIM0->TC;
	buffer.trace[buffer.write_pos].synchro = SYNCHRO_WORD;
	buffer.trace[buffer.write_pos].trace_id = trace_id;
	buffer.trace[buffer.write_pos++].value = val;
	buffer.write_pos %= BUFFER_MAX;
}

void vApplicationIdleHook(void) {
	while (1) {
		// implement trace sending here after having set configUSE_IDLE_HOOK to 1 in FreeRTOSConfig.h
		if (buffer.trace[buffer.read_pos].synchro == SYNCHRO_WORD) {
			trace_t traceSend = buffer.trace[buffer.read_pos];
			uart0_send((uint8_t *) &traceSend, sizeof(traceSend));

			buffer.trace[buffer.read_pos++].synchro = 0;
			buffer.write_pos %= BUFFER_MAX;
		}
		taskYIELD();		// force changement de contexte
	}
}

