#include <SimpleTimer.h>
#include <LedMatrix.h>

const uint8_t anodes[] = { 9, 14, 15, 16, 17, 18, 10 };
const uint8_t gnds[] = { 8, 7, 6, 5, 4, 3, 2 };

LedMatrix leds(sizeof(anodes), anodes, gnds);
SimpleTimer timer;

const uint8_t X[] = {
	0b1000001,
	0b0100010,
	0b0010100,
	0b0001000,
	0b0010100,
	0b0100010,
	0b1000001,
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
