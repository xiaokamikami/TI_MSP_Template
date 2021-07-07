/*
 * pwm.c
 *
 *  Created on: 2021Äê7ÔÂ6ÈÕ
 *      Author: 13173
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
void PWM_Init(void){
    /* Timer_A UpDown Configuration Parameter */
    const Timer_A_UpDownModeConfig upDownConfig =
    {
            TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock SOurce
            TIMER_A_CLOCKSOURCE_DIVIDER_1,          // SMCLK/1 = 3MHz
            TIMER_PERIOD,                           // 127 tick period
            TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
            TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,    // Disable CCR0 interrupt
            TIMER_A_DO_CLEAR                        // Clear value

    };

    /* Timer_A Compare Configuration Parameter  (PWM1) */
    const Timer_A_CompareModeConfig compareConfig_PWM1 =
    {
            TIMER_A_CAPTURECOMPARE_REGISTER_1,          // Use CCR1
            TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
            TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output but
            DUTY_CYCLE1                                 // 32 Duty Cycle
    };

    /* Timer_A Compare Configuration Parameter (PWM2) */
    const Timer_A_CompareModeConfig compareConfig_PWM2 =
    {
            TIMER_A_CAPTURECOMPARE_REGISTER_2,          // Use CCR2
            TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
            TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output but
            DUTY_CYCLE2                                 // 96 Duty Cycle
    };

    /* Setting P7.7 and P7.6 and peripheral outputs for CCR */
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2,
            GPIO_PIN0 + GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configuring Timer_A1 for UpDown Mode and starting */
    MAP_Timer_A_configureUpDownMode(TIMER_A1_BASE, &upDownConfig);
    MAP_Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UPDOWN_MODE);

    /* Initialize compare registers to generate PWM1 */
    MAP_Timer_A_initCompare(TIMER_A1_BASE, &compareConfig_PWM1);

    /* Initialize compare registers to generate PWM2 */
    MAP_Timer_A_initCompare(TIMER_A1_BASE, &compareConfig_PWM2);

}


