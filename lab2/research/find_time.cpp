#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

int main() {
    int max_threads = 30;
    std::string program_name = getenv("LAB2_PATH_TO_PROGRAMM");
	std::string path_to_data = getenv("LAB2_PATH_TO_DATA");
	std::string output_file = "results.txt";

	std::ofstream file(output_file);
	if (!file.is_open()) {
            std::cerr << "The file could not be opened to record the results.\n";
            return 1;
	}

    for (int n = 1; n <= max_threads; ++n) {

        for (int i = 0; i < 100; ++i) {
            std::string command = program_name + " " + path_to_data + " " +  std::to_string(n);

            auto start = std::chrono::high_resolution_clock::now();
            int result = std::system(command.c_str());

            if (result != 0) {
                std::cerr << "Error when starting the program with " << n
                          << " threads.\n";
                continue;
            }

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            file << n << " " << elapsed.count() << "\n";
        }
    }
    file.close();

    return 0;
}
