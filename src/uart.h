/*
 * Description: UART driver
 * Created on : 30 sept. 2013
 * Author     : VP
 */
#ifndef __UART_H 
#define __UART_H

#define IER_THRE	0x02
#define IS_TX_EMPTY (1<<5)

/* Description: UART 0 initialisation
 *
 * Parameter: baudrate [bit/s]
 */
void uart0_init(uint32_t baudrate);

/* Description: UART 0 initialisation
 *
 * Parameters: data: pointer on data to be sent
 *             length: data length [bytes]
 */
void uart0_send(uint8_t *data, uint32_t length);

#endif
