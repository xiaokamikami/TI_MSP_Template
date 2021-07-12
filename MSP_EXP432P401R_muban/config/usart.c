/*
 * usart.c
 *
 *  Created on: 2021Äê7ÔÂ12ÈÕ
 *      Author: 13173
 */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
    const eUSCI_UART_ConfigV1 uartConfig =
    {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
            26,                                      // BRDIV = 26
            0,                                       // UCxBRF = 0
            37,                                      // UCxBRS = 37
            EUSCI_A_UART_NO_PARITY,                  // No Parity
            EUSCI_A_UART_MSB_FIRST,                  // MSB First
            EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
            EUSCI_A_UART_MODE,                       // UART mode
            EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,  // Oversampling
            EUSCI_A_UART_8_BIT_LEN                   // 8 bit data length
    };

void USART_Init(void){
    /* Selecting P1.2 and P1.3 in UART mode PC */
    /* Selecting P3.2 and P3.3 in UART mode PC */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
             GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);


    /* Configuring UART Module */
    MAP_UART_initModule(EUSCI_A2_BASE, &uartConfig);

    /* Enable UART module */
    MAP_UART_enableModule(EUSCI_A2_BASE);

    /* Enabling interrupts */
    MAP_UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA2);

}
