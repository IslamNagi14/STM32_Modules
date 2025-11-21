/**************************************************************/
/********************Name    : Islam Nagi	*******************/
/********************Date    : 22/8/2025    *******************/
/********************Version    : 1.0       *******************/
/********************SWC    : Timer(1 & 8)   ******************/
/**************************************************************/

#include"LIB/StdTypes.h"
#include"LIB/errorStatuse.h"
#include"LIB/stm32f103xx.h"
#include"LIB/BitMath.h"

#include"TIM18/TIM18_Interface.h"
#include"TIM18/TIM18_Config.h"
#include"TIM18/TIM18_Private.h"

static volatile void (*TIM1_GAofPtrTOFun[5])(void) = {NULL,NULL,NULL,NULL,NULL};
static volatile void (*TIM8_GAofPtrTOFun[5])(void) = {NULL,NULL,NULL,NULL,NULL};

/****************** Basic Delay ******************/


ES_t TIM_enuDelaySync_ms(TIM_Id_t Copy_enuTimID, u32 Copy_u32Delay_ms)
{
	ES_t Local_enuErrorState = ES_OK;

	if(Copy_u32Delay_ms == 0) return ES_OK;

	volatile TIM18_REGDef_t* TIMx;

	switch(Copy_enuTimID)
	{
	case TIM1_ID: TIMx = TIM1; break;
	case TIM8_ID: TIMx = TIM8; break;
	default: return ES_Out_Of_Range;
	}

	// Calculate optimal prescaler and auto-reload values
	u32 timer_clock = F_APB2;  // Assuming 8MHz
	u32 prescaler = 7999;      // 8MHz / 7200 = 10kHz
	u32 arr_value = (Copy_u32Delay_ms * 10) - 1; // 10kHz -> 0.1ms ticks

	if(arr_value > 0xFFFF)
	{
		// Need to adjust prescaler for longer delays
		prescaler = 7999;     // 8MHz / 8000 = 1kHz
		arr_value = Copy_u32Delay_ms - 1;

		if(arr_value > 0xFFFF)
			return ES_Out_Of_Range;
	}

	// Configure timer
	TIMx->PSC = prescaler;
	TIMx->ARR = arr_value;
	TIMx->CNT = 0;
	TIMx->SR = 0;  // Clear all flags
	TIMx->EGR = 1; // Generate update to load prescaler

	// Start timer
	SETBIT(TIMx->CR1, 0);

	// Wait for update flag with timeout
	u32 timeout = 1000000; // Reasonable timeout
	while(!GETBIT(TIMx->SR, 0) && timeout--);

	if(timeout == 0)
		Local_enuErrorState = ES_NOK;

	// Stop and clean up
	CLEARBIT(TIMx->CR1, 0);
	CLEARBIT(TIMx->SR, 0);

	return Local_enuErrorState;
}


//ES_t TIM_enuDelaySync_ms(TIM_Id_t Copy_enuTimID, u32 Copy_u32Delay_ms)
//{
//	ES_t Local_enuErrorState = ES_OK;
//
//	//  timer tick period in microseconds
//	/*f32 timer_tick_period_ms;*/f64 timer_tick_period_ms;
//	//  time for one full cycle (ARR+1 ticks)
//	f32 full_cycle_time_ms;
//	//  number of full cycles needed
//	f32 Local_f32Cycles;
//
//	u16 full_cycles ;
//	f32 remainder ;
//	u16 remaining_ticks;
//
//	switch(Copy_enuTimID)
//	{
//	case TIM1_ID:
//		// Initialize timer for delay (1ms per tick example)
//		TIM1->PSC = 7199;  // 8MHz/7200 = 1.111kHz
//		TIM1->ARR = 999;   // 1ms period
//		TIM1->RCR = 0;     // No repetition
//		TIM1->CNT = 0;
//		// Calculate timer tick period in microseconds
//		timer_tick_period_ms = (1000UL * (TIM1->PSC + 1)) / F_APB2;
//		// Calculate time for one full cycle (ARR+1 ticks)
//		full_cycle_time_ms = (TIM1->ARR + 1) * timer_tick_period_ms;
//		// Calculate number of full cycles needed
//		Local_f32Cycles = (Copy_u32Delay_ms /** 1000UL*/) / full_cycle_time_ms;
//		if(Local_f32Cycles == (u8)Local_f32Cycles)
//		{
//			TIM1->RCR = 0;
//		}
//		else
//		{
//			if(Local_f32Cycles > 255)
//				break;
//			full_cycles = (u16)Local_f32Cycles;
//			remainder = Local_f32Cycles - full_cycles;
//			remaining_ticks = (u16)(remainder * (TIM1->ARR + 1));
//
//			if(full_cycles > 0) // RCR counts repetitions, so N-1 for N cycles
//			{
//				TIM1->RCR = full_cycles - 1;
//			}
//          else
//          {
//				TIM1->RCR = 0;
//				TIM1->CNT = TIM1->ARR - remaining_ticks;
//			}
//
//		}
//		SETBIT(TIM1->CR1,0);// enable counter
//		while(!GETBIT(TIM1->SR,0));// wait for UIF flag
//		CLEARBIT(TIM1->SR,0);// clear UIF flag
//		CLEARBIT(TIM1->CR1,0);// disable counter
//		break;
//	case TIM8_ID:
//
//		// Initialize timer for delay (1ms per tick example)
//		TIM8->PSC = 7199;  // 8MHz/7200 = 1.111kHz
//		TIM8->ARR = 999;   // 1ms period
//		TIM8->RCR = 0;     // No repetition
//		TIM8->CNT = 0;
//		// Calculate timer tick period in microseconds
//		timer_tick_period_ms = (1000UL * (TIM8->PSC + 1)) / F_APB2;
//		// Calculate time for one full cycle (ARR+1 ticks)
//		full_cycle_time_ms = (TIM8->ARR + 1) * timer_tick_period_ms;
//		// Calculate number of full cycles needed
//		Local_f32Cycles = (Copy_u32Delay_ms /** 1000UL*/) / full_cycle_time_ms;
//		if(Local_f32Cycles == (u8)Local_f32Cycles)
//		{
//			TIM8->RCR = 0;
//		}
//		else
//		{
//			if(Local_f32Cycles > 255)
//				break;
//			full_cycles = (u16)Local_f32Cycles;
//			remainder = Local_f32Cycles - full_cycles;
//			remaining_ticks = (u16)(remainder * (TIM8->ARR + 1));
//
//			if(full_cycles > 0) // RCR counts repetitions, so N-1 for N cycles
//			{
//				TIM8->RCR = full_cycles - 1;
//			}
//          else
//          {
//				TIM8->RCR = 0;
//				TIM8->CNT = TIM8->ARR - remaining_ticks;
//			}
//
//		}
//		SETBIT(TIM8->CR1,0);// enable counter
//		while(!GETBIT(TIM8->SR,0));// wait for UIF flag
//		CLEARBIT(TIM8->SR,0);// clear UIF flag
//		CLEARBIT(TIM8->CR1,0);// disable counter
//		break;
//	default:
//		Local_enuErrorState = ES_Out_Of_Range;
//	}
//
//	return Local_enuErrorState;
//}


