/**
  ******************************************************************************
  * @file    main.c
  * @author  Oscar Alvarez
  * @version V0.1
  * @brief   Main function to turn on an LED on a STM Nucleo board.
  ******************************************************************************
*/

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stdint.h>

int main(void)
{
	uint32_t * pClkCtrolReg = (uint32_t *)0x40023830;
	uint32_t * pPortBModeReg = (uint32_t *)0x40020400;
	uint32_t * pPortBOutReg = (uint32_t *)0x40020414;

	// 1. enable the clock for GPIOB peripheral in the AHB1ENR
	uint32_t temp = *pClkCtrolReg; // read register status
	temp = temp | 0x02; // modify the bit needed
	*pClkCtrolReg = temp; // save the register new value

	// alternative 1 not using variable temp
	// *pClkCtrolReg = *pClkCtrolReg | 0x08;

	//alternative 2 short C notation
	// *pClkCtrolReg |= 0x08;

	// 2. configure the mode of the IO pin as output
	*pPortBModeReg &= 0xFFFF3FFF; // clear the 14 and 15 bit positions (CLEAR)
	*pPortBModeReg |= 0x4000; // make 14 bit position as 1 (SET)

	// 3. SET the 7 bit of the output data register to make I/O pin 7 as HIGH.
	*pPortBOutReg |= 0x80;


	while(1);
}
