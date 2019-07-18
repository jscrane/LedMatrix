#include <SimpleTimer.h>
#include <LedMatrix.h>

const uint8_t anodes[] = { 18, 17, 16, 15, 14, 12, 11, 10 };
const uint8_t gnds[] = { 9, 8, 7, 6, 5, 4, 3, 2 };

LedMatrix leds(sizeof(anodes), anodes, gnds);
SimpleTimer timer;

typedef uint8_t char_t[8];

// based on https://github.com/dhepper/font8x8/blob/master/font8x8_basic.h
const char_t chars[] = {
	{ 0x00, 0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E},   // U+0063 (c)
	{ 0x0C, 0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E},   // U+0069 (i)
	{ 0x00, 0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E},   // U+0061 (a)
	{ 0x00, 0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E},   // U+006F (o)
	{ 0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x18},   // U+0021 (!)
};

const int nc = sizeof(chars)/sizeof(chars[0]);

void scroll() {
	static int ci, off;

	int ni = ci+1;
	if (ni == nc) ni = 0;

	const char_t &c = chars[ci], &n = chars[ni];
	char_t d = { 0, 0, 0, 0, 0, 0, 0};
	for (int i = 0; i < leds.side(); i++) {
		int j = 0;
		for (int oj = off; oj < leds.side(); j++, oj++) {
			uint8_t a = (1 << oj), b = (1 << j);
			if (c[i] & a)
				d[i] |= b;
			else
				d[i] &= ~b;
		}
		for (int oj = 0; oj < off; j++, oj++) {
			uint8_t a = (1 << oj), b = (1 << j);
			if (n[i] & a)
				d[i] |= b;
			else
				d[i] &= ~b;
		}
	}
	if (++off == leds.side()) {
		off = 0;
		if (++ci == nc)
			ci = 0;
	}

	leds.bitmap(d);
}

void setup() {
	leds.begin();
	timer.setInterval(150, scroll);
}

void loop() {
	timer.run();
	leds.refresh();
}
