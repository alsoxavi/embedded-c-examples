/**
  ******************************************************************************
  * @file    main.c
  * @author  Oscar Alvarez
  * @version V1.0
  * @brief   Same led toggle example but now using bit fields.
  ******************************************************************************
*/

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stdint.h>

#include "hardware.h"

int main(void)
{

	RCC_AHB1ENR_t volatile * const pClkCtrl = (RCC_AHB1ENR_t *) 0x40023830;
	GPIOx_MODER_t volatile * const pPortBMode = (GPIOx_MODER_t *) 0x40020400;
	GPIOx_ODR_t volatile * const pPortBOutData = (GPIOx_ODR_t *) 0x40020414;

	pClkCtrl -> gpiob_en = 1;

	pPortBMode -> pin_7 = 1;

	while(1)
	{
		pPortBOutData -> pin_7 = 1;

		for(uint32_t i = 0; i <= 300000; i++);

		pPortBOutData -> pin_7 = 0;

		for(uint32_t i = 0; i <= 300000; i++);
	}

}