ES_t TIM_enuDelayAsync_ms(TIM_Id_t Copy_enuTimID, u32 Copy_u32Delay_ms)
{
	ES_t Local_enuErrorState = ES_OK;
	/*
	 * when you go to ISR disable counter and clear UIF then call your function
	 *
	 * */
	//  timer tick period in microseconds
	f32 timer_tick_period_ms;
	//  time for one full cycle (ARR+1 ticks)
	f32 full_cycle_time_ms;
	//  number of full cycles needed
	f32 Local_f32Cycles;

	u16 full_cycles ;
	f32 remainder ;
	u16 remaining_ticks;







	switch(Copy_enuTimID)
	{
	case TIM1_ID:

		// Initialize timer for delay (1ms per tick example)
		TIM1->PSC = 7199;  // 8MHz/7200 = 1.111kHz
		TIM1->ARR = 999;   // 1ms period
		TIM1->RCR = 0;     // No repetition
		TIM1->CNT = 0;
		// Calculate timer tick period in microseconds
		timer_tick_period_ms = (1000UL * (TIM1->PSC + 1)) / F_APB2;
		// Calculate time for one full cycle (ARR+1 ticks)
		full_cycle_time_ms = (TIM1->ARR + 1) * timer_tick_period_ms;
		// Calculate number of full cycles needed
		Local_f32Cycles = (Copy_u32Delay_ms /** 1000UL*/) / full_cycle_time_ms;
		if(Local_f32Cycles == (u8)Local_f32Cycles)
		{
			TIM1->RCR = 0;
		}
		else
		{
			if(Local_f32Cycles > 255)
				break;
			full_cycles = (u16)Local_f32Cycles;
			remainder = Local_f32Cycles - full_cycles;
			remaining_ticks = (u16)(remainder * (TIM1->ARR + 1));

			TIM1->RCR = full_cycles - 1;  // RCR counts repetitions, so N-1 for N cycles
			TIM1->CNT = TIM1->ARR - remaining_ticks;
		}
		SETBIT(TIM1->CR1,0);// enable counter
		SETBIT(TIM1->DIER, 0);  // Enable Update interrupt for TIM1
		break;
	case TIM8_ID:

		// Initialize timer for delay (1ms per tick example)
		TIM8->PSC = 7199;  // 8MHz/7200 = 1.111kHz
		TIM8->ARR = 999;   // 1ms period
		TIM8->RCR = 0;     // No repetition
		TIM8->CNT = 0;
		// Calculate timer tick period in microseconds
		timer_tick_period_ms = (1000UL * (TIM8->PSC + 1)) / F_APB2;
		// Calculate time for one full cycle (ARR+1 ticks)
		full_cycle_time_ms = (TIM8->ARR + 1) * timer_tick_period_ms;
		// Calculate number of full cycles needed
		Local_f32Cycles = (Copy_u32Delay_ms /** 1000UL*/) / full_cycle_time_ms;
		if(Local_f32Cycles == (u8)Local_f32Cycles)
		{
			TIM8->RCR = 0;
		}
		else
		{
			if(Local_f32Cycles > 255)
				break;
			full_cycles = (u16)Local_f32Cycles;
			remainder = Local_f32Cycles - full_cycles;
			remaining_ticks = (u16)(remainder * (TIM8->ARR + 1));

			TIM8->RCR = full_cycles - 1;  // RCR counts repetitions, so N-1 for N cycles
			TIM8->CNT = TIM8->ARR - remaining_ticks;
		}
		SETBIT(TIM8->CR1,0);// enable counter
		SETBIT(TIM8->DIER, 0);  // Enable Update interrupt for TIM8
		break;
	default:
		Local_enuErrorState = ES_Out_Of_Range;
	}

	return Local_enuErrorState;
}



