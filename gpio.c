#include "gpio.h"

void GPIO_Init(void)
{
    /* Enable GPIOA, GPIOB and GPIOC clocks */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    /* =====================================================
       GPIOA
       PA1  -> White LED
       PA6  -> Red LED
       ===================================================== */

    /* PA1 output */
    GPIOA->MODER &= ~(3U << (1 * 2));
    GPIOA->MODER |=  (1U << (1 * 2));

    /* PA6 output */
    GPIOA->MODER &= ~(3U << (6 * 2));
    GPIOA->MODER |=  (1U << (6 * 2));

    /* Push-pull */
    GPIOA->OTYPER &= ~(1U << 1);
    GPIOA->OTYPER &= ~(1U << 6);

    /* No pull-up/pull-down */
    GPIOA->PUPDR &= ~(3U << (1 * 2));
    GPIOA->PUPDR &= ~(3U << (6 * 2));


    /* =====================================================
       GPIOB
       PB0  -> IR sensor input
       PB5  -> Green LED
       PB10 -> Buzzer
       ===================================================== */

    /* PB0 input */
    GPIOB->MODER &= ~(3U << (0 * 2));

    /* PB0 pull-up
       IR sensor is ACTIVE LOW */
    GPIOB->PUPDR &= ~(3U << (0 * 2));
    GPIOB->PUPDR |=  (1U << (0 * 2));


    /* PB5 output */
    GPIOB->MODER &= ~(3U << (5 * 2));
    GPIOB->MODER |=  (1U << (5 * 2));

    /* PB10 output */
    GPIOB->MODER &= ~(3U << (10 * 2));
    GPIOB->MODER |=  (1U << (10 * 2));

    GPIOB->OTYPER &= ~(1U << 5);
    GPIOB->OTYPER &= ~(1U << 10);

    GPIOB->PUPDR &= ~(3U << (5 * 2));
    GPIOB->PUPDR &= ~(3U << (10 * 2));


    /* =====================================================
       GPIOC
       PC0-PC3 -> Keypad rows
       PC4-PC7 -> Keypad columns
       ===================================================== */

    /* PC0-PC3 OUTPUT */
    for (int i = 0; i < 4; i++)
    {
        GPIOC->MODER &= ~(3U << (i * 2));
        GPIOC->MODER |=  (1U << (i * 2));

        GPIOC->OTYPER &= ~(1U << i);

        GPIOC->PUPDR &= ~(3U << (i * 2));
    }

    /* PC4-PC7 INPUT */
    for (int i = 4; i < 8; i++)
    {
        GPIOC->MODER &= ~(3U << (i * 2));

        /* Internal pull-up */
        GPIOC->PUPDR &= ~(3U << (i * 2));
        GPIOC->PUPDR |=  (1U << (i * 2));
    }

    /* Initial states */
    GPIOA->BSRR = (1U << (1 + 16));   // PA1 OFF
    GPIOA->BSRR = (1U << (6 + 16));   // PA6 OFF

    GPIOB->BSRR = (1U << (5 + 16));   // PB5 OFF
    GPIOB->BSRR = (1U << (10 + 16));  // PB10 OFF

    /* Keypad rows HIGH */
    GPIOC->BSRR = 0x0000000F;
}
