#include <handlerphile.h>
#include <exception>


using namespace Contextual;

TEST_CASE("Test read/write functionality", "[read/write]") {


	SECTION("Test read, default mode") {

		with {
			FileHandler("tests/test_file.txt")(
				[&](auto filehander) {
					const std::string contents = filehander->read();
					REQUIRE(contents == "This is a test.");

				}
			)
		};
	}

	SECTION("Test read and write, default mode") {
		with {
			FileHandler("tests/test_file.txt")(
				[&](auto filehandler) {
					filehandler->file << "This is not a test.";
					std::string contents = filehandler->read();
					REQUIRE(contents == "This is not a test.");

				}
			)
		};	
	}

	SECTION("Test input mode argument") {
		with {
			FileHandler("tests/test_file.txt",  std::ios::trunc | std::ios::in | std::ios::out)(
				[&](auto filehandler) {
					filehandler->file << "This is a test.";
					std::string contents = filehandler->read();
					REQUIRE(contents == "This is a test.");
				}
			)
		};
	}
}

TEST_CASE("Test exceptions", "[exceptions]") {

	SECTION("Test non-existent file") {
		try {
			with {
				FileHandler("tests/non-existent.txt") (
					[&](auto filehandler) {
						REQUIRE(false);
					}
				)
			};
		} catch (std::runtime_error& e){
			REQUIRE(std::string(e.what()) == "File was not opened or was unexpectedly closed!");
		}

	}

	SECTION("Test error when closing file in context") {
		try {
			with {
				FileHandler("tests/non-existent.txt") (
					[&](auto filehandler) {
						filehandler->file.close();
					}
				)
			};
		} catch (std::runtime_error& e){
			REQUIRE(std::string(e.what()) == "File was not opened or was unexpectedly closed!");
		}
	}

	SECTION("Test exception handling") {
		try{
			with {
				FileHandler("tests/test_file.txt") (
					[&](auto filehandler){
						throw std::runtime_error("");
					}
				)
			};
		}
	}

}
