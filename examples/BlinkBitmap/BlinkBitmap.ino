#include <SimpleTimer.h>
#include <LedMatrix.h>

const uint8_t anodes[] = { 18, 17, 16, 15, 14, 12, 11, 10 };
const uint8_t gnds[] = { 9, 8, 7, 6, 5, 4, 3, 2 };

LedMatrix leds(sizeof(anodes), anodes, gnds);
SimpleTimer timer;

const uint8_t X[] = {
	0b10000001,
	0b01000010,
	0b00100100,
	0b00011000,
	0b00011000,
	0b00100100,
	0b01000010,
	0b10000001,
};

void next_bitmap() {
	static bool b;
	if (b)
		leds.bitmap(X);
	else
		leds.clear();
	b = !b;
}

void setup() {
	leds.begin();
	leds.bitmap(X);
	timer.setInterval(1000, next_bitmap);
}

void loop() {
	leds.refresh();
	timer.run();
}
