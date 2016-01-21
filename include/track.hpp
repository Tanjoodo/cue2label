#include <string>
#ifndef TRACK_HPP
#define TRACK_HPP

#include <string>

#include "index.hpp"

struct track {
	index ind;
	std::string title;
	track() { }
	track(int min, 
          int sec,
		  int frs,
		  std::string title):ind(min, sec, frs),title(title) { }
};

#endif
