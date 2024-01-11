#include "Pit.h"
#include "Uart.h"

#define RED_LED_PIN (18) /* PORT B */
#define GREEN_LED_PIN (19) /* PORT B */
#define BLUE_LED_PIN (1) /* PORT D */

uint8_t led_state;
uint8_t change_sequence;
uint8_t individual_color;
uint8_t duration_flag;
uint8_t stop_led;

void PIT_Init(void) {
	
	/* Activarea semnalului de ceas pentru perifericul PIT */
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	/* Utilizarea semnalului de ceas pentru tabloul de timere */
	PIT_MCR &= ~PIT_MCR_MDIS_MASK;
	/* Oprirea decrementarii valorilor numaratoarelor in modul debug */
	PIT->MCR |= PIT_MCR_FRZ_MASK;
	/* Setarea valorii numaratorului de pe canalul 0 la o perioada de 1 secunda */
	
	/*461ms:*/
	PIT->CHANNEL[0].LDVAL = 0xAB917D ;
	
  /* Activarea intreruperilor pe canalul 0 */
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;
	/* Activarea timerului de pe canalul 0 */
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
	
	/* Activarea intreruperii mascabile si setarea prioritatii */
	NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_SetPriority(PIT_IRQn,5);
	NVIC_EnableIRQ(PIT_IRQn);
	
	led_state=0;
}

