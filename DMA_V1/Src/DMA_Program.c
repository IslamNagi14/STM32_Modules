/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 3/6/2025     ******************/
/********************Version : 1.0          ******************/
/********************SWC     : DMA          ******************/
/*************************************************************/


#include"StdTypes.h"
#include"errorStatuse.h"
#include"BitMath.h"
#include"stm32f103xx.h"


#include"DMA_Config.h"
#include"DMA_Private.h"
#include"DMA_Interface.h"



static volatile void (*DMA_AVidPtr2Fun[7])(void) = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};



/*This function is used to initialize a specific DMA Channel*/
ES_t DMA_enuDmaChannelInit(const DMA_ConfigStr_t* Copy_PstrDmaChannelConfig)
{
	ES_t Local_enuErrorState = ES_OK;
	if(Copy_PstrDmaChannelConfig)
	{
		switch(Copy_PstrDmaChannelConfig ->ChannelNumber)
		{
		case DMA_u8Channel_1:
			DMA -> CCR1 = ZERO;
			DMA -> CCR1 |= ( Copy_PstrDmaChannelConfig ->ChannelPriority << 12 ); // SET Channel priority
			DMA -> CCR1 |= ( Copy_PstrDmaChannelConfig ->DataSize << 10 );        // set memory size
			DMA -> CCR1 |= ( Copy_PstrDmaChannelConfig ->DataSize << 8 );         // set pripheral size
			switch(Copy_PstrDmaChannelConfig ->DataTransType)
			{
			case DMA_u8Peripheral2MEM:
				CLEARBIT(DMA -> CCR1 , 4); //SET peripheral to memory mode
				break;
			case DMA_u8MEM2Peripheral:
				SETBIT(DMA -> CCR1 , 4);   //SET memory to  peripheral mode
				break;
			case DMA_u8MEM2MEM:
				SETBIT(DMA -> CCR1 , 14);  //SET memory to  memory mode
				break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;break;
			}

			if(DMA_u8Enable == Copy_PstrDmaChannelConfig ->IncrementMode)
			{
				//set Increment Mode
				SETBIT(DMA -> CCR1 , 6);
				SETBIT(DMA -> CCR1 , 7);
			}
			else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->IncrementMode){}
			else
			{
				Local_enuErrorState = ES_Out_Of_Range;
			}
			if(DMA_u8Enable == Copy_PstrDmaChannelConfig ->EnableTCINT)
			{
				SETBIT(DMA -> CCR1 , 1);//Enable Complete transfer INT

			}
			else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->EnableTCINT){}
			else
			{
				Local_enuErrorState = ES_Out_Of_Range;
			}
			if(DMA_u8Enable == Copy_PstrDmaChannelConfig -> EnableCircMod)
			{
				SETBIT(DMA -> CCR1 , 5);//Enable Circular mode
			}
			else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->EnableCircMod){}
			else
			{
				Local_enuErrorState = ES_Out_Of_Range;
			}
			break;
			case DMA_u8Channel_2:
				DMA -> CCR2 = ZERO;
				DMA -> CCR2 |= Copy_PstrDmaChannelConfig ->ChannelPriority << 12; // SET Channel priority
				DMA -> CCR2 |= Copy_PstrDmaChannelConfig ->DataSize << 10;        // set memory size
				DMA -> CCR2 |= Copy_PstrDmaChannelConfig ->DataSize << 8;         // set pripheral size
				switch(Copy_PstrDmaChannelConfig ->DataTransType)
				{
				case DMA_u8Peripheral2MEM:
					CLEARBIT(DMA -> CCR2 , 4);    //SET peripheral to memory mode
					break;
				case DMA_u8MEM2Peripheral:
					SETBIT(DMA -> CCR2 , 4);      //SET memory to  peripheral mode
					break;
				case DMA_u8MEM2MEM:
					SETBIT(DMA -> CCR2 , 14);     //SET memory to  memory mode
					break;
				default:
					Local_enuErrorState = ES_Out_Of_Range;break;
				}

				if(DMA_u8Enable == Copy_PstrDmaChannelConfig ->IncrementMode)
				{
					//set Increment Mode
					SETBIT(DMA -> CCR2 , 6);
					SETBIT(DMA -> CCR2 , 7);
				}
				else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->IncrementMode){}
				else
				{
					Local_enuErrorState = ES_Out_Of_Range;
				}
				if(DMA_u8Enable == Copy_PstrDmaChannelConfig ->EnableTCINT)
				{
					SETBIT(DMA -> CCR2 , 1);          //Enable Complete transfer INT

				}
				else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->EnableTCINT){}
				else
				{
					Local_enuErrorState = ES_Out_Of_Range;
				}
				if(DMA_u8Enable == Copy_PstrDmaChannelConfig -> EnableCircMod)
				{
					SETBIT(DMA -> CCR2 , 5);         //Enable Circular mode
				}
				else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->EnableCircMod){}
				else
				{
					Local_enuErrorState = ES_Out_Of_Range;
				}
				break;
				case DMA_u8Channel_3:
					DMA -> CCR3 = ZERO;
					DMA -> CCR3 |= Copy_PstrDmaChannelConfig ->ChannelPriority << 12;    // SET Channel priority
					DMA -> CCR3 |= Copy_PstrDmaChannelConfig ->DataSize << 10;           // set memory size
					DMA -> CCR3 |= Copy_PstrDmaChannelConfig ->DataSize << 8;            // set pripheral size
					switch(Copy_PstrDmaChannelConfig ->DataTransType)
					{
					case DMA_u8Peripheral2MEM:
						CLEARBIT(DMA -> CCR3 , 4);  //SET peripheral to memory mode
						break;
					case DMA_u8MEM2Peripheral:
						SETBIT(DMA -> CCR3 , 4);    //SET memory to  peripheral mode
						break;
					case DMA_u8MEM2MEM:
						SETBIT(DMA -> CCR3 , 14);   //SET memory to  memory mode
						break;
					default:
						Local_enuErrorState = ES_Out_Of_Range;break;
					}

					if(DMA_u8Enable == Copy_PstrDmaChannelConfig ->IncrementMode)
					{
						//set Increment Mode
						SETBIT(DMA -> CCR3 , 6);
						SETBIT(DMA -> CCR3 , 7);
					}
					else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->IncrementMode){}
					else
					{
						Local_enuErrorState = ES_Out_Of_Range;
					}
					if(DMA_u8Enable == Copy_PstrDmaChannelConfig ->EnableTCINT)
					{
						SETBIT(DMA -> CCR3 , 1);      //Enable Complete transfer INT

					}
					else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->EnableTCINT){}
					else
					{
						Local_enuErrorState = ES_Out_Of_Range;
					}
					if(DMA_u8Enable == Copy_PstrDmaChannelConfig -> EnableCircMod)
					{
						SETBIT(DMA -> CCR3 , 5);               //Enable Circular mode
					}
					else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->EnableCircMod){}
					else
					{
						Local_enuErrorState = ES_Out_Of_Range;
					}
					break;
					case DMA_u8Channel_4:
						DMA -> CCR4 = ZERO;
						DMA -> CCR4 |= Copy_PstrDmaChannelConfig ->ChannelPriority << 12;    // SET Channel priority
						DMA -> CCR4 |= Copy_PstrDmaChannelConfig ->DataSize << 10;           // set memory size
						DMA -> CCR4 |= Copy_PstrDmaChannelConfig ->DataSize << 8;            // set pripheral size
						switch(Copy_PstrDmaChannelConfig ->DataTransType)
						{
						case DMA_u8Peripheral2MEM:
							CLEARBIT(DMA -> CCR4 , 4);      //SET peripheral to memory mode
							break;
						case DMA_u8MEM2Peripheral:
							SETBIT(DMA -> CCR4 , 4);        //SET memory to  peripheral mode
							break;
						case DMA_u8MEM2MEM:
							SETBIT(DMA -> CCR4 , 14);       //SET memory to  memory mode
							break;
						default:
							Local_enuErrorState = ES_Out_Of_Range;break;
						}

						if(DMA_u8Enable == Copy_PstrDmaChannelConfig ->IncrementMode)
						{
							//set Increment Mode
							SETBIT(DMA -> CCR4 , 6);
							SETBIT(DMA -> CCR4 , 7);
						}
						else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->IncrementMode){}
						else
						{
							Local_enuErrorState = ES_Out_Of_Range;
						}
						if(DMA_u8Enable == Copy_PstrDmaChannelConfig ->EnableTCINT)
						{
							SETBIT(DMA -> CCR4 , 1);  //Enable Complete transfer INT

						}
						else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->EnableTCINT){}
						else
						{
							Local_enuErrorState = ES_Out_Of_Range;
						}
						if(DMA_u8Enable == Copy_PstrDmaChannelConfig -> EnableCircMod)
						{
							SETBIT(DMA -> CCR4 , 5);         //Enable Circular mode
						}
						else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->EnableCircMod){}
						else
						{
							Local_enuErrorState = ES_Out_Of_Range;
						}
						break;
						case DMA_u8Channel_5:
							DMA -> CCR5 = ZERO;
							DMA -> CCR5 |= Copy_PstrDmaChannelConfig ->ChannelPriority << 12;   // SET Channel priority
							DMA -> CCR5 |= Copy_PstrDmaChannelConfig ->DataSize << 10;          // set memory size
							DMA -> CCR5 |= Copy_PstrDmaChannelConfig ->DataSize << 8;           // set pripheral size
							switch(Copy_PstrDmaChannelConfig ->DataTransType)
							{
							case DMA_u8Peripheral2MEM:
								CLEARBIT(DMA -> CCR5 , 4);    //SET peripheral to memory mode
								break;
							case DMA_u8MEM2Peripheral:
								SETBIT(DMA -> CCR5 , 4);      //SET memory to  peripheral mode
								break;
							case DMA_u8MEM2MEM:
								SETBIT(DMA -> CCR5 , 14);     //SET memory to  memory mode
								break;
							default:
								Local_enuErrorState = ES_Out_Of_Range;break;
							}

							if(DMA_u8Enable == Copy_PstrDmaChannelConfig ->IncrementMode)
							{
								//set Increment Mode
								SETBIT(DMA -> CCR5 , 6);
								SETBIT(DMA -> CCR5 , 7);
							}
							else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->IncrementMode){}
							else
							{
								Local_enuErrorState = ES_Out_Of_Range;
							}
							if(DMA_u8Enable == Copy_PstrDmaChannelConfig ->EnableTCINT)
							{
								SETBIT(DMA -> CCR5 , 1);

							}
							else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->EnableTCINT){}
							else
							{
								Local_enuErrorState = ES_Out_Of_Range;
							}
							if(DMA_u8Enable == Copy_PstrDmaChannelConfig -> EnableCircMod)
							{
								SETBIT(DMA -> CCR5 , 5);      //Enable Circular mode
							}
							else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->EnableCircMod){}
							else
							{
								Local_enuErrorState = ES_Out_Of_Range;
							}
							break;
							case DMA_u8Channel_6:
								DMA -> CCR6 = ZERO;
								DMA -> CCR6 |= Copy_PstrDmaChannelConfig ->ChannelPriority << 12;   // SET Channel priority
								DMA -> CCR6 |= Copy_PstrDmaChannelConfig ->DataSize << 10;          // set memory size
								DMA -> CCR6 |= Copy_PstrDmaChannelConfig ->DataSize << 8;           // set pripheral size
								switch(Copy_PstrDmaChannelConfig ->DataTransType)
								{
								case DMA_u8Peripheral2MEM:
									CLEARBIT(DMA -> CCR6 , 4);     //SET peripheral to memory mode
									break;
								case DMA_u8MEM2Peripheral:
									SETBIT(DMA -> CCR6 , 4);       //SET memory to  peripheral mode
									break;
								case DMA_u8MEM2MEM:
									SETBIT(DMA -> CCR6 , 14);      //SET memory to  memory mode
									break;
								default:
									Local_enuErrorState = ES_Out_Of_Range;break;
								}

								if(DMA_u8Enable == Copy_PstrDmaChannelConfig ->IncrementMode)
								{
									//set Increment Mode
									SETBIT(DMA -> CCR6 , 6);
									SETBIT(DMA -> CCR6 , 7);
								}
								else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->IncrementMode){}
								else
								{
									Local_enuErrorState = ES_Out_Of_Range;
								}
								if(DMA_u8Enable == Copy_PstrDmaChannelConfig ->EnableTCINT)
								{
									SETBIT(DMA -> CCR6 , 1);     //Enable Complete transfer INT

								}
								else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->EnableTCINT){}
								else
								{
									Local_enuErrorState = ES_Out_Of_Range;
								}
								if(DMA_u8Enable == Copy_PstrDmaChannelConfig -> EnableCircMod)
								{
									SETBIT(DMA -> CCR6 , 5);       //Enable Circular mode
								}
								else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->EnableCircMod){}
								else
								{
									Local_enuErrorState = ES_Out_Of_Range;
								}
								break;
								case DMA_u8Channel_7:
									DMA -> CCR7 = ZERO;
									DMA -> CCR7 |= Copy_PstrDmaChannelConfig ->ChannelPriority << 12; // SET Channel priority
									DMA -> CCR7 |= Copy_PstrDmaChannelConfig ->DataSize << 10;        // set memory size
									DMA -> CCR7 |= Copy_PstrDmaChannelConfig ->DataSize << 8;         // set pripheral size
									switch(Copy_PstrDmaChannelConfig ->DataTransType)
									{
									case DMA_u8Peripheral2MEM:
										CLEARBIT(DMA -> CCR7 , 4);    //SET peripheral to memory mode
										break;
									case DMA_u8MEM2Peripheral:
										SETBIT(DMA -> CCR7 , 4);      //SET memory to  peripheral mode
										break;
									case DMA_u8MEM2MEM:
										SETBIT(DMA -> CCR7 , 14);     //SET memory to  memory mode
										break;
									default:
										Local_enuErrorState = ES_Out_Of_Range;break;
									}

									if(DMA_u8Enable == Copy_PstrDmaChannelConfig ->IncrementMode)
									{
										//set Increment Mode
										SETBIT(DMA -> CCR7 , 6);
										SETBIT(DMA -> CCR7 , 7);
									}
									else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->IncrementMode){}
									else
									{
										Local_enuErrorState = ES_Out_Of_Range;
									}
									if(DMA_u8Enable == Copy_PstrDmaChannelConfig ->EnableTCINT)
									{
										SETBIT(DMA -> CCR7 , 1);             //Enable Complete transfer INT

									}
									else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->EnableTCINT){}
									else
									{
										Local_enuErrorState = ES_Out_Of_Range;
									}
									if(DMA_u8Enable == Copy_PstrDmaChannelConfig -> EnableCircMod)
									{
										SETBIT(DMA -> CCR7 , 5);                      //Enable Circular mode
									}
									else if(DMA_u8Disable == Copy_PstrDmaChannelConfig ->EnableCircMod){}
									else
									{
										Local_enuErrorState = ES_Out_Of_Range;
									}
									break;
									default:
										Local_enuErrorState = ES_Out_Of_Range;
		}
	}
	else
	{
		Local_enuErrorState = ES_NULLPOINTER;
	}


	return Local_enuErrorState;
}