/****************** CTC Mode ******************/
ES_t TIM_enuEnableCTCAsynch(TIM_Id_t Copy_enuTimID, TIM_Channel_t Copy_enuChannel, u16 Copy_u16CompareValue)
{
	ES_t Local_enuErrorState = ES_OK;
	/*
	 * when you go to ISR disable counter and clear CCxIF then call your function
	 *
	 * */
	switch(Copy_enuTimID)
	{
	case TIM1_ID:

		switch(Copy_enuChannel)
		{
		case TIM_CHANNEL_1:
			CLEARBIT(TIM1->SR,1);// clear CCxIF
			TIM1->CCR1 = Copy_u16CompareValue;
			SETBIT(TIM1->DIER,1);// enable Capture/Compare 1 interrupt
			break;
		case TIM_CHANNEL_2:
			CLEARBIT(TIM1->SR,2);// clear CCxIF
			TIM1->CCR2 = Copy_u16CompareValue;
			SETBIT(TIM1->DIER,2);// enable Capture/Compare 2 interrupt
			break;
		case TIM_CHANNEL_3:
			CLEARBIT(TIM1->SR,3);// clear CCxIF
			TIM1->CCR3 = Copy_u16CompareValue;
			SETBIT(TIM1->DIER,3);// enable Capture/Compare 3 interrupt
			break;
		case TIM_CHANNEL_4:
			CLEARBIT(TIM1->SR,4);// clear CCxIF
			TIM1->CCR4 = Copy_u16CompareValue;
			SETBIT(TIM1->DIER,4);// enable Capture/Compare 4 interrupt
			break;
		default:
			Local_enuErrorState = ES_Out_Of_Range;
		}
		SETBIT(TIM1->CR1,0);// enable counter for timer 1
		break;
		case TIM8_ID:

			switch(Copy_enuChannel)
			{
			case TIM_CHANNEL_1:
				CLEARBIT(TIM8->SR,1);// clear CCxIF
				TIM8->CCR1 = Copy_u16CompareValue;
				SETBIT(TIM8->DIER,1);// enable Capture/Compare 1 interrupt
				break;
			case TIM_CHANNEL_2:
				CLEARBIT(TIM8->SR,2);// clear CCxIF
				TIM8->CCR2 = Copy_u16CompareValue;
				SETBIT(TIM8->DIER,2);// enable Capture/Compare 2 interrupt
				break;
			case TIM_CHANNEL_3:
				CLEARBIT(TIM8->SR,3);// clear CCxIF
				TIM8->CCR3 = Copy_u16CompareValue;
				SETBIT(TIM8->DIER,3);// enable Capture/Compare 3 interrupt
				break;
			case TIM_CHANNEL_4:
				CLEARBIT(TIM8->SR,4);// clear CCxIF
				TIM8->CCR4 = Copy_u16CompareValue;
				SETBIT(TIM8->DIER,4);// enable Capture/Compare 4 interrupt
				break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;
			}
			SETBIT(TIM8->CR1,0);// enable counter for timer 8
			break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;
	}

	return Local_enuErrorState;
}
ES_t TIM_enuDisableCTC(TIM_Id_t Copy_enuTimID, TIM_Channel_t Copy_enuChannel)
{
	ES_t Local_enuErrorState = ES_OK;
	/*
	 * when you go to ISR disable counter and clear CCxIF then call your function
	 *
	 * */
	switch(Copy_enuTimID)
	{
	case TIM1_ID:
		CLEARBIT(TIM1->CR1,0);// disable counter for timer 1
		switch(Copy_enuChannel)
		{
		case TIM_CHANNEL_1:

			CLEARBIT(TIM1->DIER,1);// disable Capture/Compare 1 interrupt
			break;
		case TIM_CHANNEL_2:

			CLEARBIT(TIM1->DIER,2);// disable Capture/Compare 2 interrupt
			break;
		case TIM_CHANNEL_3:

			CLEARBIT(TIM1->DIER,3);// disable Capture/Compare 3 interrupt
			break;
		case TIM_CHANNEL_4:

			CLEARBIT(TIM1->DIER,4);// disable Capture/Compare 4 interrupt
			break;
		default:
			Local_enuErrorState = ES_Out_Of_Range;
		}
		break;
		case TIM8_ID:
			CLEARBIT(TIM8->CR1,0);// disable counter for timer 8
			switch(Copy_enuChannel)
			{
			case TIM_CHANNEL_1:

				CLEARBIT(TIM8->DIER,1);// disable Capture/Compare 1 interrupt
				break;
			case TIM_CHANNEL_2:

				CLEARBIT(TIM8->DIER,2);// disable Capture/Compare 2 interrupt
				break;
			case TIM_CHANNEL_3:

				CLEARBIT(TIM8->DIER,3);// disable Capture/Compare 3 interrupt
				break;
			case TIM_CHANNEL_4:

				CLEARBIT(TIM8->DIER,4);// disable Capture/Compare 4 interrupt
				break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;
			}
			break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;
	}

	return Local_enuErrorState;
}


