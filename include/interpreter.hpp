#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <vector>

#include "index.hpp"
#include "track.hpp"
#include "token.hpp"

class interpreter {
private:
	std::vector<std::string> file_lines;
	bool name_valid = true, index_valid = true;
	std::string current_track_name;
	index current_track_index;
	void interpret_command(std::vector<token> tokens);
public:
	std::vector<track> track_list;
	interpreter() {}
	interpreter(std::vector<std::string> file_lines);
};

#endif
