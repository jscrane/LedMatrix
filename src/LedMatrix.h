#ifndef __LEDMATRIX_H__
#define __LEDMATRIX_H__

class LedMatrix {
public:
	LedMatrix(uint8_t s, const uint8_t a[], const uint8_t g[]): side(s) {
		for (int i = 0; i < side; i++) {
			sources[i] = a[i];
			sinks[i] = g[i];
			state[i] = 0;
		}
	}

	void begin() {
		for (int i = 0; i < side; i++) {
			pinMode(sources[i], OUTPUT);
			pinMode(sinks[i], OUTPUT);
			digitalWrite(sources[i], LOW);
			digitalWrite(sinks[i], HIGH);
		}
	}

	void clear() {
		for (int i = 0; i < side; i++)
			state[i] = 0;
	}

	void set(uint8_t r, uint8_t c) {
		state[r] |= (1 << c);
	}

	void clr(uint8_t r, uint8_t c) {
		state[r] &= ~(1 << c);
	}

	void bitmap(const uint8_t b[]) {
		for (int i = 0; i < side; i++)
			state[i] = b[i];
	}

	void refresh() {
		for (int i = 0; i < 20; i++)
			_refresh();
	}

private:
	void _refresh() {
		for (uint8_t r = 0, pr = prev(r); r < side; pr = r, r = next(r)) {
			digitalWrite(sinks[pr], HIGH);
			for (uint8_t c = 0; c < side; c = next(c)) {
				uint8_t rs = state[r];
				digitalWrite(sources[c], rs & (1 << c));
			}
			digitalWrite(sinks[r], LOW);
		}
	}

	inline int prev(int i) {
		return i == 0? side-1: --i;
	}

	inline int next(int i) {
		return i < side? ++i: 0;
	}

	uint8_t sources[8], sinks[8];
	uint8_t side;
	uint8_t state[8];
};
#endif
