#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

void play_tone(uint8_t ocr2a_val, uint16_t duration_ms) {
	// Setup Timer2 in CTC mode
	TCCR2A = 0x02;
	TCCR2B = 0b00000011;  // Prescaler = 32
	OCR2A = ocr2a_val;
	
	for (uint16_t i = 0; i < duration_ms; i += 2) {
		while (!(TIFR2 & (1 << OCF2A)));
		TIFR2 |= (1 << OCF2A); // Clear flag
		PORTC ^= (1 << PC5);   // Toggle buzzer
		_delay_ms(1);          // Rough half-period
	}
	
	TCCR2B = 0x00;
	PORTC &= ~(1 << PC5); // Turn off buzzer
	_delay_ms(100);       // Short pause between notes
}

int main(void) {
	DDRC |= (1 << PC5);  // Set PC5 as output
	
	CLKPR = (1 << CLKPCE);
	CLKPR = 0b00000011;  // Clock divided by 8 → 1 MHz

	while (1) {
		play_tone(60, 500); // Do
		play_tone(53, 500); // Re
		play_tone(47, 500); // Mi
		play_tone(44, 500); // Fa
		play_tone(40, 500); // So
		play_tone(35, 500); // La
		play_tone(29, 500); // Ti
		_delay_ms(1000);
	}
}
