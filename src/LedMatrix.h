#ifndef __LEDMATRIX_H__
#define __LEDMATRIX_H__

class LedMatrix {
public:
	LedMatrix(uint8_t side, const uint8_t sources[], const uint8_t sinks[]);

	void begin();

	void clear() {
		for (int i = 0; i < _side; i++)
			_state[i] = 0;
	}

	inline void set(uint8_t r, uint8_t c) {
		_state[r] |= (1 << c);
	}

	inline void clr(uint8_t r, uint8_t c) {
		_state[r] &= ~(1 << c);
	}

	void bitmap(const uint8_t b[]) {
		for (int i = 0; i < _side; i++)
			_state[i] = b[i];
	}

	void refresh() {
		for (int i = 0; i < 20; i++)
			_refresh();
	}

	inline uint8_t prev(uint8_t i) const {
		return i == 0? _side-1: --i;
	}

	inline uint8_t next(uint8_t i) const {
		return ++i < _side? i: 0;
	}

	inline uint8_t side() const {
		return _side;
	}
private:
	void _refresh();

	uint8_t _sources[8], _sinks[8];
	const uint8_t _side;
	uint8_t _state[8];
};
#endif
