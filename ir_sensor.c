#include "stm32f446xx.h"
#include "ir_sensor.h"

uint8_t IR_PersonDetected(void)
{
    if ((GPIOB->IDR & (1U << 0)) == 0)
    {
        return 1;
    }

    return 0;
}
