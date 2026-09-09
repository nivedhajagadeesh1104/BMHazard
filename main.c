#include "stm32f446xx.h"
#include <stdint.h>

#include "gpio.h"
#include "delay.h"
#include "keypad.h"
#include "led.h"
#include "buzzer.h"
#include "ir_sensor.h"


#define PASSWORD_LENGTH  4
#define MAX_ATTEMPTS     3
#define LOCKOUT_TIME     10000


const char correct_password[PASSWORD_LENGTH + 1] = "1234";


/* =====================================================
   PASSWORD CHECK
   ===================================================== */

uint8_t CheckPassword(void)
{
    char entered_password[PASSWORD_LENGTH + 1];

    char key;

    uint8_t index = 0;


    while (1)
    {
        key = Keypad_GetKey();

        if (key == 0)
            continue;


        /* Number */
        if (key >= '0' && key <= '9')
        {
            if (index < PASSWORD_LENGTH)
            {
                entered_password[index] = key;
                index++;
            }
        }


        /* Clear */
        else if (key == '*')
        {
            index = 0;
        }


        /* Submit */
        else if (key == '#')
        {
            if (index != PASSWORD_LENGTH)
            {
                return 0;
            }

            entered_password[index] = '\0';


            for (index = 0;
                 index < PASSWORD_LENGTH;
                 index++)
            {
                if (entered_password[index] !=
                    correct_password[index])
                {
                    return 0;
                }
            }

            return 1;
        }
    }
}


/* =====================================================
   LOCKOUT
   ===================================================== */

void Lockout(void)
{
    White_Off();
    Green_Off();

    Red_On();
    Buzzer_On();

    Delay_ms(LOCKOUT_TIME);

    Red_Off();
    Buzzer_Off();
}


/* =====================================================
   MAIN
   ===================================================== */

int main(void)
{
    uint8_t attempts;
    uint8_t password_correct;


    /* GPIO initialization */
    GPIO_Init();


    /* SysTick initialization */
    SysTick_Init();


    /* Everything OFF */
    LEDs_All_Off();
    Buzzer_Off();


    while (1)
    {
        /* =============================================
           PERSON DETECTION
           IR ACTIVE LOW
           ============================================= */

        if (IR_PersonDetected())
        {
            /* Person detected */

            White_On();
            Green_Off();
            Red_Off();
            Buzzer_Off();

            Delay_ms(500);


            attempts = 0;


            /* =========================================
               PASSWORD ATTEMPTS
               ========================================= */

            while (attempts < MAX_ATTEMPTS)
            {
                password_correct = CheckPassword();


                /* =====================================
                   CORRECT PASSWORD
                   ===================================== */

                if (password_correct)
                {
                    /*
                       ACCESS GRANTED

                       White OFF
                       Green ON
                       Red OFF
                       Buzzer OFF
                    */

                    White_Off();
                    Red_Off();
                    Buzzer_Off();

                    Green_On();


                    /* Access granted for 3 seconds */
                    Delay_ms(3000);


                    Green_Off();

                    break;
                }


                /* =====================================
                   WRONG PASSWORD
                   ===================================== */

                else
                {
                    attempts++;


                    /*
                       ACCESS DENIED

                       White OFF
                       Green OFF
                       Red ON
                       Buzzer ON
                    */

                    White_Off();
                    Green_Off();

                    Red_On();
                    Buzzer_On();


                    /* Warning */
                    Delay_ms(1000);


                    Red_Off();
                    Buzzer_Off();


                    /* =================================
                       THREE WRONG ATTEMPTS
                       ================================= */

                    if (attempts >= MAX_ATTEMPTS)
                    {
                        Lockout();
                    }

                    else
                    {
                        /* Ready for another PIN */

                        White_On();

                        Delay_ms(500);
                    }
                }
            }


            /* =========================================
               WAIT UNTIL PERSON LEAVES
               ========================================= */

            while (IR_PersonDetected())
            {
                Delay_ms(50);
            }


            /* Back to idle */

            LEDs_All_Off();
            Buzzer_Off();

            Delay_ms(500);
        }


        Delay_ms(50);
    }
}
