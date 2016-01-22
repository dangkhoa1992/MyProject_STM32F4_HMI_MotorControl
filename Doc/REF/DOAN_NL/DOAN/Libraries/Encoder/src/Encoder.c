#include "stm32f4xx.h"
#include "Encoder.h"

void ENC_Config(int Autoreload)
{
	 /* TIM3 configuration: Encoder Input mode ------------------------
     The encoder output channel A and B are connected to TIM3 CH1 (PA6) and CH2 (PA7), 
  ------------------------------------------------------------ */
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* TIM3 & GPIOA clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  
  /* TIM3 CH1 & CH2 configuration : PA6 & PA7 */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Connect TIM pin to AF2 */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
	
	/* Set them up as encoder inputs */
	/* Set both inputs to rising polarity to let it use both edges */
	TIM_EncoderInterfaceConfig (TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); 
	TIM_SetAutoreload (TIM3, Autoreload); 
	
	/* Turn on the timer/counters */
	TIM_Cmd (TIM3, ENABLE);
	
	/* Reset encoder */
	TIM_SetCounter (TIM3,0);
}

uint32_t EncoderValue(void)
{
	return TIM_GetCounter (TIM3);
}
