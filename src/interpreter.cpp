#include <vector>
#include <sstream>
#include <iostream>

#include "../include/interpreter.hpp"

std::vector<std::string> parse_line(std::string line);
std::vector<token> tokenize(std::vector<std::string> words);
index parse_index(token index_token);

interpreter::interpreter(std::vector<std::string> file_lines)
{
	using namespace std;
	// TODO
	// Parse each line and tokenize it
	// Then, execute each command
	for (auto line: file_lines) {
		vector<string> line_pieces = parse_line(line);
		vector<token> tokens = tokenize(line_pieces);
		interpret_command(tokens);
	}
	for (auto t: this->track_list)
		std::cout << "track found: " << t.title
			<< " with index " << t.ind.seconds / 60 << "m "
			<< t.ind.seconds % 60 << "s "
			<< t.ind.frames << "f\n";
}

void interpreter::interpret_command(std::vector<token> tokens)
{
	if (tokens[0].is_keyword)
	{
		if (tokens[0].value == "TITLE") {
			if (!index_valid) {
				this->current_track_name = tokens[1].value;
				this->name_valid = true;
			}
		}		
		else if (tokens[0].value == "INDEX") {
			if (!index_valid){
			   	this->current_track_index = parse_index(tokens[2]);
				this->index_valid = true;
			}
		}
		else if (tokens[0].value == "TRACK") {
			if (name_valid && index_valid && this->current_track_name != "")
				this->track_list.push_back(track(this->current_track_index,
                                                 this->current_track_name));

			this->name_valid = false;
			this->index_valid = false;
		}
	}
}

index parse_index(token index_token)
{
	std::string index_str = index_token.value;
	index_str[2] = index_str[5] = ' ';
	std::istringstream ss(index_str);
	int min, sec, fra;
	ss >> min >> sec >> fra;
	return index(min, sec, fra);
}

std::vector<token> tokenize(std::vector<std::string> parsed_line)
{
	using namespace std;
	vector<token> result;
	for (string s: parsed_line) {
		if (s[0] == '"')
			result.push_back(token(false, s.substr(1, s.length() - 2)));
		else if (s[0] >= '0' && s[0] <= '9')
			result.push_back(token(false, s));
		else
			result.push_back(token(true, s));
	}

	return result;

}

std::vector<std::string> parse_line(std::string line)
{
	using namespace std;

	vector<string> results;

	string current;
	bool in_string = false;

	for (auto c: line) {
		if (!in_string) {
			if (c == ' ' || c == '\n' || c == '\t') {
				if (current != "")
					results.push_back(current);
				current = "";
			}
		   	else if (c == '"') {
				in_string = true;
				current += c;
			}
		   	else {
				current += c;
			}
		}
		else {
			current += c;
			if (c == '"') {
				in_string = false;
				results.push_back(current);
				current = "";
			}
		}
	}
	
	if (current != "")
		results.push_back(current);

	return results;
}
