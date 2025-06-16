#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "SysTimer.h"

#include <string.h>
#include <stdio.h>
#include "Char_to_Morse.h"

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

void UART_input_handler(){	//
	char rxByte[100];
	printf("Give sentence to print in morse then press enter:\r\n");
	scanf ("%[^\n]%*c", &rxByte);
	
	if (rxByte == '1'){
		LED_On();
		delay(1000);
		LED_Off();
		
	}
	else if (rxByte == '2'){
		LED_On();
		delay(2000);
		LED_Off();
		
	}
	printf("LED is Off\r\n\r\n");
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
	int a;
	char b[] = "Done";
	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	SysTick_Init();
	LED_Init();
	UART2_Init();
	
	a = 0;
	while (1){
		/*
		LED_Off();
		UART_led_controller();
		UART_print_Done();
		a++;
		*/
		send_morse_string("HELLO WORLD");
    unit_delay(14);
		
	}
}

