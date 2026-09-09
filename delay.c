#include "delay.h"

volatile uint32_t ms_ticks = 0;

void SysTick_Handler(void)
{
    ms_ticks++;
}

void SysTick_Init(void)
{
    SysTick->LOAD = 16000 - 1;
    SysTick->VAL = 0;

    SysTick->CTRL =
        SysTick_CTRL_CLKSOURCE_Msk |
        SysTick_CTRL_TICKINT_Msk |
        SysTick_CTRL_ENABLE_Msk;
}

void Delay_ms(uint32_t ms)
{
    uint32_t start = ms_ticks;

    while ((ms_ticks - start) < ms)
    {
    }
}