/****************** PWM Generation ******************/
ES_t TIM_enuPWM_Init(TIM_Id_t Copy_enuTimID, TIM_Channel_t Copy_enuChannel, u32 freq_hz, TIM_PWM_Alignment_t alignment_mode)
{
	ES_t Local_enuErrorState = ES_OK;
	u32 timer_clock;

	switch(Copy_enuTimID)
	{
	case TIM1_ID:
		TIM1->PSC = 4;// set prescaler in PSC
		SETBIT(TIM1->BDTR,15);// enable main output
		SETBIT(TIM1->CR1, 7); // reload after update event
		switch(alignment_mode)
		{
		case TIM_PWM_EDGE_ALIGNED:
			TIM1->CR1 &= ~(0x3<<5);// select Edge-aligned mode

			timer_clock = F_APB2 / (TIM1->PSC + 1);
			TIM1->ARR = (timer_clock / freq_hz) - 1;
			break;
		case TIM_PWM_CENTER_ALIGNED:
			TIM1->CR1 |= (0x3<<5);// select Center-aligned mode3
			timer_clock = F_APB2 / (TIM1->PSC + 1);
			TIM1->ARR = (timer_clock /(2 * freq_hz)) - 1;			break;
		default:
			Local_enuErrorState = ES_Out_Of_Range;
		}
		switch(Copy_enuChannel)
		{
		case TIM_CHANNEL_1:
			TIM1->CCMR1 &= ~(0x7<<4);// mask OCxM
			TIM1->CCMR1 |= (0x6<<4);// set PWMMODE1
			SETBIT(TIM1->CCMR1,3);// enable preload to change CCRx after update event
			SETBIT(TIM1->CCER,0);// enable CH1
			break;
		case TIM_CHANNEL_2:
			TIM1->CCMR1 &= ~(0x7<<12);// mask OCxM
			TIM1->CCMR1 |= (0x6<<12);// set PWMMODE1
			SETBIT(TIM1->CCMR1,11);// enable preload to change CCRx after update event
			SETBIT(TIM1->CCER,4);// enable CH2
			break;
		case TIM_CHANNEL_3:
			TIM1->CCMR2 &= ~(0x7<<4);// mask OCxM
			TIM1->CCMR2 |= (0x6<<4);// set PWMMODE1
			SETBIT(TIM1->CCMR2,3);// enable preload to change CCRx after update event
			SETBIT(TIM1->CCER,8);// enable CH3
			break;
		case TIM_CHANNEL_4:
			TIM1->CCMR2 &= ~(0x7<<12);// mask OCxM
			TIM1->CCMR2 |= (0x6<<12);// set PWMMODE1
			SETBIT(TIM1->CCMR2,11);// enable preload to change CCRx after update event
			SETBIT(TIM1->CCER,12);// enable CH4
			break;
		default:
			Local_enuErrorState = ES_Out_Of_Range;
		}
		break;
		case TIM8_ID:
			TIM8->PSC = 4;// set prescaler in PSC
			SETBIT(TIM8->BDTR,15);// enable main output
			SETBIT(TIM8->CR1, 7); //reload after update event
			switch(alignment_mode)
			{
			case TIM_PWM_EDGE_ALIGNED:
				TIM8->CR1 &= ~(0x3<<5);// select Edge-aligned mode
				timer_clock = F_APB2 / (TIM8->PSC + 1);
				TIM8->ARR = (timer_clock / freq_hz) - 1;
				break;
			case TIM_PWM_CENTER_ALIGNED:
				TIM8->CR1 |= (0x3<<5);// select Center-aligned mode3
				timer_clock = F_APB2 / (TIM1->PSC + 1);
				TIM8->ARR = (timer_clock /(2 * freq_hz)) - 1;
				break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;
			}
			switch(Copy_enuChannel)
			{
			case TIM_CHANNEL_1:
				TIM8->CCMR1 &= ~(0x7<<4);// mask OCxM
				TIM8->CCMR1 |= (0x6<<4);// set PWMMODE1
				SETBIT(TIM8->CCMR1,3);// enable preload to change CCRx after update event
				SETBIT(TIM8->CCER,0);// enable CH1
				break;
			case TIM_CHANNEL_2:
				TIM8->CCMR1 &= ~(0x7<<12);// mask OCxM
				TIM8->CCMR1 |= (0x6<<12);// set PWMMODE1
				SETBIT(TIM8->CCMR1,11);// enable preload to change CCRx after update event
				SETBIT(TIM8->CCER,4);// enable CH2
				break;
			case TIM_CHANNEL_3:
				TIM8->CCMR2 &= ~(0x7<<4);// mask OCxM
				TIM8->CCMR2 |= (0x6<<4);// set PWMMODE1
				SETBIT(TIM8->CCMR2,3);// enable preload to change CCRx after update event
				SETBIT(TIM8->CCER,8);// enable CH3
				break;
			case TIM_CHANNEL_4:
				TIM8->CCMR2 &= ~(0x7<<12);// mask OCxM
				TIM8->CCMR2 |= (0x6<<12);// set PWMMODE1
				SETBIT(TIM8->CCMR2,11);// enable preload to change CCRx after update event
				SETBIT(TIM8->CCER,12);// enable CH4
				break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;
			}
			break;
			default:

				break;
	}

	return Local_enuErrorState;
}
ES_t TIM_enuPWM_SetDuty(TIM_Id_t Copy_enuTimID, TIM_Channel_t Copy_enuChannel, f32 Copy_f32Duty_percent)
{
	ES_t Local_enuErrorState = ES_OK;
	if(Copy_f32Duty_percent < 0.0f)
		Copy_f32Duty_percent = 0.0f;
	else if (Copy_f32Duty_percent > 100.0f)
		Copy_f32Duty_percent = 100.0f;

	u16 max_value;
	u16 ccr_value ;

	switch(Copy_enuTimID)
	{
	case TIM1_ID:
		max_value = TIM1->ARR;
		ccr_value = (u16)((max_value + 1) * (Copy_f32Duty_percent / 100.0));
		switch(Copy_enuChannel)
		{
		case TIM_CHANNEL_1:

			TIM1->CCR1 = (ccr_value > max_value) ? max_value : ccr_value;
			break;
		case TIM_CHANNEL_2:

			TIM1->CCR2 = (ccr_value > max_value) ? max_value : ccr_value;
			break;
		case TIM_CHANNEL_3:

			TIM1->CCR3 = (ccr_value > max_value) ? max_value : ccr_value;
			break;
		case TIM_CHANNEL_4:

			TIM1->CCR4 = (ccr_value > max_value) ? max_value : ccr_value;
			break;
		default:
			Local_enuErrorState = ES_Out_Of_Range;
		}
		break;
		case TIM8_ID:
			max_value = TIM8->ARR;
			ccr_value = (u16)((max_value + 1) * (Copy_f32Duty_percent / 100.0));
			switch(Copy_enuChannel)
			{
			case TIM_CHANNEL_1:
				TIM8->CCR1 = (ccr_value > max_value) ? max_value : ccr_value;

				break;
			case TIM_CHANNEL_2:
				TIM8->CCR2 = (ccr_value > max_value) ? max_value : ccr_value;
				break;
			case TIM_CHANNEL_3:
				TIM8->CCR3 = (ccr_value > max_value) ? max_value : ccr_value;
				break;
			case TIM_CHANNEL_4:
				TIM8->CCR4 = (ccr_value > max_value) ? max_value : ccr_value;
				break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;
			}
			break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;
	}

	return Local_enuErrorState;
}
ES_t TIM_enuPWM_Start(TIM_Id_t Copy_enuTimID, TIM_Channel_t Copy_enuChannel)
{
	ES_t Local_enuErrorState = ES_OK;
	switch(Copy_enuTimID)
	{
	case TIM1_ID:
		SETBIT(TIM1->CR1,0);  // Enable counter of timer 1
		SETBIT(TIM1->BDTR,15); // Main output enable for advanced timers

		break;
	case TIM8_ID:
		SETBIT(TIM8->CR1,0);  // Enable counter of timer 8
		SETBIT(TIM8->BDTR,15); // Main output enable for advanced timers

		break;
	default:
		Local_enuErrorState = ES_Out_Of_Range;
		break;
	}
	return Local_enuErrorState;
}
ES_t TIM_enuPWM_Stop(TIM_Id_t Copy_enuTimID, TIM_Channel_t Copy_enuChannel)
{
	ES_t Local_enuErrorState = ES_OK;
	switch(Copy_enuTimID)
	{
	case TIM1_ID:
		CLEARBIT(TIM1->CR1,0);// disable counter for timer 1
		switch(Copy_enuChannel)
		{
		case TIM_CHANNEL_1:
			CLEARBIT(TIM1->CCER,0);// disable CH1
			break;
		case TIM_CHANNEL_2:

			CLEARBIT(TIM1->CCER,4);// disable CH2
			break;
		case TIM_CHANNEL_3:

			CLEARBIT(TIM1->CCER,8);// disable CH3
			break;
		case TIM_CHANNEL_4:

			CLEARBIT(TIM1->CCER,12);// disable CH4
			break;
		default:
			Local_enuErrorState = ES_Out_Of_Range;
		}
		break;
		case TIM8_ID:
			CLEARBIT(TIM8->CR1,0);// disable counter for timer 8
			switch(Copy_enuChannel)
			{
			case TIM_CHANNEL_1:
				CLEARBIT(TIM8->CCER,0);// disable CH1
				break;
			case TIM_CHANNEL_2:

				CLEARBIT(TIM8->CCER,4);// disable CH2
				break;
			case TIM_CHANNEL_3:

				CLEARBIT(TIM8->CCER,8);// disable CH3
				break;
			case TIM_CHANNEL_4:

				CLEARBIT(TIM8->CCER,12);// disable CH4
				break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;
			}
			break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;
				break;
	}
	return Local_enuErrorState;
}

