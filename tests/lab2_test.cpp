#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <unistd.h>
#include <filesystem>

const std::string LAB2_PATH_TO_PROGRAMM = std::string(getenv("LAB2_PATH_TO_PROGRAMM"));
const std::string LAB2_PATH_TO_INPUT_DATA = std::string(getenv("LAB2_PATH_TO_INPUT_DATA"));
const std::string LAB2_PATH_TO_OUTPUT_DATA = std::string(getenv("LAB2_PATH_TO_OUTPUT_DATA"));


TEST(TestUsingDataFromFiles, TestMain) {
    std::string maxThreads = "10";
    std::ifstream inputDataFile(LAB2_PATH_TO_INPUT_DATA);
    std::ifstream outputDataFile(LAB2_PATH_TO_OUTPUT_DATA);
    std::string inputData;
    std::string outputData;
    std::string line;
    std::string output;
    std::string currentInputFilePath =
        std::filesystem::current_path().string() + "current_input_file.txt";
    std::string command;
    std::array<char, 128> buffer;

    if (!(inputDataFile.is_open() && outputDataFile.is_open())) {
        std::cerr << "Can not open file with input data or output data"
                  << std::endl;
        exit(1);
    }

    while (true) {
        inputData.clear();
        outputData.clear();
        output.clear();
        line.clear();

        while (getline(inputDataFile, line)) {
            if (line.empty()) {
                break;
            }
            inputData += line + "\n";
        }

        while (getline(outputDataFile, line)) {
            if (line.empty()) {
                break;
            }
            outputData += line + "\n";
        }

        if (inputData.empty() || outputData.empty()) {
            exit(0);
        }

        std::ofstream currentInputFile(currentInputFilePath);
        if (!currentInputFile.is_open()) {
            std::cerr << "Can not open file for writing current points"
                      << std::endl;
            exit(1);
        } else {
            currentInputFile << inputData;
            currentInputFile.close();
        }

        command = LAB2_PATH_TO_PROGRAMM + " " + currentInputFilePath + " " +
                  maxThreads;
        FILE *pipe = popen(command.c_str(), "r");
        if (!pipe) {
            throw std::runtime_error("Can not open pipe!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
            output += buffer.data();
        }
        pclose(pipe);

        EXPECT_EQ(output, outputData);
    }

    inputDataFile.close();
    outputDataFile.close();
    std::remove(currentInputFilePath.c_str());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}