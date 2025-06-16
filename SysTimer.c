
#include "SysTimer.h"

volatile uint32_t msTicks;


//-------------------------------------------------------------------------------------------
// Initialize SysTick	
//-------------------------------------------------------------------------------------------	
//uint32_t IRQn;
//uint8_t  priority, priority_value;

void SysTick_Init(void){
	
	//  SysTick Control and Status Register
	SysTick->CTRL = 0;										// Disable SysTick IRQ and SysTick Counter
	
	// SysTick Reload Value Register
	SysTick->LOAD = 10000 - 1;    // 1ms, Default clock
	
	// SysTick Current Value Register
	SysTick->VAL = 0;


//	IRQn = (((uint32_t)(int32_t)SysTick_IRQn) & 0xFUL)-4UL;
//	priority = 1;
//	priority_value = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
//	SCB->SHP[IRQn] = priority_value;
	
	NVIC_SetPriority(SysTick_IRQn, 1);		// Set Priority to 1
	NVIC_EnableIRQ(SysTick_IRQn);					// Enable EXTI0_1 interrupt in NVIC

	// Enables SysTick exception request
	// 1 = counting down to zero asserts the SysTick exception request
	// 0 = counting down to zero does not assert the SysTick exception request
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	
	// Select processor clock
	// If CLKSOURCE = 0, the external clock is used. The frequency of SysTick clock is the frequency of the AHB clock divided by 8.
	// If CLKSOURCE = 1, the processor clock is used.
	SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;		
	
	// Enable SysTick IRQ and SysTick Timer
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  
}





//-------------------------------------------------------------------------------------------
// SysTick Interrupt Handler
//-------------------------------------------------------------------------------------------
void SysTick_Handler(void){
	msTicks++;
}
	
//-------------------------------------------------------------------------------------------
// Delay in ms
//-------------------------------------------------------------------------------------------
void delay (uint32_t T){
  uint32_t curTicks;
	msTicks = 0;
  curTicks = msTicks;
  while ((msTicks - curTicks) < T);
	
	msTicks = 0;
}
