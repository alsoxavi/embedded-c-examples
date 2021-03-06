/**
  ******************************************************************************
  * @file    main.c
  * @author  Oscar Alvarez
  * @version V1.0
  * @brief   Example on how to read input pins
  ******************************************************************************
*/

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stdint.h>

int main(void)
{
	uint32_t volatile * pClkCtrolReg = (uint32_t *)0x40023830;

	uint32_t volatile * pPortBModeReg = (uint32_t *)0x40020400;
	uint32_t volatile * pPortBOutReg = (uint32_t *)0x40020414;

	uint32_t volatile * pPortCModeReg = (uint32_t *)0x40020800;
	uint32_t volatile * pPortCInputReg = (uint32_t *)0x40020810;

	// 1. enable the clock for GPIOB and GPIOC
	*pClkCtrolReg |= (1 << 1);
	*pClkCtrolReg |= (1 << 2);

	// 2. configuring PB7 as output
	*pPortBModeReg &= ~(3 << 14);
	*pPortBModeReg |= (1 << 14);

	// 3. configuring PC13 as input (CLEAR 26 and 27 bit positions)
	*pPortCModeReg &= ~(3 << 26);

	while(1)
	{
		// 4. read the pin status of PC13 (GPIOC INPUT DATA REGISTER)
		uint8_t pinStatus = (uint8_t)((*pPortCInputReg >> 13) & 0x01);
		if (pinStatus) {
			*pPortBOutReg |= (1 << 7);
		} else {
			*pPortBOutReg &= ~(1 << 7);
		}
	}
}
