/**
  ******************************************************************************
  * @file    main.c
  * @author  Oscar Alvarez
  * @version V1.0
  * @brief   Default main function.
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

	*pClkCtrolReg |= (1 << 1); // SET the second bit

	*pPortBModeReg &= ~(3 << 14); // CLEAR the 14 and 15 bit positions
	*pPortBModeReg |= (1 << 14); // SET the 14 bit position

	while(1)
	{
	*pPortBOutReg |= (1 << 7); // SET the 7 bit 1

	// introduce of software delay
	for(uint32_t i = 0; i <= 300000; i++);

	*pPortBOutReg &= ~(1 << 7); // SET the 7 bit 1

	// introduce of software delay
	for(uint32_t i = 0; i <= 300000; i++);
	}
}
