#include <string>
#ifndef TRACK_HPP
#define TRACK_HPP

#include <string>

#include "index.hpp"

struct track {
	index ind;
	std::string title;
	int track_no;
	track() { }
	track(int min, 
          int sec,
		  int frs,
		  std::string title,
		  int track_no)
			:ind(min, sec, frs),
			title(title) { }
	track(index ind,
          std::string title) { this->ind = ind; this->title = title; }
};

#endif
