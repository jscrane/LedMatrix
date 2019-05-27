#include <Arduino.h>
#include <LedMatrix.h>

void LedMatrix::begin() {
	for (int i = 0; i < _side; i++) {
		pinMode(_sources[i], OUTPUT);
		pinMode(_sinks[i], OUTPUT);
		digitalWrite(_sources[i], LOW);
		digitalWrite(_sinks[i], HIGH);
	}
}

void LedMatrix::_refresh() {
	for (uint8_t r = 0, pr = _side-1; r < _side; pr = r, r++) {
		digitalWrite(_sinks[pr], HIGH);
		for (uint8_t c = 0; c < _side; c++) {
			uint8_t rs = _state[r];
			digitalWrite(_sources[c], rs & (1 << c));
		}
		digitalWrite(_sinks[r], LOW);
	}
}

LedMatrix::LedMatrix(uint8_t s, const uint8_t a[], const uint8_t g[]): _side(s) {
	for (int i = 0; i < _side; i++) {
		_sources[i] = a[i];
		_sinks[i] = g[i];
		_state[i] = 0;
	}
}
