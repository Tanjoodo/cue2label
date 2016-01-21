#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

struct token {
	bool is_keyword;
	std::string value;
	token() { this->is_keyword = false; }
	token(bool is_keyword, std::string value)
		:is_keyword(is_keyword),value(value) { }
};

#endif
