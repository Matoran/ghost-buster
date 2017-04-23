/**
 * @authors: LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: manage traces
 * Language:  C
 * Date : april 2017
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

/**
 * write a trace to a circulary buffer
 * @param trace_id the trace number(task number)
 * @param val 0 or 1
 */
void write_trace(uint8_t trace_id, short val) {
	//write_trace_ref(trace_id, val);
	buffer.trace[buffer.write_pos].time = LPC_TIM0->TC;
	buffer.trace[buffer.write_pos].synchro = SYNCHRO_WORD;
	buffer.trace[buffer.write_pos].trace_id = trace_id;
	buffer.trace[buffer.write_pos++].value = val;
	buffer.write_pos %= BUFFER_MAX;
}

/**
 * called by FreeRTOS when it do nothing
 */
void vApplicationIdleHook(void) {
	while (1) {
		if (buffer.write_pos != buffer.read_pos) {
			uart0_send((uint8_t *) &buffer.trace[buffer.read_pos++], sizeof(trace_t));
			buffer.read_pos %= BUFFER_MAX;
		}
		taskYIELD();		// force changement de contexte
	}
}