/*This function is used to transfer data by DMA from source to destination (by interrupt)*/
ES_t DMA_enuDmaAsyncChannelTrans(const DMA_ConfigStr_t* Copy_PstrDmaChannelConfig , u32 Copy_u32SrcAddress , u32 Copy_u32DesAddress , u16 Copy_u16NumOfTrans)
{
	ES_t Local_enuErrorState = ES_OK;
	if(DMA_u8Channel_1 <= Copy_PstrDmaChannelConfig -> ChannelNumber && DMA_u8Channel_7 >= Copy_PstrDmaChannelConfig -> ChannelNumber && 65535 >= Copy_u16NumOfTrans)
	{

		switch(Copy_PstrDmaChannelConfig -> ChannelNumber)
		{
		case DMA_u8Channel_1:
			CLEARBIT(DMA -> CCR1 , 0);                        // Disable Channel
			DMA -> CNDTR1 = Copy_u16NumOfTrans;				  // set number of transfer
			switch(Copy_PstrDmaChannelConfig ->DataTransType)
			{
			case DMA_u8Peripheral2MEM:
				DMA -> CPAR1 = Copy_u32SrcAddress;			  // set Peripheral address as a SrcAddress
				DMA -> CMAR1 = Copy_u32DesAddress;			  // set memory address as a DesAddress

				break;
			case DMA_u8MEM2Peripheral:
				DMA -> CMAR1 = Copy_u32SrcAddress;			  // set memory address as a SrcAddress
				DMA -> CPAR1 = Copy_u32DesAddress;			  // set Peripheral address as a DesAddress
				break;
			case DMA_u8MEM2MEM:
				DMA -> CPAR1 = Copy_u32SrcAddress;            // set Peripheral address as a SrcAddress
				DMA -> CMAR1 = Copy_u32DesAddress;            // set memory address as a DesAddress
				break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;break;
			}
			SETBIT(DMA -> CCR1 , 0);						  // Enable Channel
			break;
			case DMA_u8Channel_2:
				CLEARBIT(DMA -> CCR2 , 0);                            // Disable Channel
				DMA -> CNDTR2 = Copy_u16NumOfTrans;                   // set number of transfer
				switch(Copy_PstrDmaChannelConfig ->DataTransType)
				{
				case DMA_u8Peripheral2MEM:
					DMA -> CPAR2 = Copy_u32SrcAddress;                // set Peripheral address as a SrcAddress
					DMA -> CMAR2 = Copy_u32DesAddress;                // set memory address as a DesAddress

					break;
				case DMA_u8MEM2Peripheral:
					DMA -> CMAR2 = Copy_u32SrcAddress;                // set memory address as a SrcAddress
					DMA -> CPAR2 = Copy_u32DesAddress;                // set Peripheral address as a DesAddress
					break;
				case DMA_u8MEM2MEM:
					DMA -> CPAR2 = Copy_u32SrcAddress;                // set Peripheral address as a SrcAddress
					DMA -> CMAR2 = Copy_u32DesAddress;                // set memory address as a DesAddress
					break;
				default:
					Local_enuErrorState = ES_Out_Of_Range;break;
				}
				SETBIT(DMA -> CCR2 , 0);                              // Enable Channel
				break;
				case DMA_u8Channel_3:
					CLEARBIT(DMA -> CCR3 , 0);                           // Disable Channel
					DMA -> CNDTR3 = Copy_u16NumOfTrans;                  // set number of transfer
					switch(Copy_PstrDmaChannelConfig ->DataTransType)
					{
					case DMA_u8Peripheral2MEM:
						DMA -> CPAR3 = Copy_u32SrcAddress;               // set Peripheral address as a SrcAddress
						DMA -> CMAR3 = Copy_u32DesAddress;               // set memory address as a DesAddress

						break;
					case DMA_u8MEM2Peripheral:
						DMA -> CMAR3 = Copy_u32SrcAddress;               // set memory address as a SrcAddress
						DMA -> CPAR3 = Copy_u32DesAddress;               // set Peripheral address as a DesAddress
						break;
					case DMA_u8MEM2MEM:
						DMA -> CPAR3 = Copy_u32SrcAddress;               // set Peripheral address as a SrcAddress
						DMA -> CMAR3 = Copy_u32DesAddress;               // set memory address as a DesAddress
						break;
					default:
						Local_enuErrorState = ES_Out_Of_Range;break;
					}
					SETBIT(DMA -> CCR3 , 0);                             // Enable Channel
					break;
					case DMA_u8Channel_4:
						CLEARBIT(DMA -> CCR4 , 0);                             // Disable Channel
						DMA -> CNDTR4 = Copy_u16NumOfTrans;                    // set number of transfer
						switch(Copy_PstrDmaChannelConfig ->DataTransType)
						{
						case DMA_u8Peripheral2MEM:
							DMA -> CPAR4 = Copy_u32SrcAddress;                 // set Peripheral address as a SrcAddress
							DMA -> CMAR4 = Copy_u32DesAddress;                 // set memory address as a DesAddress

							break;
						case DMA_u8MEM2Peripheral:
							DMA -> CMAR4 = Copy_u32SrcAddress;                 // set memory address as a SrcAddress
							DMA -> CPAR4 = Copy_u32DesAddress;                 // set Peripheral address as a DesAddress
							break;
						case DMA_u8MEM2MEM:
							DMA -> CPAR4 = Copy_u32SrcAddress;                 // set Peripheral address as a SrcAddress
							DMA -> CMAR4 = Copy_u32DesAddress;                 // set memory address as a DesAddress
							break;
						default:
							Local_enuErrorState = ES_Out_Of_Range;break;
						}
						SETBIT(DMA -> CCR4 , 0);                               // Enable Channel
						break;
						case DMA_u8Channel_5:
							CLEARBIT(DMA -> CCR5 , 0);                           // Disable Channel
							DMA -> CNDTR5 = Copy_u16NumOfTrans;                  // set number of transfer
							switch(Copy_PstrDmaChannelConfig ->DataTransType)
							{
							case DMA_u8Peripheral2MEM:
								DMA -> CPAR5 = Copy_u32SrcAddress;               // set Peripheral address as a SrcAddress
								DMA -> CMAR5 = Copy_u32DesAddress;               // set memory address as a DesAddress

								break;
							case DMA_u8MEM2Peripheral:
								DMA -> CMAR5 = Copy_u32SrcAddress;               // set memory address as a SrcAddress
								DMA -> CPAR5 = Copy_u32DesAddress;               // set Peripheral address as a DesAddress
								break;
							case DMA_u8MEM2MEM:
								DMA -> CPAR5 = Copy_u32SrcAddress;               // set Peripheral address as a SrcAddress
								DMA -> CMAR5 = Copy_u32DesAddress;               // set memory address as a DesAddress
								break;
							default:
								Local_enuErrorState = ES_Out_Of_Range;break;
							}
							SETBIT(DMA -> CCR5 , 0);                             // Enable Channel
							break;
							case DMA_u8Channel_6:
								CLEARBIT(DMA -> CCR6 , 0);                          // Disable Channel
								DMA -> CNDTR6 = Copy_u16NumOfTrans;                 // set number of transfer
								switch(Copy_PstrDmaChannelConfig ->DataTransType)
								{
								case DMA_u8Peripheral2MEM:
									DMA -> CPAR6 = Copy_u32SrcAddress;              // set Peripheral address as a SrcAddress
									DMA -> CMAR6 = Copy_u32DesAddress;              // set memory address as a DesAddress

									break;
								case DMA_u8MEM2Peripheral:
									DMA -> CMAR6 = Copy_u32SrcAddress;              // set memory address as a SrcAddress
									DMA -> CPAR6 = Copy_u32DesAddress;              // set Peripheral address as a DesAddress
									break;
								case DMA_u8MEM2MEM:
									DMA -> CPAR6 = Copy_u32SrcAddress;              // set Peripheral address as a SrcAddress
									DMA -> CMAR6 = Copy_u32DesAddress;              // set memory address as a DesAddress
									break;
								default:
									Local_enuErrorState = ES_Out_Of_Range;break;
								}
								SETBIT(DMA -> CCR6 , 0);                            // Enable Channel
								break;
								case DMA_u8Channel_7:
									CLEARBIT(DMA -> CCR7 , 0);                           // Disable Channel
									DMA -> CNDTR7 = Copy_u16NumOfTrans;                  // set number of transfer
									switch(Copy_PstrDmaChannelConfig ->DataTransType)
									{
									case DMA_u8Peripheral2MEM:
										DMA -> CPAR7 = Copy_u32SrcAddress;               // set Peripheral address as a SrcAddress
										DMA -> CMAR7 = Copy_u32DesAddress;               // set memory address as a DesAddress

										break;
									case DMA_u8MEM2Peripheral:
										DMA -> CMAR7 = Copy_u32SrcAddress;               // set memory address as a SrcAddress
										DMA -> CPAR7 = Copy_u32DesAddress;               // set Peripheral address as a DesAddress
										break;
									case DMA_u8MEM2MEM:
										DMA -> CPAR7 = Copy_u32SrcAddress;               // set Peripheral address as a SrcAddress
										DMA -> CMAR7 = Copy_u32DesAddress;               // set memory address as a DesAddress
										break;
									default:
										Local_enuErrorState = ES_Out_Of_Range;break;
										SETBIT(DMA -> CCR7 , 0);
									}                                                    // Enable Channel
									break;
		}
	}
	else
	{
		Local_enuErrorState = ES_Out_Of_Range;
	}


	return Local_enuErrorState;
}

