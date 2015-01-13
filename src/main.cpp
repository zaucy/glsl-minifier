#include <cstring>
#include <fstream>

#include <glsl_minifier.h>

std::string read_file(std::string path) {
	std::ifstream file;
	std::string fileString;
	file.open(path, std::ifstream::binary);
	
	if(file.is_open()) {
		auto fileBuf = file.rdbuf();
		std::size_t fileSize = fileBuf->pubseekoff(0, file.end);
		fileBuf->pubseekoff(0, file.beg);
		char* buffer = new char[fileSize];
		fileBuf->sgetn(buffer, fileSize);
		
		fileString.append(buffer, fileSize);
		
		file.close();
		
		
		delete[] buffer;
	} else {
		printf("Couldn't open file: '%s'\n", path.c_str());
	}
	
	return fileString;
}

void parse_arg(char**& args, int args_left) {
	char* arg = *args;
	
	if(strcmp(arg, "-o") == 0) {
		if(args_left > 0) {
			args++;
			printf("output file = '%s'\n", *args);
		} else {
			printf("no output file\n");
		}
	} else {
		printf("%s\n", glsl_minifier::minify(read_file(arg)).c_str());
	}
}

int main(int argc, char* argv[]) {
	
	for(int i=1; argc > i; i++) {
		char* arg = argv[i];
		char** args = argv+i;
		parse_arg(args, argc - i);
		while(argc > i && *args != argv[i]) {
			i++;
		}
	}
	
	return 0;
}
