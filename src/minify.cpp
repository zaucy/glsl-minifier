#include "../include/glsl_minifier.h"

using namespace std;

bool is_eol(char c) {
	return c == '\n' || c == '\r';
}

bool is_ws(char c) {
	return c == ' ' || c == '\t' || is_eol(c);
}

bool needs_ws(char c) {
	return !is_ws(c)
		&& c != '('
		&& c != ')'
		&& c != '{'
		&& c != '}'
		&& c != ';'
		&& c != ':'
		&& c != '='
		&& c != '\''
		&& c != '"';
}

string glsl_minifier::minify(string src) {
	string minified_src;
	
	char c = '\0', last_c;
	
	for(auto it=src.begin(); it != src.end(); it++) {
		last_c = c;
		c = *it;
		
		
		if(c == '#') {
			if(last_c != '\0' && last_c != '\n') {
				minified_src += '\n';
			}
			for(; it != src.end(); it++) {
				last_c = c;
				c = *it;
				
				minified_src += c;
				
				if(is_eol(c) && last_c != '\\') {
					last_c = c;
					break;
				} else
				if(c == '/' && last_c == '/') {
					minified_src.pop_back();
					minified_src.pop_back();
					for(; it != src.end(); it++) {
						c = *it;
						if(is_eol(c)) {
							break;
						}
					}
					minified_src += '\n';
					last_c = '\n';
					break;
				}
			}
		} else
		if(is_ws(c) && is_ws(last_c)) {
			continue;
		} else
		if(is_ws(c) && !needs_ws(last_c)) {
			continue;
		}
		if(is_ws(last_c) && !needs_ws(c)) {
			if(is_ws(minified_src.back())) {
				minified_src.pop_back();
			}
			minified_src.push_back(c);
			continue;
		} else
		if(last_c == '/' && c == '/') {
			minified_src.pop_back();
			for(; it != src.end(); it++) {
				last_c = c;
				c = *it;
				if(is_eol(c)) {
					break;
				}
			}
		} else
		if(last_c == '/' && c == '*') {
			minified_src.pop_back();
			it++;
			for(; it != src.end(); it++) {
				last_c = c;
				c = *it;
				if(last_c == '*' && c == '/') {
					break;
				}
			}
		} else {
			minified_src += c;
		}
	}
	
	return minified_src;
}
