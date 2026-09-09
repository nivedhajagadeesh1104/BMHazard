#include "stm32f446xx.h"
#include "delay.h"
#include "keypad.h"

static const char keymap[4][4] =
{
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

char Keypad_GetKey(void)
{
    uint32_t row;
    uint32_t col;

    for (row = 0; row < 4; row++)
    {
        /* Set all rows HIGH */
        GPIOC->BSRR = 0x0000000F;

        /* Current row LOW */
        GPIOC->BSRR = (1U << (row + 16));

        Delay_ms(1);

        for (col = 0; col < 4; col++)
        {
            /* Column pins PC4-PC7 */
            if ((GPIOC->IDR & (1U << (col + 4))) == 0)
            {
                /* Debounce */
                Delay_ms(20);

                if ((GPIOC->IDR & (1U << (col + 4))) == 0)
                {
                    /* Wait for key release */
                    while ((GPIOC->IDR & (1U << (col + 4))) == 0)
                    {
                    }

                    return keymap[row][col];
                }
            }
        }
    }

    return 0;
}
