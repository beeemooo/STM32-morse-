#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "SysTimer.h"

#include "ring_buffer.h"
#include <string.h>
#include <stdio.h>
#include "Char_to_Morse.h"

#define MAX_MSG_LEN 255          // maximum input length

char RxComByte = 0;
uint8_t buffer[BufferSize];		//It is 32

/*
void demo_of_printf_scanf(){	//
	char rxByte;
	printf("Give Red LED control input (Y = On, N = off):\r\n");
	scanf ("%c", &rxByte);
	if (rxByte == 'N' || rxByte == 'n'){
		LED_Off();
		printf("LED Turned On for 1sec\r\n\r\n");
	}
	else if (rxByte == 'Y' || rxByte == 'y'){
		LED_On();
		printf("LED Turned On for 2sec\r\n\r\n");
	}
}
*/

/*
void UART_input_handler(){	//
	char rxByte[256];
	printf("Give sentence to print in morse then press enter:\r\n");
	//scanf ("%255[^\n]%*c", rxByte);
	scanf("%255[^\r]%*c", rxByte);  

	printf("processing morse code");
	send_morse_string(rxByte);
	
	printf("DONE\r\n\r\n");
}
*/


void UART_input_handler(void)
{
    char msg[MAX_MSG_LEN + 1];   // +1 byte space for null terminating
    uint16_t idx = 0;

    printf("Give sentence to print in morse then press enter:\r\n");

    /* === receiving === */
    while (1)
    {
        int ch = getchar();          
        if (ch == '\r' || ch == '\n') {
            //change line
            putchar('\r');
            putchar('\n');
            msg[idx] = '\0';         // terminating string
            break;
        }

        /* bacspace logic */
        if ((ch == 0x08 || ch == 0x7F) && idx > 0) {
            --idx;
            /* removing char at terminal */
            putchar('\b'); putchar(' '); putchar('\b');
            continue;
        }

        /* save char in morse buffer */
        if (idx < MAX_MSG_LEN) {
            msg[idx++] = (char)ch;
            putchar(ch);             // echo string
        }
        //if buffer is full, ignore the input
    }

    /* === 2. process morse === */
    printf("\r\nprocessing morse code...\r\n");
    send_morse_string(msg);          // convert string to morse code
    printf("DONE\r\n\r\n");
}

/*
void demo_of_UART_print(int a){
	int n, i;
	float b;
	b = (float)a/100;
	n = sprintf((char *)buffer, "a = %d\t", a);
	n += sprintf((char *)buffer + n, "b = %f\r\n", b);
	USART_Write(USART2, buffer, n);		
	for (i = 0; i < 8000000; i++); // Delay
	LED_Toggle();
}
*/

void UART_print_Done(void){
	int n, i;
	
	n = sprintf((char *)buffer, "Done\n");
	
	USART_Write(USART2, buffer, n);		
	for (i = 0; i < 8000000; i++); // Delay
	
}

int main(void){
	
	
	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	SysTick_Init();
	LED_Init();
	UART2_Init();
	
	volatile uint32_t * debug_odr = &(GPIOA -> ODR);

    printf("\r\n--- STM32 Morse Echo Demo ---\r\n");

    
    while (1)
    {
				
        UART_input_handler();  // processing morse code
        unit_delay(14);        // delay after processing entire sentence
    }

}