/*This function is used to transfer data by DMA from source to destination (by polling)*/
ES_t DMA_enuDmaSyncChannelTrans(const DMA_ConfigStr_t* Copy_PstrDmaChannelConfig , u32 Copy_u32SrcAddress , u32 Copy_u32DesAddress , u16 Copy_u16NumOfTrans)
{
	ES_t Local_enuErrorState = ES_OK;

	if(DMA_u8Channel_1 <= Copy_PstrDmaChannelConfig -> ChannelNumber && DMA_u8Channel_7 >= Copy_PstrDmaChannelConfig -> ChannelNumber && 65535 >= Copy_u16NumOfTrans)
	{

		switch(Copy_PstrDmaChannelConfig -> ChannelNumber)
		{
		case DMA_u8Channel_1:
			CLEARBIT(DMA -> CCR1 , 0);                                        // Disable Channel
			DMA -> CNDTR1 = Copy_u16NumOfTrans;                               // set number of transfer
			switch(Copy_PstrDmaChannelConfig ->DataTransType)
			{
			case DMA_u8Peripheral2MEM:
				DMA -> CPAR1 = Copy_u32SrcAddress;                            // set Peripheral address as a SrcAddress
				DMA -> CMAR1 = Copy_u32DesAddress;                            // set memory address as a DesAddress

				break;
			case DMA_u8MEM2Peripheral:
				DMA -> CMAR1 = Copy_u32SrcAddress;                            // set memory address as a SrcAddress
				DMA -> CPAR1 = Copy_u32DesAddress;                            // set Peripheral address as a DesAddress
				break;
			case DMA_u8MEM2MEM:
				DMA -> CPAR1 = Copy_u32SrcAddress;                            // set Peripheral address as a SrcAddress
				DMA -> CMAR1 = Copy_u32DesAddress;                            // set memory address as a DesAddress
				break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;break;
			}
			SETBIT(DMA -> CCR1 , 0);                                          // Enable Channel
			while(!(GETBIT(DMA -> ISR , 1))); // Polling for the transfer complete flag
			SETBIT(DMA -> IFCR , 1);		  // clear transfer complete flag
			break;
			case DMA_u8Channel_2:
				CLEARBIT(DMA -> CCR2 , 0);                                      // Disable Channel
				DMA -> CNDTR2 = Copy_u16NumOfTrans;                             // set number of transfer
				switch(Copy_PstrDmaChannelConfig ->DataTransType)
				{
				case DMA_u8Peripheral2MEM:
					DMA -> CPAR2 = Copy_u32SrcAddress;                          // set Peripheral address as a SrcAddress
					DMA -> CMAR2 = Copy_u32DesAddress;                          // set memory address as a DesAddress

					break;
				case DMA_u8MEM2Peripheral:
					DMA -> CMAR2 = Copy_u32SrcAddress;                          // set memory address as a SrcAddress
					DMA -> CPAR2 = Copy_u32DesAddress;                          // set Peripheral address as a DesAddress
					break;
				case DMA_u8MEM2MEM:
					DMA -> CPAR2 = Copy_u32SrcAddress;                          // set Peripheral address as a SrcAddress
					DMA -> CMAR2 = Copy_u32DesAddress;                          // set memory address as a DesAddress
					break;
				default:
					Local_enuErrorState = ES_Out_Of_Range;break;
				}
				SETBIT(DMA -> CCR2 , 0);                                        // Enable Channel
				while(!(GETBIT(DMA -> ISR , 5)));
				SETBIT(DMA -> IFCR , 5);
				break;
				case DMA_u8Channel_3:
					CLEARBIT(DMA -> CCR3 , 0);                                  // Disable Channel
					DMA -> CNDTR3 = Copy_u16NumOfTrans;                         // set number of transfer
					switch(Copy_PstrDmaChannelConfig ->DataTransType)
					{
					case DMA_u8Peripheral2MEM:
						DMA -> CPAR3 = Copy_u32SrcAddress;                      // set Peripheral address as a SrcAddress
						DMA -> CMAR3 = Copy_u32DesAddress;                      // set memory address as a DesAddress

						break;
					case DMA_u8MEM2Peripheral:
						DMA -> CMAR3 = Copy_u32SrcAddress;                      // set memory address as a SrcAddress
						DMA -> CPAR3 = Copy_u32DesAddress;                      // set Peripheral address as a DesAddress
						break;
					case DMA_u8MEM2MEM:
						DMA -> CPAR3 = Copy_u32SrcAddress;                      // set Peripheral address as a SrcAddress
						DMA -> CMAR3 = Copy_u32DesAddress;                      // set memory address as a DesAddress
						break;
					default:
						Local_enuErrorState = ES_Out_Of_Range;break;
					}
					SETBIT(DMA -> CCR3 , 0);                                    // Enable Channel
					while(!(GETBIT(DMA -> ISR , 9)));       // Polling for the transfer complete flag
					SETBIT(DMA -> IFCR , 9);                // clear transfer complete flag
					break;
					case DMA_u8Channel_4:
						CLEARBIT(DMA -> CCR4 , 0);                                 // Disable Channel
						DMA -> CNDTR4 = Copy_u16NumOfTrans;                        // set number of transfer
						switch(Copy_PstrDmaChannelConfig ->DataTransType)
						{
						case DMA_u8Peripheral2MEM:
							DMA -> CPAR4 = Copy_u32SrcAddress;                     // set Peripheral address as a SrcAddress
							DMA -> CMAR4 = Copy_u32DesAddress;                     // set memory address as a DesAddress

							break;
						case DMA_u8MEM2Peripheral:
							DMA -> CMAR4 = Copy_u32SrcAddress;                     // set memory address as a SrcAddress
							DMA -> CPAR4 = Copy_u32DesAddress;                     // set Peripheral address as a DesAddress
							break;
						case DMA_u8MEM2MEM:
							DMA -> CPAR4 = Copy_u32SrcAddress;                     // set Peripheral address as a SrcAddress
							DMA -> CMAR4 = Copy_u32DesAddress;                     // set memory address as a DesAddress
							break;
						default:
							Local_enuErrorState = ES_Out_Of_Range;break;
						}
						SETBIT(DMA -> CCR4 , 0);                                   // Enable Channel
						while(!(GETBIT(DMA -> ISR , 13)));   // Polling for the transfer complete flag
						SETBIT(DMA -> IFCR , 13);            // clear transfer complete flag
						break;
						case DMA_u8Channel_5:
							CLEARBIT(DMA -> CCR5 , 0);                              // Disable Channel
							DMA -> CNDTR5 = Copy_u16NumOfTrans;                     // set number of transfer
							switch(Copy_PstrDmaChannelConfig ->DataTransType)
							{
							case DMA_u8Peripheral2MEM:
								DMA -> CPAR5 = Copy_u32SrcAddress;                  // set Peripheral address as a SrcAddress
								DMA -> CMAR5 = Copy_u32DesAddress;                  // set memory address as a DesAddress

								break;
							case DMA_u8MEM2Peripheral:
								DMA -> CMAR5 = Copy_u32SrcAddress;                  // set memory address as a SrcAddress
								DMA -> CPAR5 = Copy_u32DesAddress;                  // set Peripheral address as a DesAddress
								break;
							case DMA_u8MEM2MEM:
								DMA -> CPAR5 = Copy_u32SrcAddress;                  // set Peripheral address as a SrcAddress
								DMA -> CMAR5 = Copy_u32DesAddress;                  // set memory address as a DesAddress
								break;
							default:
								Local_enuErrorState = ES_Out_Of_Range;break;
							}
							SETBIT(DMA -> CCR5 , 0);                                // Enable Channel
							while(!(GETBIT(DMA -> ISR , 17)));   // Polling for the transfer complete flag
							SETBIT(DMA -> IFCR , 17);            // clear transfer complete flag
							break;
							case DMA_u8Channel_6:
								CLEARBIT(DMA -> CCR6 , 0);                              // Disable Channel
								DMA -> CNDTR6 = Copy_u16NumOfTrans;                     // set number of transfer
								switch(Copy_PstrDmaChannelConfig ->DataTransType)
								{
								case DMA_u8Peripheral2MEM:
									DMA -> CPAR6 = Copy_u32SrcAddress;                  // set Peripheral address as a SrcAddress
									DMA -> CMAR6 = Copy_u32DesAddress;                  // set memory address as a DesAddress

									break;
								case DMA_u8MEM2Peripheral:
									DMA -> CMAR6 = Copy_u32SrcAddress;                  // set memory address as a SrcAddress
									DMA -> CPAR6 = Copy_u32DesAddress;                  // set Peripheral address as a DesAddress
									break;
								case DMA_u8MEM2MEM:
									DMA -> CPAR6 = Copy_u32SrcAddress;                  // set Peripheral address as a SrcAddress
									DMA -> CMAR6 = Copy_u32DesAddress;                  // set memory address as a DesAddress
									break;
								default:
									Local_enuErrorState = ES_Out_Of_Range;break;
								}
								SETBIT(DMA -> CCR6 , 0);                                // Enable Channel
								while(!(GETBIT(DMA -> ISR , 21)));   // Polling for the transfer complete flag
								SETBIT(DMA -> IFCR , 21);            // clear transfer complete flag
								break;
								case DMA_u8Channel_7:
									CLEARBIT(DMA -> CCR7 , 0);                              // Disable Channel
									DMA -> CNDTR7 = Copy_u16NumOfTrans;                     // set number of transfer
									switch(Copy_PstrDmaChannelConfig ->DataTransType)
									{
									case DMA_u8Peripheral2MEM:
										DMA -> CPAR7 = Copy_u32SrcAddress;                  // set Peripheral address as a SrcAddress
										DMA -> CMAR7 = Copy_u32DesAddress;                  // set memory address as a DesAddress

										break;
									case DMA_u8MEM2Peripheral:
										DMA -> CMAR7 = Copy_u32SrcAddress;                  // set memory address as a SrcAddress
										DMA -> CPAR7 = Copy_u32DesAddress;                  // set Peripheral address as a DesAddress
										break;
									case DMA_u8MEM2MEM:
										DMA -> CPAR7 = Copy_u32SrcAddress;                  // set Peripheral address as a SrcAddress
										DMA -> CMAR7 = Copy_u32DesAddress;                  // set memory address as a DesAddress
										break;
									default:
										Local_enuErrorState = ES_Out_Of_Range;break;
									}
									SETBIT(DMA -> CCR7 , 0);                                // Enable Channel
									while(!(GETBIT(DMA -> ISR , 25)));   // Polling for the transfer complete flag
									SETBIT(DMA -> IFCR , 25);            // clear transfer complete flag
									break;
		}
	}
	else
	{
		Local_enuErrorState = ES_Out_Of_Range;
	}



	return Local_enuErrorState;
}