/****************** Input Capture ******************/
ES_t TIM_enuIC_Init(TIM_Id_t Copy_enuTimID, TIM_Channel_t Copy_enuChannel, TIM_IC_Edge_t Copy_enuEdge, u8 Copy_u8Prescaler)
{
	ES_t Local_enuErrorState = ES_OK;

	switch(Copy_enuTimID)
	{
	case TIM1_ID:
		switch(Copy_enuChannel)
		{
		case TIM_CHANNEL_1:
			TIM1->CCMR1 &= ~(0x3 << 0);// Mask CCxS bits
			TIM1->CCMR1 |= (0x1 << 0);// CC1 channel is configured as input, IC1 is mapped on TI1
			TIM1->CCMR1 &= ~(0x3 << 2);// mask ICxPSC
			TIM1->CCMR1 |= ((Copy_u8Prescaler & 0x3)<< 2);// set prescaler

			switch(Copy_enuEdge)
			{
			case TIM_IC_RISING_EDGE:
				CLEARBIT(TIM1->CCER,1);//clear CCxP
				CLEARBIT(TIM1->CCER,3);//clear CCxNP
				break;
			case TIM_IC_FALLING_EDGE:
				SETBIT(TIM1->CCER,1);//set CCxP
				CLEARBIT(TIM1->CCER,3);//clear CCxNP
				break;
			case TIM_IC_BOTH_EDGES:
				SETBIT(TIM1->CCER,1);//set CCxP
				SETBIT(TIM1->CCER,3);//set CCxNP
				break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;
				break;

			}
			SETBIT(TIM1->CCER,0);//Capture/Compare Enable Register
			break;
			case TIM_CHANNEL_2:
				TIM1->CCMR1 &= ~(0x3 << 8);// Mask CCxS bits
				TIM1->CCMR1 |= (0x1 << 8);// CC2 channel is configured as input, IC2 is mapped on TI2
				TIM1->CCMR1 &= ~(0x3 << 12);// mask ICxPSC
				TIM1->CCMR1 |= ((Copy_u8Prescaler & 0x3)<< 12);// set prescaler
				switch(Copy_enuEdge)
				{
				case TIM_IC_RISING_EDGE:
					CLEARBIT(TIM1->CCER,5);//clear CCxP
					CLEARBIT(TIM1->CCER,7);//clear CCxNP
					break;
				case TIM_IC_FALLING_EDGE:
					SETBIT(TIM1->CCER,5);//set CCxP
					CLEARBIT(TIM1->CCER,7);//clear CCxNP
					break;
				case TIM_IC_BOTH_EDGES:
					SETBIT(TIM1->CCER,5);//set CCxP
					SETBIT(TIM1->CCER,7);//set CCxNP
					break;
				default:
					Local_enuErrorState = ES_Out_Of_Range;
					break;

				}
				SETBIT(TIM1->CCER,4);//Capture/Compare Enable Register
				break;
				case TIM_CHANNEL_3:
					TIM1->CCMR2 &= ~(0x3 << 0);// Mask CCxS bits
					TIM1->CCMR2 |= (0x1 << 0);// CC3 channel is configured as input, IC3 is mapped on TI3
					TIM1->CCMR2 &= ~(0x3 << 2);// mask ICxPSC
					TIM1->CCMR2 |= ((Copy_u8Prescaler & 0x3)<< 2);// set prescaler
					switch(Copy_enuEdge)
					{
					case TIM_IC_RISING_EDGE:
						CLEARBIT(TIM1->CCER,9);//clear CCxP
						CLEARBIT(TIM1->CCER,11);//clear CCxNP
						break;
					case TIM_IC_FALLING_EDGE:
						SETBIT(TIM1->CCER,9);//set CCxP
						CLEARBIT(TIM1->CCER,11);//clear CCxNP
						break;
					case TIM_IC_BOTH_EDGES:
						SETBIT(TIM1->CCER,9);//set CCxP
						SETBIT(TIM1->CCER,11);//set CCxNP
						break;
					default:
						Local_enuErrorState = ES_Out_Of_Range;
						break;

					}
					SETBIT(TIM1->CCER,8);//Capture/Compare Enable Register
					break;
					case TIM_CHANNEL_4:
						TIM1->CCMR2 &= ~(0x3 << 8);// Mask CCxS bits
						TIM1->CCMR2 |= (0x1 << 8);//CC4 channel is configured as input, IC4 is mapped on TI4
						TIM1->CCMR2 &= ~(0x3 << 10);// mask ICxPSC
						TIM1->CCMR2 |= ((Copy_u8Prescaler & 0x3)<< 10);// set prescaler
						switch(Copy_enuEdge)
						{
						case TIM_IC_RISING_EDGE:
							CLEARBIT(TIM1->CCER,13);//clear CCxP

							break;
						case TIM_IC_FALLING_EDGE:
							SETBIT(TIM1->CCER,13);//set CCxP

							break;
						case TIM_IC_BOTH_EDGES:
							Local_enuErrorState = ES_NOK;// CH 4 does NOT provid this mode
							break;
						default:
							Local_enuErrorState = ES_Out_Of_Range;
							break;

						}
						SETBIT(TIM1->CCER,12);//Capture/Compare Enable Register
						break;
						default:
							Local_enuErrorState = ES_Out_Of_Range;
							break;
		}

		break;
		case TIM8_ID:

			switch(Copy_enuChannel)
			{
			case TIM_CHANNEL_1:
				TIM8->CCMR1 &= ~(0x3 << 0);// Mask CCxS bits
				TIM8->CCMR1 |= (0x1 << 0);// CC1 channel is configured as input, IC1 is mapped on TI1
				TIM8->CCMR1 &= ~(0x3 << 2);// mask ICxPSC
				TIM8->CCMR1 |= ((Copy_u8Prescaler & 0x3)<< 2);// set prescaler

				switch(Copy_enuEdge)
				{
				case TIM_IC_RISING_EDGE:
					CLEARBIT(TIM8->CCER,1);//clear CCxP
					CLEARBIT(TIM8->CCER,3);//clear CCxNP
					break;
				case TIM_IC_FALLING_EDGE:
					SETBIT(TIM8->CCER,1);//set CCxP
					CLEARBIT(TIM8->CCER,3);//clear CCxNP
					break;
				case TIM_IC_BOTH_EDGES:
					SETBIT(TIM8->CCER,1);//set CCxP
					SETBIT(TIM8->CCER,3);//set CCxNP
					break;
				default:
					Local_enuErrorState = ES_Out_Of_Range;
					break;

				}
				SETBIT(TIM8->CCER,0);//Capture/Compare Enable Register
				break;
				case TIM_CHANNEL_2:
					TIM8->CCMR1 &= ~(0x3 << 8);// Mask CCxS bits
					TIM8->CCMR1 |= (0x1 << 8);// CC2 channel is configured as input, IC2 is mapped on TI2
					TIM8->CCMR1 &= ~(0x3 << 12);// mask ICxPSC
					TIM8->CCMR1 |= ((Copy_u8Prescaler & 0x3)<< 12);// set prescaler
					switch(Copy_enuEdge)
					{
					case TIM_IC_RISING_EDGE:
						CLEARBIT(TIM8->CCER,5);//clear CCxP
						CLEARBIT(TIM8->CCER,7);//clear CCxNP
						break;
					case TIM_IC_FALLING_EDGE:
						SETBIT(TIM8->CCER,5);//set CCxP
						CLEARBIT(TIM8->CCER,7);//clear CCxNP
						break;
					case TIM_IC_BOTH_EDGES:
						SETBIT(TIM8->CCER,5);//set CCxP
						SETBIT(TIM8->CCER,7);//set CCxNP
						break;
					default:
						Local_enuErrorState = ES_Out_Of_Range;
						break;

					}
					SETBIT(TIM8->CCER,4);//Capture/Compare Enable Register
					break;
					case TIM_CHANNEL_3:
						TIM8->CCMR2 &= ~(0x3 << 0);// Mask CCxS bits
						TIM8->CCMR2 |= (0x1 << 0);// CC3 channel is configured as input, IC3 is mapped on TI3
						TIM8->CCMR2 &= ~(0x3 << 2);// mask ICxPSC
						TIM8->CCMR2 |= ((Copy_u8Prescaler & 0x3) << 2);// set prescaler
						switch(Copy_enuEdge)
						{
						case TIM_IC_RISING_EDGE:
							CLEARBIT(TIM8->CCER,9);//clear CCxP
							CLEARBIT(TIM8->CCER,11);//clear CCxNP
							break;
						case TIM_IC_FALLING_EDGE:
							SETBIT(TIM8->CCER,9);//set CCxP
							CLEARBIT(TIM8->CCER,11);//clear CCxNP
							break;
						case TIM_IC_BOTH_EDGES:
							SETBIT(TIM8->CCER,9);//set CCxP
							SETBIT(TIM8->CCER,11);//set CCxNP
							break;
						default:
							Local_enuErrorState = ES_Out_Of_Range;
							break;

						}
						SETBIT(TIM8->CCER,8);//Capture/Compare Enable Register
						break;
						case TIM_CHANNEL_4:
							TIM8->CCMR2 &= ~(0x3 << 8);// Mask CCxS bits
							TIM8->CCMR2 |= (0x1 << 8);//CC4 channel is configured as input, IC4 is mapped on TI4
							TIM8->CCMR2 &= ~(0x3 << 10);// mask ICxPSC
							TIM8->CCMR2 |= ((Copy_u8Prescaler & 0x3) << 10);// set prescaler
							switch(Copy_enuEdge)
							{
							case TIM_IC_RISING_EDGE:
								CLEARBIT(TIM8->CCER,13);//clear CCxP

								break;
							case TIM_IC_FALLING_EDGE:
								SETBIT(TIM8->CCER,13);//set CCxP

								break;
							case TIM_IC_BOTH_EDGES:
								Local_enuErrorState = ES_NOK;// CH 4 does NOT provid this mode
								break;
							default:
								Local_enuErrorState = ES_Out_Of_Range;
								break;

							}
							SETBIT(TIM8->CCER,12);//Capture/Compare Enable Register
							break;
							default:
								Local_enuErrorState = ES_Out_Of_Range;
								break;
			}

			break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;
				break;
	}

	return Local_enuErrorState;
}
ES_t TIM_enuIC_GetValue(TIM_Id_t Copy_enuTimID, TIM_Channel_t Copy_enuChannel,u16 * Copy_Pu16Val)
{
	ES_t Local_enuErrorState = ES_OK;

	// Wait for capture flag


	if(Copy_Pu16Val)
	{
		switch(Copy_enuTimID)
		{
		case TIM1_ID:
			switch(Copy_enuChannel)
			{
			case TIM_CHANNEL_1:
				while(!GETBIT(TIM1->SR, 1));// Wait for capture flag
				*Copy_Pu16Val = TIM1->CCR1;
				CLEARBIT(TIM1->SR, 1);
				break;
			case TIM_CHANNEL_2:
				while(!GETBIT(TIM1->SR, 1));// Wait for capture flag
				*Copy_Pu16Val = TIM1->CCR2;
				CLEARBIT(TIM1->SR, 1);
				break;
			case TIM_CHANNEL_3:
				while(!GETBIT(TIM1->SR, 1));// Wait for capture flag
				*Copy_Pu16Val = TIM1->CCR3;
				CLEARBIT(TIM1->SR, 1);
				break;
			case TIM_CHANNEL_4:
				while(!GETBIT(TIM1->SR, 1));// Wait for capture flag
				*Copy_Pu16Val = TIM1->CCR4;
				CLEARBIT(TIM1->SR, 1);
				break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;
				break;
			}
			break;
			case TIM8_ID:
				switch(Copy_enuChannel)
				{
				case TIM_CHANNEL_1:
					while(!GETBIT(TIM8->SR, 1));// Wait for capture flag
					*Copy_Pu16Val = TIM8->CCR1;
					CLEARBIT(TIM8->SR, 1);
					break;
				case TIM_CHANNEL_2:
					while(!GETBIT(TIM8->SR, 1));// Wait for capture flag
					*Copy_Pu16Val = TIM8->CCR2;
					CLEARBIT(TIM8->SR, 1);
					break;
				case TIM_CHANNEL_3:
					while(!GETBIT(TIM8->SR, 1));// Wait for capture flag
					*Copy_Pu16Val = TIM8->CCR3;
					CLEARBIT(TIM8->SR, 1);
					break;
				case TIM_CHANNEL_4:
					while(!GETBIT(TIM8->SR, 1));// Wait for capture flag
					*Copy_Pu16Val = TIM8->CCR4;
					CLEARBIT(TIM8->SR, 1);
					break;
				default:
					Local_enuErrorState = ES_Out_Of_Range;
					break;
				}
				break;
				default:
					Local_enuErrorState = ES_Out_Of_Range;
					break;

		}
	}
	else
	{
		Local_enuErrorState = ES_NULLPOINTER;
	}

	return Local_enuErrorState;
}
ES_t TIM_enuIC_EnableInterrupt(TIM_Id_t Copy_enuTimID, TIM_Channel_t Copy_enuChannel)
{
	ES_t Local_enuErrorState = ES_OK;
	/*
	 * after going to isr clear CCxIF then call your function
	 * */
	switch(Copy_enuTimID)
	{
	case TIM1_ID:
		switch(Copy_enuChannel)
		{
		case TIM_CHANNEL_1:
			SETBIT(TIM1->DIER,1);//enable Capture/Compare 1 interrupt
			break;
		case TIM_CHANNEL_2:
			SETBIT(TIM1->DIER,2);//enable Capture/Compare 2 interrupt
			break;
		case TIM_CHANNEL_3:
			SETBIT(TIM1->DIER,3);//enable Capture/Compare 3 interrupt
			break;
		case TIM_CHANNEL_4:
			SETBIT(TIM1->DIER,4);//enable Capture/Compare 4 interrupt
			break;
		default:
			Local_enuErrorState = ES_Out_Of_Range;
			break;
		}
		break;
		case TIM8_ID:
			switch(Copy_enuChannel)
			{
			case TIM_CHANNEL_1:
				SETBIT(TIM8->DIER,1);//enable Capture/Compare 1 interrupt
				break;
			case TIM_CHANNEL_2:
				SETBIT(TIM8->DIER,2);//enable Capture/Compare 2 interrupt
				break;
			case TIM_CHANNEL_3:
				SETBIT(TIM8->DIER,3);//enable Capture/Compare 3 interrupt
				break;
			case TIM_CHANNEL_4:
				SETBIT(TIM8->DIER,4);//enable Capture/Compare 4 interrupt
				break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;
				break;
			}
			break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;
				break;

	}


	return Local_enuErrorState;
}
ES_t TIM_enuIC_DisableInterrupt(TIM_Id_t Copy_enuTimID, TIM_Channel_t Copy_enuChannel)
{
	ES_t Local_enuErrorState = ES_OK;

	switch(Copy_enuTimID)
	{
	case TIM1_ID:
		switch(Copy_enuChannel)
		{
		case TIM_CHANNEL_1:
			CLEARBIT(TIM1->DIER,1);//disable Capture/Compare 1 interrupt
			break;
		case TIM_CHANNEL_2:
			CLEARBIT(TIM1->DIER,2);//disable Capture/Compare 2 interrupt
			break;
		case TIM_CHANNEL_3:
			CLEARBIT(TIM1->DIER,3);//disable Capture/Compare 3 interrupt
			break;
		case TIM_CHANNEL_4:
			CLEARBIT(TIM1->DIER,4);//disable Capture/Compare 4 interrupt
			break;
		default:
			Local_enuErrorState = ES_Out_Of_Range;
			break;
		}
		break;
		case TIM8_ID:
			switch(Copy_enuChannel)
			{
			case TIM_CHANNEL_1:
				CLEARBIT(TIM8->DIER,1);//disable Capture/Compare 1 interrupt
				break;
			case TIM_CHANNEL_2:
				CLEARBIT(TIM8->DIER,2);//disable Capture/Compare 2 interrupt
				break;
			case TIM_CHANNEL_3:
				CLEARBIT(TIM8->DIER,3);//disable Capture/Compare 3 interrupt
				break;
			case TIM_CHANNEL_4:
				CLEARBIT(TIM8->DIER,4);//disable Capture/Compare 4 interrupt
				break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;
				break;
			}
			break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;
				break;

	}


	return Local_enuErrorState;
}



