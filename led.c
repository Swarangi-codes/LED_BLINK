#include <stdint.h>

#define PORTB *(volatile uint8_t*)0x25
#define DDRB *(volatile uint8_t*)0x24


int main(void){
	volatile unsigned long int i; //compiler doesn't optimize volatile variables
	
	DDRB |= (1<<5);
	
	while(1){
		PORTB |= (1<<5);
		for(i=0; i<0x7D00; i++);  // ≈ 1 second at 128kHz
		PORTB &= ~(1<<5);
		for(i=0; i<0x7D00; i++);  // ≈ 1 second at 128kHz
	}
}