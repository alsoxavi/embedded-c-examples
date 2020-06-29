/**
  ******************************************************************************
  * @file    main.c
  * @author  Oscar Alvarez
  * @version V1.0
  * @brief   Matrix 4x4 keypad reading example
  ******************************************************************************
*/

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stdint.h>
#include <stdio.h>

#include "hardware.h"

void delay()
{
	for(uint32_t i = 0; i < 200000 ; i++);
}

int main(void)
{
	// Register addresses
	RCC_AHB1ENR_t volatile * const pClockCtrl = (RCC_AHB1ENR_t *) (0x40023830 + 0x30);
	GPIOx_MODER_t volatile * const pPortDMode = (GPIOx_MODER_t *) (0x40020C00 + 0x00);
	GPIOx_PUPDR_t volatile * const pPortDPull = (GPIOx_PUPDR_t *) (0x40020C00 + 0x0C);
	GPIOx_IDR_t volatile * const pPortDInput = (GPIOx_IDR_t *) (0x40020C00 + 0x10);
	GPIOx_ODR_t volatile * const pPortDOut = (GPIOx_ODR_t *) (0x40020C00 + 0x14);

	// Enable port D clock
	pClockCtrl -> gpiod_en = ENABLE;

	// Set PD0, PD1, PD2, PD3 as output (rows)
	pPortDMode -> pin_0 = OUTPUT_MODE;
	pPortDMode -> pin_1 = OUTPUT_MODE;
	pPortDMode -> pin_2 = OUTPUT_MODE;
	pPortDMode -> pin_3 = OUTPUT_MODE;

	// Set PD4, PD5, PD6, PD7 as input (columns)
	pPortDMode -> pin_4 = INPUT_MODE;
	pPortDMode -> pin_5 = INPUT_MODE;
	pPortDMode -> pin_6 = INPUT_MODE;
	pPortDMode -> pin_7 = INPUT_MODE;

	// Set Pull-Up for PD4, PD5, PD6, PD7
	pPortDPull -> pin_4 = PULL_UP;
	pPortDPull -> pin_5 = PULL_UP;
	pPortDPull -> pin_6 = PULL_UP;
	pPortDPull -> pin_7 = PULL_UP;

	// Make all rows HIGH
	pPortDOut -> pin_0 = HIGH;
	pPortDOut -> pin_1 = HIGH;
	pPortDOut -> pin_2 = HIGH;
	pPortDOut -> pin_3 = HIGH;

	//Loop begin =======================================
	while(1)
	{
		// Make R1 LOW (PD0)
		pPortDOut -> pin_0 = LOW;

		// Read C1 (PD4)
		if(!(pPortDInput -> pin_4))
		{
			delay();
			// key is pressed
			printf("1\n");
		}
		// Read C2 (PD5)
		if(!(pPortDInput -> pin_5))
		{
			delay();
			// key is pressed
			printf("2\n");
		}
		// Read C3 (PD6)
		if(!(pPortDInput -> pin_6))
		{
			delay();
			// key is pressed
			printf("3\n");
		}
		// Read C4 (PD7)
		if(!(pPortDInput -> pin_7))
		{
			delay();
			// key is pressed
			printf("A\n");
		}

		// Make R2 LOW (PD1)
		pPortDOut -> pin_0 = HIGH;
		pPortDOut -> pin_1 = LOW;

		// Read C1 (PD4)
		if(!(pPortDInput -> pin_4))
		{
			delay();
			// key is pressed
			printf("4\n");
		}
		// Read C2 (PD5)
		if(!(pPortDInput -> pin_5))
		{
			delay();
			// key is pressed
			printf("5\n");
		}
		// Read C3 (PD6)
		if(!(pPortDInput -> pin_6))
		{
			delay();
			// key is pressed
			printf("6\n");
		}
		// Read C4 (PD7)
		if(!(pPortDInput -> pin_7))
		{
			delay();
			// key is pressed
			printf("B\n");
		}

		// Make R3 LOW (PD2)
		pPortDOut -> pin_1 = HIGH;
		pPortDOut -> pin_2 = LOW;

		// Read C1 (PD4)
		if(!(pPortDInput -> pin_4))
		{
			delay();
			// key is pressed
			printf("7\n");
		}
		// Read C2 (PD5)
		if(!(pPortDInput -> pin_5))
		{
			delay();
			// key is pressed
			printf("8\n");
		}
		// Read C3 (PD6)
		if(!(pPortDInput -> pin_6))
		{
			delay();
			// key is pressed
			printf("9\n");
		}
		// Read C4 (PD7)
		if(!(pPortDInput -> pin_7))
		{
			delay();
			// key is pressed
			printf("C\n");
		}

		// Make R4 LOW (PD3)
		pPortDOut -> pin_2 = HIGH;
		pPortDOut -> pin_3 = LOW;

		// Read C1 (PD4)
		if(!(pPortDInput -> pin_4))
		{
			delay();
			// key is pressed
			printf("*\n");
		}
		// Read C2 (PD5)
		if(!(pPortDInput -> pin_5))
		{
			delay();
			// key is pressed
			printf("0\n");
		}
		// Read C3 (PD6)
		if(!(pPortDInput -> pin_6))
		{
			delay();
			// key is pressed
			printf("#\n");
		}
		// Read C4 (PD7)
		if(!(pPortDInput -> pin_7))
		{
			delay();
			// key is pressed
			printf("D\n");
		}

		// Make R4 HIGH (PD3)
		pPortDOut -> pin_3 = HIGH;
	}
}
