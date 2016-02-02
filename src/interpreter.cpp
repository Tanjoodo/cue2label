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

	for (auto line: file_lines) {
		vector<string> line_pieces = parse_line(line);
		vector<token> tokens = tokenize(line_pieces);
		interpret_command(tokens);
	}
}

void interpreter::interpret_command(std::vector<token> tokens)
{
	if (tokens[0].is_keyword)
	{
		if (tokens[0].value == "TITLE") {
			if (name_valid) {
				if (!track_list.empty())
					this->track_list[track_list.size() - 1].title
					   	= tokens[1].value;
				this->name_valid = false;
			}
		}		
		else if (tokens[0].value == "INDEX") {
			if (index_valid){
				if (!track_list.empty())
					this->track_list[track_list.size() - 1].ind
					   	= parse_index(tokens[2]);
				this->index_valid = false;
			}
		}
		else if (tokens[0].value == "TRACK") {
			this->track_list.push_back(track());

			this->name_valid = true;
			this->index_valid = true;
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
				if (c != '\r') current += c;
			}
		   	else {
				if (c != '\r') current += c;
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
