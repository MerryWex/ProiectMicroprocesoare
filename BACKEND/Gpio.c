#include "Gpio.h"

#define RED_LED_PIN (18) /* PORT B */
#define GREEN_LED_PIN (19) /* PORT B */
#define BLUE_LED_PIN (1) /* PORT D */

#define LED_PIN12 (12) /* PORT A12*/
#define LED_PIN4 (4) /* PORT A4 */
#define LED_PIN5 (5) /* PORT A5 */


void RGBLed_Init(void){
	
	/* Activarea semnalului de ceas pentru pinii folositi in cadrul led-ului RGB */
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
	
	PORTA->PCR[LED_PIN12] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[LED_PIN12] |= PORT_PCR_MUX(1);
	
	GPIOA->PDDR |= (1<<LED_PIN12);
	GPIOA->PCOR |= (1<<LED_PIN12);
	
	/*----*/
	
	PORTA->PCR[LED_PIN4] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[LED_PIN4] |= PORT_PCR_MUX(1);
	
	GPIOA->PDDR |= (1<<LED_PIN4);
	GPIOA->PCOR |= (1<<LED_PIN4);
	
	/*----*/
	
	PORTA->PCR[LED_PIN5] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[LED_PIN5] |= PORT_PCR_MUX(1);
	
	GPIOA->PDDR |= (1<<LED_PIN5);
	GPIOA->PCOR |= (1<<LED_PIN5);
	
	/* --- RED LED --- */
	
	/* Utilizare GPIO ca varianta de multiplexare */
	PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(1);
	
	/* Configurare pin pe post de output */
	GPIOB_PDDR |= (1<<RED_LED_PIN);
	
	/* Stingerea LED-ului (punerea pe 0 logic) */
	GPIOB_PSOR |= (1<<RED_LED_PIN);
	
	/* --- GREEN LED --- */
	
	/* Utilizare GPIO ca varianta de multiplexare */
	PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(1);
	
	/* Configurare pin pe post de output */
	GPIOB_PDDR |= (1<<GREEN_LED_PIN);
	
	/* Stingerea LED-ului (punerea pe 0 logic) */
	GPIOB_PSOR |= (1<<GREEN_LED_PIN);
	
	/* --- BLUE LED --- */
	
	/* Utilizare GPIO ca varianta de multiplexare */
	PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(1);
	
	/* Configurare pin pe post de output */
	GPIOD_PDDR |= (1<<BLUE_LED_PIN);
	
	/* Stingerea LED-ului (punerea pe 0 logic) */
	GPIOD_PSOR |= (1<<BLUE_LED_PIN);
}
