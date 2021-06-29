/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/*******************************************************************************
 * MSP432 GPIO - Toggle Output High/Low
 *
 * Description: In this very simple example, the LED on P1.0 is configured as
 * an output using DriverLib's GPIO APIs. An infinite loop is then started
 * which will continuously toggle the GPIO and effectively blink the LED.
 *
 *                MSP432P401
 *             ------------------
 *         /|\|                  |
 *          | |                  |
 *          --|RST         P1.0  |---> P1.0 LED
 *            |                  |
 *            |                  |
 *            |                  |
 *            |                  |
 *
 ******************************************************************************/
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include "pwmled.h"
#include "Key.h"

static uint8_t key_mode = 0;
//![Simple GPIO Config]
int main(void)
{
    volatile uint32_t ii;

    /* Halting the Watchdog */
    MAP_WDT_A_holdTimer();

    //PWM_Init();
    Key_Init();
    /* Configuring P1.0 as output */

    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0);    //off
    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN1);    //off
    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN2);    //off
    //使能中断
    Interrupt_enableInterrupt(INT_PORT1);
    Interrupt_enableSleepOnIsrExit();
    Interrupt_enableMaster();
    while (1)
    {

        /* Delay Loop */
        //for(ii=0;ii<20000;ii++)
        //{
        //}

        //GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0);
        //GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN2);
        //GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN2);
        //GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
        if(key_mode == 1){
            GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN0);    //on
        }
        else if(key_mode ==2){
            GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN1);    //on
        }
        else if(key_mode ==3){
            GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN2);    //on
        }
        else{

        }
        MAP_PCM_gotoLPM0();
    }
}
//![Simple GPIO Config]
void PORT1_IRQHandler(void)
{

    //中断服务
    uint32_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1); //获取中断状态
    GPIO_clearInterruptFlag(GPIO_PORT_P1,status);   //清除标志位

    if(status & GPIO_PIN1)
    {
        key_mode =1;
    }
    else if( status & GPIO_PIN4 )
    {

        key_mode =2;
    }
    else
    {

    }
}

void TA0_N_IRQHandler(void)
{
    MAP_Timer_A_clearInterruptFlag(TIMER_A0_BASE);
    MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