ES_t TIM_enuCallBack(TIM_Id_t Copy_enuTimID,TIM_Interrupt_t Copy_enuInterruptID, void (*Copy_PvidFun)(void) )
{
	ES_t Local_enuErrorState = ES_OK;
	if(Copy_PvidFun)
	{
		if(Copy_enuInterruptID >= TIM_INT_UIE && Copy_enuInterruptID <= TIM_INT_CTC4 )
		{
			switch(Copy_enuTimID)
			{
			case TIM1_ID:
				TIM1_GAofPtrTOFun[Copy_enuInterruptID] = Copy_PvidFun;
				break;
			case TIM8_ID:
				TIM8_GAofPtrTOFun[Copy_enuInterruptID] = Copy_PvidFun;
				break;
			default:
				Local_enuErrorState = ES_Out_Of_Range;
			}
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



void TIM1_UP_IRQHandler(void)
{
	if(GETBIT(TIM1->SR,0))
	{
		CLEARBIT(TIM1->SR,0);
		if(TIM1_GAofPtrTOFun[TIM_INT_UIE])
		{
			TIM1_GAofPtrTOFun[TIM_INT_UIE]();
		}
		else
		{
			/*DO Nothing*/
		}

	}
}
void TIM1_CC_IRQHandler(void)
{
	if(GETBIT(TIM1->SR,1))
	{
		CLEARBIT(TIM1->SR,1);
		if(TIM1_GAofPtrTOFun[TIM_INT_CC1IE])
		{
			TIM1_GAofPtrTOFun[TIM_INT_CC1IE]();
		}
		else
		{
			/*DO Nothing*/
		}

	}
	if(GETBIT(TIM1->SR,2))
	{
		CLEARBIT(TIM1->SR,2);
		if(TIM1_GAofPtrTOFun[TIM_INT_CC2IE])
		{
			TIM1_GAofPtrTOFun[TIM_INT_CC2IE]();
		}
		else
		{
			/*DO Nothing*/
		}

	}
	if(GETBIT(TIM1->SR,3))
	{
		CLEARBIT(TIM1->SR,3);
		if(TIM1_GAofPtrTOFun[TIM_INT_CC3IE])
		{
			TIM1_GAofPtrTOFun[TIM_INT_CC3IE]();
		}
		else
		{
			/*DO Nothing*/
		}

	}
	if(GETBIT(TIM1->SR,4))
	{
		CLEARBIT(TIM1->SR,4);
		if(TIM1_GAofPtrTOFun[TIM_INT_CC4IE])
		{
			TIM1_GAofPtrTOFun[TIM_INT_CC4IE]();
		}
		else
		{
			/*DO Nothing*/
		}

	}
}

void TIM8_UP_IRQHandler(void)
{

	if(GETBIT(TIM8->SR,0))
	{
		CLEARBIT(TIM8->SR,0);
		if(TIM8_GAofPtrTOFun[TIM_INT_UIE])
		{
			TIM8_GAofPtrTOFun[TIM_INT_UIE]();
		}
		else
		{
			/*DO Nothing*/
		}

	}
}
void TIM8_CC_IRQHandler(void)
{
	if(GETBIT(TIM8->SR,1))
	{
		CLEARBIT(TIM8->SR,1);
		if(TIM8_GAofPtrTOFun[TIM_INT_CC1IE])
		{
			TIM8_GAofPtrTOFun[TIM_INT_CC1IE]();
		}
		else
		{
			/*DO Nothing*/
		}

	}
	if(GETBIT(TIM8->SR,2))
	{
		CLEARBIT(TIM8->SR,2);
		if(TIM8_GAofPtrTOFun[TIM_INT_CC2IE])
		{
			TIM8_GAofPtrTOFun[TIM_INT_CC2IE]();
		}
		else
		{
			/*DO Nothing*/
		}

	}
	if(GETBIT(TIM8->SR,3))
	{
		CLEARBIT(TIM8->SR,3);
		if(TIM8_GAofPtrTOFun[TIM_INT_CC3IE])
		{
			TIM8_GAofPtrTOFun[TIM_INT_CC3IE]();
		}
		else
		{
			/*DO Nothing*/
		}

	}
	if(GETBIT(TIM8->SR,4))
	{
		CLEARBIT(TIM8->SR,4);
		if(TIM8_GAofPtrTOFun[TIM_INT_CC4IE])
		{
			TIM8_GAofPtrTOFun[TIM_INT_CC4IE]();
		}
		else
		{
			/*DO Nothing*/
		}

	}
}

