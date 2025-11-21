/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 3/6/2025     ******************/
/********************Version : 1.0          ******************/
/********************SWC     : DMA          ******************/
/*************************************************************/

#include"StdTypes.h"
#include"BitMath.h"
#include"errorStatuse.h"

#include"RCC/RCC_Int.h"

#include"GPIO/GPIO_Int.h"

#include"NVIC/NVIC_Interface.h"

#include"DMA_Interface.h"

GPIO_PinCongig_t PC13 = {GPIO_u8GPIO_C , GPIO_u8PIN13 , GPIO_u8Output10MHzPushPull};
DMA_ConfigStr_t dma_channel1 = {DMA_u8Channel_1, DMA_u8Low , DMA_u8_1Byte , DMA_u8MEM2MEM , DMA_u8Enable,DMA_u8Enable,DMA_u8Disable};
void tog(void)
{
	GPIO_enuTogPinVal(&PC13);
	return;
}



int main(void)
{
	u16 i = 0;
	u8 arr1[1000];
	u8 arr2[1000];
	RCC_VidInitSysClk();
	RCC_enuStatePeripheralClk(IOPC, RCC_u8_ENABLE);
	RCC_enuStatePeripheralClk(DMA1, RCC_u8_ENABLE);

	GPIO_enuSetPinMode(&PC13);

	DMA_enuDmaChannelInit(&dma_channel1);

	NVIC_enuEnableINT(NVIC_u8_DMA1_Channel1);

	DMA_enuCallBack(&dma_channel1, tog);
	DMA_enuDmaAsyncChannelTrans(&dma_channel1, (u32)arr1, (u32)arr2, 1000);

    /* Loop forever */
	for(i = 0;i < 1000;i++)
	{
		arr2[i] = arr1[i];
	}

	return 0;
}