void PIT_IRQHandler(void) {
	
	/*461ms*/
	if(duration_flag == '4')
		PIT->CHANNEL[0].LDVAL = 0xAB917D ;
	
	/*10 ms*/
	if(duration_flag == '1')
		PIT->CHANNEL[0].LDVAL = 0x25376F;
	
	/*1 s*/
	if(duration_flag == '2')
		PIT->CHANNEL[0].LDVAL = 0x1742A62 ;
	
	/*2 s*/
	if(duration_flag == '3')
		PIT->CHANNEL[0].LDVAL = 0x2E854C9 ;
	
	if(PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) 
	{
	PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;
		
  if(change_sequence == '1')
  {		
		if(led_state == 0)
		{
			/* YELLOW */
			GPIOB_PSOR |= (1<<RED_LED_PIN);
			GPIOD_PSOR |= (1<<BLUE_LED_PIN);
			GPIOB_PSOR |= (1<<GREEN_LED_PIN);

			GPIOB_PCOR |= (1<<GREEN_LED_PIN);
			GPIOB_PCOR |= (1<<RED_LED_PIN);
			
			led_state = 1;
		} 
		else if (led_state == 1) 
		{
			/* TURQUOISE */
			GPIOB_PSOR |= (1<<GREEN_LED_PIN);
			GPIOB_PSOR |= (1<<RED_LED_PIN);
					
			GPIOB_PCOR |= (1<<GREEN_LED_PIN);
			GPIOD_PCOR |= (1<<BLUE_LED_PIN);
			led_state = 2;
		} 
		else if (led_state == 2)
		{			
			/* GREEN */
			GPIOB_PSOR |= (1<<GREEN_LED_PIN);
			GPIOD_PSOR |= (1<<BLUE_LED_PIN);
					
			GPIOB_PCOR |= (1<<GREEN_LED_PIN);
			led_state = 3;
		}
		else if (led_state == 3)
		{
			/* WHITE */
			GPIOB_PSOR |= (1<<GREEN_LED_PIN);
					
			GPIOB_PCOR |= (1<<RED_LED_PIN);
			GPIOD_PCOR |= (1<<BLUE_LED_PIN);
			GPIOB_PCOR |= (1<<GREEN_LED_PIN);
			led_state = 0;
			
		}
	}
	else
	{
		if(led_state == 0)
		{
			/* WHITE */
			GPIOB_PSOR |= (1<<GREEN_LED_PIN);
			GPIOB_PSOR |= (1<<RED_LED_PIN);
					
			if(stop_led == 'w')
			{
				GPIOB_PSOR |= (1<<RED_LED_PIN);
				GPIOD_PSOR |= (1<<BLUE_LED_PIN);
				GPIOB_PSOR |= (1<<GREEN_LED_PIN);
			}
			else
			{
				GPIOB_PCOR |= (1<<RED_LED_PIN);
				GPIOD_PCOR |= (1<<BLUE_LED_PIN);
				GPIOB_PCOR |= (1<<GREEN_LED_PIN);
				stop_led = 'x';
			}
			led_state = 1;
		} 
		else if (led_state == 1) 
		{
			/* GREEN */
			GPIOB_PSOR |= (1<<RED_LED_PIN);
			GPIOD_PSOR |= (1<<BLUE_LED_PIN);
			GPIOB_PSOR |= (1<<GREEN_LED_PIN);
			
			if(stop_led == 'g')
			{
				GPIOB_PSOR |= (1<<RED_LED_PIN);
				GPIOD_PSOR |= (1<<BLUE_LED_PIN);
				GPIOB_PSOR |= (1<<GREEN_LED_PIN);
				
			}
			else
			{
				GPIOB_PCOR |= (1<<GREEN_LED_PIN);
				stop_led = 'x';
			}
			led_state = 2;
		} 
		else if (led_state == 2)
		{
			/* TURQUOISE */
			GPIOB_PSOR |= (1<<GREEN_LED_PIN);
					
			if(stop_led == 't')
			{
				GPIOB_PSOR |= (1<<RED_LED_PIN);
				GPIOD_PSOR |= (1<<BLUE_LED_PIN);
				GPIOB_PSOR |= (1<<GREEN_LED_PIN);
			}
			else
			{
				GPIOB_PCOR |= (1<<GREEN_LED_PIN);
				GPIOD_PCOR |= (1<<BLUE_LED_PIN);
				stop_led = 'x';
			}
			led_state = 3;
		}
		else if (led_state == 3)
		{
			/* YELLOW */
			GPIOB_PSOR |= (1<<GREEN_LED_PIN);
			GPIOD_PSOR |= (1<<BLUE_LED_PIN);
			if(stop_led == 'y')
			{
				GPIOB_PSOR |= (1<<RED_LED_PIN);
			  GPIOD_PSOR |= (1<<BLUE_LED_PIN);
			  GPIOB_PSOR |= (1<<GREEN_LED_PIN);
			}
			else
			{
				GPIOB_PCOR |= (1<<GREEN_LED_PIN);
				GPIOB_PCOR |= (1<<RED_LED_PIN);
				stop_led = 'x';
			}
			led_state = 0;
		}
	}
	
	/* show individual colors */
	
	if(individual_color == 'W')
	{					
		GPIOB_PCOR |= (1<<RED_LED_PIN);
		GPIOD_PCOR |= (1<<BLUE_LED_PIN);
		GPIOB_PCOR |= (1<<GREEN_LED_PIN);
	}
	
	if(individual_color == 'G')
	{
		GPIOB_PSOR |= (1<<GREEN_LED_PIN);
		GPIOB_PSOR |= (1<<RED_LED_PIN);
		GPIOD_PSOR |= (1<<BLUE_LED_PIN);
		
		GPIOB_PCOR |= (1<<GREEN_LED_PIN);
	}
	
	if(individual_color == 'T')
	{
		GPIOB_PSOR |= (1<<GREEN_LED_PIN);
		GPIOB_PSOR |= (1<<RED_LED_PIN);
		GPIOD_PSOR |= (1<<BLUE_LED_PIN);
		
		GPIOB_PCOR |= (1<<GREEN_LED_PIN);
		GPIOD_PCOR |= (1<<BLUE_LED_PIN);
	}
	
	if(individual_color == 'Y')
	{
		GPIOB_PSOR |= (1<<GREEN_LED_PIN);
		GPIOB_PSOR |= (1<<RED_LED_PIN);
		GPIOD_PSOR |= (1<<BLUE_LED_PIN);
		
		GPIOB_PCOR |= (1<<GREEN_LED_PIN);
		GPIOB_PCOR |= (1<<RED_LED_PIN);
	}
	
}	
}
