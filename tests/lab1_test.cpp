#include "parent.hpp"
#include "utils.hpp"
#include <fcntl.h>
#include <gtest/gtest.h>
#include <unistd.h>

// Helper function to Simulate pipes and return data for testing child
// processes.
std::string SimulateChildProcess(const char *childPath, const char *inputData) {
    int pipe_to_child[2], pipe_from_child[2];

    if (pipe(pipe_to_child) == -1 || pipe(pipe_from_child) == -1) {
        perror("Error creating pipes");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Error creating the process");
        exit(1);
    }

    if (pid == 0) {                // Child process
        close(pipe_to_child[1]);   // Close unused write end of the input pipe
        close(pipe_from_child[0]); // Close unused read end of the output pipe

        // Pass file descriptors to child via arguments
        std::string readFdStr = std::to_string(pipe_to_child[0]);
        std::string writeFdStr = std::to_string(pipe_from_child[1]);

        char *args[] = {const_cast<char *>(childPath),
                        const_cast<char *>(readFdStr.c_str()),
                        const_cast<char *>(writeFdStr.c_str()), nullptr};

        if (execvp(args[0], args) == -1) {
            perror("Error starting the child process");
            exit(EXIT_FAILURE);
        }
    } else {                       // Parent process
        close(pipe_to_child[0]);   // Close unused read end of the input pipe
        close(pipe_from_child[1]); // Close unused write end of the output pipe

        // Write input data to child process
        write(pipe_to_child[1], inputData, strlen(inputData) + 1);
        close(pipe_to_child[1]); // Close after writing

        // Read processed data from child process
        char buffer[256];
        read(pipe_from_child[0], buffer, sizeof(buffer));
        close(pipe_from_child[0]);

        int status;
        waitpid(pid, &status, 0); // Wait for the child to finish
        return std::string(buffer);
    }
}

// Test ToLowerCase function
TEST(UtilsTests, ToLowerCaseTest) {
    char str[] = "HeLLo WoRLd!";
    ToLowerCase(str);
    EXPECT_STREQ(str, "hello world!");
}

// Test ReplaceSpacesWithUnderscore function
TEST(UtilsTests, ReplaceSpacesWithUnderscoreTest) {
    char str[] = "Hello World!";
    ReplaceSpacesWithUnderscore(str);
    EXPECT_STREQ(str, "Hello_World!");
}

// Test Child1 functionality
TEST(ChildProcessTests, Child1LowerCaseTest1) {
    const char *input = "Hello WORLD!";
    std::string result =
        SimulateChildProcess("/workspaces/OSystems/build/lab1/child1", input);
    EXPECT_EQ(result, "hello world!");
}

TEST(ChildProcessTests, Child1LowerCaseTest2) {
    const char *input = "1 2 3 4 5";
    std::string result =
        SimulateChildProcess("/workspaces/OSystems/build/lab1/child1", input);
    EXPECT_EQ(result, "1 2 3 4 5");
}

TEST(ChildProcessTests, Child1LowerCaseTest3) {
    const char *input = "A B C d e    f";
    std::string result =
        SimulateChildProcess("/workspaces/OSystems/build/lab1/child1", input);
    EXPECT_EQ(result, "a b c d e    f");
}

TEST(ChildProcessTests, Child1LowerCaseTest4) {
    const char *input = "";
    std::string result =
        SimulateChildProcess("/workspaces/OSystems/build/lab1/child1", input);
    EXPECT_EQ(result, "");
}

// Test Child2 functionality
TEST(ChildProcessTests, Child2ReplaceSpacesTest1) {
    const char *input = "hello world!";
    std::string result =
        SimulateChildProcess("/workspaces/OSystems/build/lab1/child2", input);
    EXPECT_EQ(result, "hello_world!");
}

TEST(ChildProcessTests, Child2ReplaceSpacesTest2) {
    const char *input = "a a a a a a a a";
    std::string result =
        SimulateChildProcess("/workspaces/OSystems/build/lab1/child2", input);
    EXPECT_EQ(result, "a_a_a_a_a_a_a_a");
}

TEST(ChildProcessTests, Child2ReplaceSpacesTest3) {
    const char *input = "          ";
    std::string result =
        SimulateChildProcess("/workspaces/OSystems/build/lab1/child2", input);
    EXPECT_EQ(result, "__________");
}

TEST(ChildProcessTests, Child2ReplaceSpacesTest4) {
    const char *input = "";
    std::string result =
        SimulateChildProcess("/workspaces/OSystems/build/lab1/child2", input);
    EXPECT_EQ(result, "");
}

void SimulateInputOutputForParent(const std::string &testInput,
                                  std::string &output) {
    // Redirect input
    std::istringstream inputStream(testInput);
    std::streambuf *originalCinBuffer = std::cin.rdbuf(inputStream.rdbuf());
    // Redirect output
    std::ostringstream outputStream;
    std::streambuf *originalCoutBuffer = std::cout.rdbuf(outputStream.rdbuf());

    Parent("/workspaces/OSystems/build/lab1/child1",
           "/workspaces/OSystems/build/lab1/child2");

    // Restore input
    std::cin.rdbuf(originalCinBuffer);
    // Restore output
    std::cout.rdbuf(originalCoutBuffer);
    output = outputStream.str();
    // Remove hints from output
    size_t pos = output.find("Enter your text: ");
    if (pos != std::string::npos) {
        output.erase(pos, strlen("Enter your text: "));
    }
}

TEST(ParentChildIntegrationTests, ParentChild1Child2Test1) {
    std::string input = "Hello World";
    std::string output;
    SimulateInputOutputForParent(input, output);
    EXPECT_EQ(output, "hello_world\n");
}

TEST(ParentChildIntegrationTests, ParentChild1Child2Test2) {
    std::string input = "A_A aaa   bb cd ";
    std::string output;
    SimulateInputOutputForParent(input, output);
    EXPECT_EQ(output, "a_a_aaa___bb_cd_\n");
}

TEST(ParentChildIntegrationTests, ParentChild1Child2Test3) {
    std::string input = " ";
    std::string output;
    SimulateInputOutputForParent(input, output);
    EXPECT_EQ(output, "_\n");
}

TEST(ParentChildIntegrationTests, ParentChild1Child2Test4) {
    std::string input = "";
    std::string output;
    SimulateInputOutputForParent(input, output);
    EXPECT_EQ(output, "\n");
}

// Main entry point for tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
