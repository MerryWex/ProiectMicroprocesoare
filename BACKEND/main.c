#include "MKL25Z4.h"
#include "Uart.h"
#include "Pit.h"
#include "Gpio.h"
#include "ADC.h"

extern uint32_t timer_value;
extern uint8_t led_state;
extern uint8_t change_sequence;
extern uint8_t individual_color;
extern uint8_t duration_flag;
extern uint8_t stop_led;


int main(void) {

	uint8_t receivedChar = 'X';
	
	UART0_Init(115200);
	RGBLed_Init();
	ADC0_Init();
	PIT_Init();
	
	while(1) {
		
	if (is_UART_DataAvailable()) {
		receivedChar = UART_Receive();
	}
	if(receivedChar == 'M')
	{
		change_sequence = '1';
		individual_color = 'X';
	}
	else
	{
		change_sequence = '0';
		individual_color = 'X';
	}
	
	if(receivedChar == 'N' && change_sequence == 1)
	{
		change_sequence = '0';
		individual_color = 'X';
		stop_led = 'q';
	}

	if(receivedChar == 'W')
		individual_color = 'W';
	if(receivedChar == 'G')
		individual_color = 'G';
	if(receivedChar == 'T')
		individual_color = 'T';
	if(receivedChar == 'Y')
		individual_color = 'Y';
		
	if(receivedChar == '1')
		duration_flag = '1';
  if(receivedChar == '2')
		duration_flag = '2';
	if(receivedChar == '3')
		duration_flag = '3';
	if(receivedChar == '4')
		duration_flag = '4';
	
	if(receivedChar == 'w')
		stop_led = 'w';
	if(receivedChar == 'g')
		stop_led = 'g';
	if(receivedChar == 't')
		stop_led = 't';
	if(receivedChar == 'y')
		stop_led = 'y';
	
	PIT_IRQHandler();
	ADC0_IRQHandler();
	UART0_IRQHandler();
		
		if(flag)
		{
			uint8_t parte_zecimala = (uint8_t) measured_voltage;
			uint8_t parte_fractionara1 = ((uint8_t)(measured_voltage * 10)) % 10;
			uint8_t parte_fractionara2 = ((uint8_t)(measured_voltage * 100)) % 10;
			
			UART0_Transmit('V');
			UART0_Transmit('o');
			UART0_Transmit('l');
			UART0_Transmit('t');
			UART0_Transmit('a');
			UART0_Transmit('g');
			UART0_Transmit('e');
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
