#include "stm32f446xx.h"
#include "buzzer.h"

void Buzzer_On(void)
{
    GPIOB->BSRR = (1U << 10);
}

void Buzzer_Off(void)
{
    GPIOB->BSRR = (1U << (10 + 16));
}
