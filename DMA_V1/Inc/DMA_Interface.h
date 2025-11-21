/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 3/6/2025     ******************/
/********************Version : 1.0          ******************/
/********************SWC     : DMA          ******************/
/*************************************************************/

#ifndef DMA_INTERFACE_H_
#define DMA_INTERFACE_H_

#include"StdTypes.h"
#include"errorStatuse.h"
/******************************   typedefs   ****************************************/

typedef enum
{
	DMA_u8Channel_1 = 1,
	DMA_u8Channel_2,
	DMA_u8Channel_3,
	DMA_u8Channel_4,
	DMA_u8Channel_5,
	DMA_u8Channel_6,
	DMA_u8Channel_7
}DMA_ChannelID_t;


typedef enum
{
	DMA_u8Low,
	DMA_u8Medium,
	DMA_u8High,
	DMA_u8VeryHigh
}DMA_ChannelPriority_t;

typedef enum
{
	DMA_u8Peripheral2MEM,
	DMA_u8MEM2Peripheral,
	DMA_u8MEM2MEM
}DMA_DataTrans_t;

typedef enum
{
	DMA_u8Disable,
	DMA_u8Enable

}DMA_States_t;

typedef enum
{
	DMA_u8_1Byte,
	DMA_u8_2Byte,
	DMA_u8_4Byte

}DMA_DataSize_t;


typedef struct
{
	DMA_ChannelID_t ChannelNumber;
	DMA_ChannelPriority_t ChannelPriority;
	DMA_DataSize_t DataSize;
	DMA_DataTrans_t DataTransType;
	DMA_States_t IncrementMode;
	DMA_States_t EnableTCINT;
	DMA_States_t EnableCircMod;
}DMA_ConfigStr_t;


/************************************************************************************/


/******************************   functions' prototypes   ****************************************/

/*This function is used to initialize a specific DMA Channel*/
ES_t DMA_enuDmaChannelInit(const DMA_ConfigStr_t* Copy_PstrDmaChannelConfig);

/*This function is used to transfer data by DMA from source to destination (by interrupt)*/
ES_t DMA_enuDmaAsyncChannelTrans(const DMA_ConfigStr_t* Copy_PstrDmaChannelConfig , u32 Copy_u32SrcAddress , u32 Copy_u32DesAddress , u16 Copy_u16NumOfTrans);

/*This function is used to transfer data by DMA from source to destination (by polling)*/
ES_t DMA_enuDmaSyncChannelTrans(const DMA_ConfigStr_t* Copy_PstrDmaChannelConfig , u32 Copy_u32SrcAddress , u32 Copy_u32DesAddress , u16 Copy_u16NumOfTrans);

/*This function is used to set ISR functions*/
ES_t DMA_enuCallBack(const DMA_ConfigStr_t* Copy_PstrDmaChannelConfig , void (*DMA_vidPtr2Fun)(void) );


/************************************************************************************/

#endif /* DMA_INTERFACE_H_ */