/*This function is used to set ISR functions*/
ES_t DMA_enuCallBack(const DMA_ConfigStr_t* Copy_PstrDmaChannelConfig , void (*DMA_vidPtr2Fun)(void) )
{
	ES_t Local_enuErrorState = ES_OK;

	if(DMA_vidPtr2Fun)
	{
		if(DMA_u8Channel_1 <= Copy_PstrDmaChannelConfig -> ChannelNumber && DMA_u8Channel_7 >= Copy_PstrDmaChannelConfig -> ChannelNumber)
		{
			DMA_AVidPtr2Fun[Copy_PstrDmaChannelConfig -> ChannelNumber - ONE] = DMA_vidPtr2Fun;
		}
		else
		{
			Local_enuErrorState = ES_Out_Of_Range;
		}
	}
	else
	{
		Local_enuErrorState = ES_NULLPOINTER;
	}

	return Local_enuErrorState;
}




void DMA1_Channel1_IRQHandler(void)
{
	SETBIT(DMA -> IFCR , 1);// clear transfer complete flag
	if(DMA_AVidPtr2Fun[DMA_u8Channel_1 - ONE])
	{
		DMA_AVidPtr2Fun[DMA_u8Channel_1 - ONE]();
	}

}
void DMA1_Channel2_IRQHandler(void)
{
	SETBIT(DMA -> IFCR , 5);// clear transfer complete flag
		if(DMA_AVidPtr2Fun[DMA_u8Channel_2 - ONE])
		{
			DMA_AVidPtr2Fun[DMA_u8Channel_2 - ONE]();
		}
}
void DMA1_Channel3_IRQHandler(void)
{
	SETBIT(DMA -> IFCR , 9);// clear transfer complete flag
		if(DMA_AVidPtr2Fun[DMA_u8Channel_3 - ONE])
		{
			DMA_AVidPtr2Fun[DMA_u8Channel_3 - ONE]();
		}
}
void DMA1_Channel4_IRQHandler(void)
{
	SETBIT(DMA -> IFCR , 13);// clear transfer complete flag
		if(DMA_AVidPtr2Fun[DMA_u8Channel_4 - ONE])
		{
			DMA_AVidPtr2Fun[DMA_u8Channel_4 - ONE]();
		}
}
void DMA1_Channel5_IRQHandler(void)
{
	SETBIT(DMA -> IFCR , 17);// clear transfer complete flag
		if(DMA_AVidPtr2Fun[DMA_u8Channel_5 - ONE])
		{
			DMA_AVidPtr2Fun[DMA_u8Channel_5 - ONE]();
		}
}
void DMA1_Channel6_IRQHandler(void)
{
	SETBIT(DMA -> IFCR , 21);// clear transfer complete flag
		if(DMA_AVidPtr2Fun[DMA_u8Channel_6 - ONE])
		{
			DMA_AVidPtr2Fun[DMA_u8Channel_6 - ONE]();
		}
}
void DMA1_Channel7_IRQHandler(void)
{
	SETBIT(DMA -> IFCR , 25); // clear transfer complete flag
		if(DMA_AVidPtr2Fun[DMA_u8Channel_7 - ONE])
		{
			DMA_AVidPtr2Fun[DMA_u8Channel_7 - ONE]();
		}
}
