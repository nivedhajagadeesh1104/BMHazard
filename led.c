#include "stm32f446xx.h"
#include "led.h"

void White_On(void)
{
    GPIOA->BSRR = (1U << 1);
}

void White_Off(void)
{
    GPIOA->BSRR = (1U << (1 + 16));
}


void Green_On(void)
{
    GPIOB->BSRR = (1U << 5);
}

void Green_Off(void)
{
    GPIOB->BSRR = (1U << (5 + 16));
}


void Red_On(void)
{
    GPIOA->BSRR = (1U << 6);
}

void Red_Off(void)
{
    GPIOA->BSRR = (1U << (6 + 16));
}


void LEDs_All_Off(void)
{
    White_Off();
    Green_Off();
    Red_Off();
}
