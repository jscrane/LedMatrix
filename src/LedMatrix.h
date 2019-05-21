#ifndef __LEDMATRIX_H__
#define __LEDMATRIX_H__

class LedMatrix {
public:
	LedMatrix(uint8_t side, const uint8_t sources[], const uint8_t sinks[]);

	void begin();

	void clear() {
		for (int i = 0; i < side; i++)
			state[i] = 0;
	}

	inline void set(uint8_t r, uint8_t c) {
		state[r] |= (1 << c);
	}

	inline void clr(uint8_t r, uint8_t c) {
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

	inline uint8_t prev(uint8_t i) {
		return i == 0? side-1: --i;
	}

	inline uint8_t next(uint8_t i) {
		return ++i < side? i: 0;
	}

private:
	void _refresh();

	uint8_t sources[8], sinks[8];
	uint8_t side;
	uint8_t state[8];
};
#endif
