#include "MKL25Z4.h"
#include "Uart.h"
#include "Pit.h"
#include "Gpio.h"
#include "ADC.h"
#include "main.h"

extern uint32_t timer_value;
extern uint8_t led_state;
extern uint8_t change_sequence;
extern uint8_t individual_color;
extern uint8_t duration_flag;
extern uint8_t stop_led;

void interpret_flags(uint8_t* _receivedChar, uint8_t* _change_sequence, uint8_t* _individual_color, uint8_t* _duration_flag, uint8_t* _stop_led)
{
	if (is_UART_DataAvailable()) {
		(*_receivedChar) = UART_Receive();
	}
	if((*_receivedChar) == 'M')
	{
		(*_change_sequence) = '1';
		(*_individual_color) = 'X';
	}
	else
	{
		(*_change_sequence) = '0';
		(*_individual_color) = 'X';
	}
	
	if((*_receivedChar == 'N') && (*_change_sequence) == 1)
	{
		(*_change_sequence) = '0';
		(*_individual_color) = 'X';
		(*_stop_led) = 'q';
	}

	if((*_receivedChar) == 'W')
		(*_individual_color) = 'W';
	if((*_receivedChar) == 'G')
		(*_individual_color) = 'G';
	if((*_receivedChar) == 'T')
		(*_individual_color) = 'T';
	if((*_receivedChar) == 'Y')
		(*_individual_color) = 'Y';
		
	if((*_receivedChar) == '1')
		(*_duration_flag) = '1';
  if((*_receivedChar) == '2')
		(*_duration_flag) = '2';
	if((*_receivedChar) == '3')
		(*_duration_flag) = '3';
	if((*_receivedChar) == '4')
		(*_duration_flag) = '4';
	
	if((*_receivedChar) == 'w')
		(*_stop_led) = 'w';
	if((*_receivedChar) == 'g')
		(*_stop_led) = 'g';
	if((*_receivedChar) == 't')
		(*_stop_led) = 't';
	if((*_receivedChar) == 'y')
		(*_stop_led) = 'y';
	
}



int main(void) {

	uint8_t receivedChar = 'X';
	
	UART0_Init(19200);
	RGBLed_Init();
	ADC0_Init();
	PIT_Init();
	
	while(1) {
	interpret_flags(&receivedChar, &change_sequence, &individual_color, &duration_flag, &stop_led);
	PIT_IRQHandler();
	ADC0_IRQHandler();
	UART0_IRQHandler();
		
		if(flag)
		{
			uint8_t parte_zecimala = (uint8_t) measured_voltage;
			uint8_t parte_fractionara1 = ((uint8_t)(measured_voltage * 10)) % 10;
			uint8_t parte_fractionara2 = ((uint8_t)(measured_voltage * 100)) % 10;
			
			UART0_Transmit('V');
			UART0_Transmit(' ');
			UART0_Transmit('=');
			UART0_Transmit(' ');
			UART0_Transmit(parte_zecimala + 0x30);
			UART0_Transmit('.');
			UART0_Transmit(parte_fractionara1 + 0x30);
			UART0_Transmit(parte_fractionara2 + 0x30);
			UART0_Transmit('V');
			UART0_Transmit(0x0A);
			UART0_Transmit(0x0D);
			/* UART0_Transmit(receivedChar); */
			flag = 0;
	 }
	}

}
