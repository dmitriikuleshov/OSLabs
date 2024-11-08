#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <unistd.h>
#include <filesystem>

const std::string LAB2_PATH_TO_PROGRAMM = std::string(getenv("LAB2_PATH_TO_PROGRAMM"));
const std::string LAB2_PATH_TO_INPUT_DATA = std::string(getenv("LAB2_PATH_TO_INPUT_DATA"));
const std::string LAB2_PATH_TO_OUTPUT_DATA = std::string(getenv("LAB2_PATH_TO_OUTPUT_DATA"));

void ExecuteProgramm(const std::string command, std::string &output) {
    std::array<char, 128> buffer;
    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("Can not open pipe!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        output += buffer.data();
    }
    pclose(pipe);
}

void PutDataToTempFile(const std::string filePath, const std::string data) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Can not open file for writing current points"
                  << std::endl;
        exit(1);
    } else {
        file << data;
        file.close();
    }
}

TEST(TestUsingDataFromFiles, TestUsingDataFromFiles) {
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
            inputDataFile.close();
            outputDataFile.close();
            std::remove(currentInputFilePath.c_str());
            return;
        }

        PutDataToTempFile(currentInputFilePath, inputData);

        command = LAB2_PATH_TO_PROGRAMM + " " + currentInputFilePath + " " +
                  maxThreads;
        ExecuteProgramm(command, output);

        EXPECT_EQ(output, outputData);
    }
}

TEST(OneThread, OneThread) {
    std::string currentInputFilePath =
        std::filesystem::current_path().string() + "current_input_file.txt";
    std::string inputData = "0 0 2\n2 0 0\n0 0 2\n0 0 1\n0 1 0\n1 0 1";
    PutDataToTempFile(currentInputFilePath, inputData);

    std::string command =
        LAB2_PATH_TO_PROGRAMM + " " + currentInputFilePath + " " + "1";
    std::string outputOne;
    ExecuteProgramm(command, outputOne);

    std::string expectedOutput = "Point 1: (0.00, 0.00, 2.00)\nPoint 2: (2.00, 0.00, 0.00)\nPoint 3: (0.00, 1.00, 0.00)\nMaximum area: 2.45\n";
    EXPECT_EQ(outputOne, expectedOutput);
}


TEST(TestTheSameResult, TestTheSameResult) {
    std::string currentInputFilePath =
        std::filesystem::current_path().string() + "current_input_file.txt";
    std::string inputData = "0 0 2\n2 0 0\n0 0 2\n0 0 1\n0 1 0\n1 0 1";
    PutDataToTempFile(currentInputFilePath, inputData);

    std::string command1 =
            LAB2_PATH_TO_PROGRAMM + " " + currentInputFilePath + " " + "1";
    std::string command2 =
        LAB2_PATH_TO_PROGRAMM + " " + currentInputFilePath + " " + "10";

    std::string outputOne;
    std::string outputMany;
    ExecuteProgramm(command1, outputOne);
    ExecuteProgramm(command2, outputMany);
    EXPECT_EQ(outputOne, outputMany);
    std::remove(currentInputFilePath.c_str());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}