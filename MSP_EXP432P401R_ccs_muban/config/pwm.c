/*
 * pwm.c
 *
 *  Created on: 2021Äê7ÔÂ6ÈÕ
 *      Author: 13173
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define TIMER_PERIOD 640
#define DUTY_CYCLE1 32
#define DUTY_CYCLE2 96

void PWM_Init(void){
    Timer_A_PWMConfig pwmConfig1 =
    {

            TIMER_A_CLOCKSOURCE_SMCLK,
            TIMER_A_CLOCKSOURCE_DIVIDER_1,
            TIMER_PERIOD,
            TIMER_A_CAPTURECOMPARE_REGISTER_1,
            TIMER_A_OUTPUTMODE_RESET_SET,
            300
    };

    Timer_A_PWMConfig pwmConfig2 =
    {
            TIMER_A_CLOCKSOURCE_SMCLK,
            TIMER_A_CLOCKSOURCE_DIVIDER_1,
            TIMER_PERIOD,
            TIMER_A_CAPTURECOMPARE_REGISTER_2,
            TIMER_A_OUTPUTMODE_RESET_SET,
            500
    };
    //![Simple Timer_A Example]
    /* Setting MCLK to REFO at 128Khz for LF mode
     * Setting SMCLK to 64Khz */
    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    //MAP_CS_initClockSignal(CS_MCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_CS_initClockSignal(CS_SMCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_PCM_setPowerState(PCM_AM_LF_VCORE0);

    // Configuring GPIO2.4 as peripheral output for PWM
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4|GPIO_PIN5,
            GPIO_PRIMARY_MODULE_FUNCTION);


    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig1);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
}


