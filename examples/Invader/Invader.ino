#include <SimpleTimer.h>
#include <LedMatrix.h>

const uint8_t anodes[] = { 18, 17, 16, 15, 14, 12, 11, 10 };
const uint8_t gnds[] = { 9, 8, 7, 6, 5, 4, 3, 2 };

LedMatrix leds(sizeof(anodes), anodes, gnds);
SimpleTimer timer;

const uint8_t A[] = {
	0b00011000,
	0b00111100,
	0b01111110,
	0b11011011,
	0b11111111,
	0b00100100,
	0b01011010,
	0b10100101,
};

const uint8_t B[] = {
	0b00011000,
	0b00111100,
	0b01111110,
	0b11011011,
	0b11111111,
	0b01011010,
	0b10100101,
	0b01000010,
};

void next_bitmap() {
	static bool b;
	if (b)
		leds.bitmap(A);
	else
		leds.bitmap(B);
	b = !b;
}

void setup() {
	leds.begin();
	leds.bitmap(A);
	timer.setInterval(1000, next_bitmap);
}

void loop() {
	leds.refresh();
	timer.run();
}
