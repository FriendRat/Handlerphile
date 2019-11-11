#include <handlerphile.h>
#include <stdio.h>

using namespace Contextual;

int main(){
	
	const std::string filename = "new_file.txt";

	with {
		FileHandler(filename, std::fstream::out)(
			[](auto filehandler) {
				filehandler->file << "This is a new file.";
			}
		)
	};

	std::string file_contents;

	with {
		FileHandler(filename)(
			[&](auto filehandler){
				file_contents = filehandler->read();
			}
		)
	}; 

	std::cout << file_contents << std::endl;

	remove(filename.c_str());
}