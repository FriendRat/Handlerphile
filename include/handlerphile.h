#ifndef HANDLERPHILE_H
#define HANDLERPHILE_H

#include <queue>
#include <contextual.h>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstring>

namespace Contextual{;

	struct IData {
		std::fstream file;

		unsigned int length(){
			file.seekg(0, file.end);
			unsigned int length = file.tellg();
			file.seekg(0, file.beg);
			return length;
		}

		std::string read() {
			unsigned int len = length();
			char* buffer = new char[len];
			memset(buffer, '\0', len);

			file.read(buffer, len);
			if (!file) {
				 std::cerr << "Error: only " << file.gcount() << "characters could be read.\n";
			}

			std::string contents;
			contents.assign(buffer, len);
			delete [] buffer;
			return contents;
		}
	};


	class FileHandler : public IResource<IData> {
	private:
		IData _data;
		bool verbose;
		std::string filename;

		void enter() override {
  			if (!resources->file.is_open()) {
	    		throw std::runtime_error("File was not opened successfully.");
  			} else {
    			if (verbose) std::cout << "File " << filename << " has been opened.\n";
  			}
		}

		void exit (std::optional<std::exception> e) override {
		    if (resources->file.is_open()){
    	        resources->file.close();
  	          if (verbose) std::cout << "File " << filename << " has been closed.\n";
  			} else {
  				throw std::runtime_error("File was not opened or was unexpectedly closed!");
  			}
  			if (e){
    			std::cerr << "An exception occurred! :::: ";
    			std::cerr << e.value().what() << ".\n";

  			}
		}

	public:
		FileHandler(std::string filename, std::ios::openmode mode = std::ios::in | std::ios::out,
										  bool verbose=false) :
												IResource<IData>(_data),
												_data(IData{std::fstream(filename, mode)}),
												verbose(verbose),
												filename(filename) {};
	};

}


#endif