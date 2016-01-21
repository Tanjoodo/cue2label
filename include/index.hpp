#ifndef INDEX_HPP
#define INDEX_HPP

struct index {
	int seconds,
		frames;
	index() { this->seconds = 0; this->frames = 0; }
	index(int min, int sec, int frs) {
		seconds = min * 60 + sec;
		frames = frs;
	}
};

#endif
