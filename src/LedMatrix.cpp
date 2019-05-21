#include <Arduino.h>
#include <LedMatrix.h>

void LedMatrix::begin() {
	for (int i = 0; i < side; i++) {
		pinMode(sources[i], OUTPUT);
		pinMode(sinks[i], OUTPUT);
		digitalWrite(sources[i], LOW);
		digitalWrite(sinks[i], HIGH);
	}
}

void LedMatrix::_refresh() {
	for (uint8_t r = 0, pr = side-1; r < side; pr = r, r++) {
		digitalWrite(sinks[pr], HIGH);
		for (uint8_t c = 0; c < side; c++) {
			uint8_t rs = state[r];
			digitalWrite(sources[c], rs & (1 << c));
		}
		digitalWrite(sinks[r], LOW);
	}
}

LedMatrix::LedMatrix(uint8_t s, const uint8_t a[], const uint8_t g[]): side(s) {
	for (int i = 0; i < side; i++) {
		sources[i] = a[i];
		sinks[i] = g[i];
		state[i] = 0;
	}
}
