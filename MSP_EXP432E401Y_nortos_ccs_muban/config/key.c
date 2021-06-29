/*
 * key.c
 *
 *  Created on: 2021Äê6ÔÂ29ÈÕ
 *      Author: 13173
 */

#include <ti/devices/msp432e4/driverlib/driverlib.h>

#include "key.h"
void Key_Init(void){
    MAP_GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0|GPIO_PIN_1);
    GPIOJ->PUR |= GPIO_PIN_0;
    GPIOJ->PUR |= GPIO_PIN_1;
    MAP_GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_PIN_0|GPIO_PIN_1, GPIO_RISING_EDGE);
    MAP_GPIOIntEnable(GPIO_PORTJ_BASE, GPIO_INT_PIN_0|GPIO_INT_PIN_1);

    MAP_IntEnable(INT_GPIOJ);
}
