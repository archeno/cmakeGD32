/*!
   \file    main.c
   \brief   USART printf

   \version 2016-08-15, V1.0.0, firmware for GD32F4xx
   \version 2018-12-12, V2.0.0, firmware for GD32F4xx
   \version 2020-09-30, V2.1.0, firmware for GD32F4xx
   \version 2022-03-09, V3.0.0, firmware for GD32F4xx
*/

/*
    Copyright (c) 2022, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32f4xx.h"
#include <stdio.h>
void delay()
{
    for(int i=0; i<1000; i++)
    for(int j=0; j<10000; j++);
}

#define MY_TICK_PERSEOCND 1000
/*  UART3  TX  RX 
    PC      10   11
           PC12 PD2
/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/

void getsum(int * pdata)
{
     *pdata += 2;
}
static uint32_t tick_count;
static uint32_t  sencond_flag;
void SysTick_Handler()
{
    if(tick_count++ == MY_TICK_PERSEOCND)
    {
        tick_count = 0;
       sencond_flag = 1;
    }
}
int volatile g_data;
int main(void)
{


    /* Config Systick clock 10ms */ 
    SysTick_Config(SystemCoreClock/1000 -1);

    /* enable GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOC);

    /* enable USART clock */
    rcu_periph_clock_enable(RCU_UART3);

    /* configure the USART0 TX pin and USART0 RX pin */
    gpio_af_set(GPIOC, GPIO_AF_8, GPIO_PIN_10);
    gpio_af_set(GPIOC, GPIO_AF_8, GPIO_PIN_11);

    /* configure USART0 TX as alternate function push-pull */
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    /* configure USART0 RX as alternate function push-pull */
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_11);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_11);

    /* USART configure */
    usart_deinit(UART3);
    usart_baudrate_set(UART3, 115200U);
    usart_receive_config(UART3, USART_RECEIVE_ENABLE);
    usart_transmit_config(UART3, USART_TRANSMIT_ENABLE);
    usart_enable(UART3);
    
   
    while(1)
    {
        if(sencond_flag)
        {
            sencond_flag  = 0;
            uart_printf("a usart transmit test example!\r\n");
        }
        getsum(&g_data);
        // uart_printf("a usart transmit test example!\r\n");
        // delay();
    };
}

void HardFault_Handler()
{

}

void uart_printf(char * string)
{
    while(*string++ != '\0')
    {
         usart_data_transmit(UART3, (uint8_t)(*string));
         while(RESET == usart_flag_get(UART3, USART_FLAG_TBE));
    }
}
