/**
  ******************************************************************************
  * @file    main.c
  * @author  Oscar Alvarez
  * @version V1.0
  * @brief   Example showing how ISR works.
  ******************************************************************************
*/
#include <stdint.h>
#include <stdio.h>

//global shared variable between main code and ISR
uint8_t volatile g_button_pressed = 0;

uint32_t g_button_press_count =0;

void button_init(void);

													  //BASE REGISTER + OFFSET
uint32_t volatile *pEXTTIPendReg			= (uint32_t*) (0x40013C00 + 0x14);
uint32_t volatile *pClkCtrolReg				= (uint32_t*) (0x40023800 + 0x30);
uint32_t volatile *pClkCtrolRegApb2			= (uint32_t*) (0x40023800 + 0x24);
uint32_t volatile *pGPIOAModeReg 			= (uint32_t*) (0x40020000 + 0x00);
uint32_t volatile *pEXTIMaskReg 			= (uint32_t*) (0x40013C00 + 0x00);
uint32_t volatile *pEXTTIEdgeCtrolReg		= (uint32_t*) (0x40013C00 + 0x08);
uint32_t volatile *pNVICIRQEnReg 			= (uint32_t*) 0xE000E100;


int main(void)
{
	button_init();

	while(1)
	{
		//Disable interrupt
		*pEXTIMaskReg &= ~( 1 << 0);

		if(g_button_pressed){
			//Some delay until button debouncing gets over
			for(uint32_t volatile i=0;i<500000/2;i++);
			g_button_press_count++;
			printf("Button is pressed : %lu\n",g_button_press_count);
			g_button_pressed = 0;
		}

		//Enable interrupt
		*pEXTIMaskReg |= ( 1 << 0);
	}


}


void button_init(void)
{

  *pClkCtrolReg |= (1 << 2);

  *pClkCtrolRegApb2 |= ( 1 << 14);

  *pEXTTIEdgeCtrolReg |= ( 1 << 13);

  *pEXTIMaskReg |= ( 1 << 13);

  *pNVICIRQEnReg |= ( 1 << 6);

}

/* This is button interrupt handler*/
void EXTI0_IRQHandler(void)
{
	//Make this flag SET . if button pressed
  g_button_pressed = 1;

  *pEXTTIPendReg |= ( 1 << 0);
}


