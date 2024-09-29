#include "../lab1/include/parent.hpp"
#include "../lab1/include/utils.hpp"
#include <fcntl.h>
#include <gtest/gtest.h>
#include <unistd.h>

// Helper function to simulate pipes and return data for testing child
// processes.
std::string simulateChildProcess(const char *childPath, const char *inputData) {
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
TEST(ChildProcessTests, Child1LowerCaseTest) {
    const char *input = "Hello WORLD!";
    std::string result =
        simulateChildProcess("/workspaces/OSystems/build/lab1/child1", input);
    EXPECT_EQ(result, "hello world!");
}

// Test Child2 functionality
TEST(ChildProcessTests, Child2ReplaceSpacesTest) {
    const char *input = "hello world!";
    std::string result =
        simulateChildProcess("/workspaces/OSystems/build/lab1/child2", input);
    EXPECT_EQ(result, "hello_world!");

    input = "a a a a a a a a";
    result =
        simulateChildProcess("/workspaces/OSystems/build/lab1/child2", input);
    EXPECT_EQ(result, "a_a_a_a_a_a_a_a");
}

void redirectInputOutput(const std::string &input, std::string &output) {
    // Save the original stdin and stdout
    int original_stdin = dup(STDIN_FILENO);
    int original_stdout = dup(STDOUT_FILENO);

    // Create temporary pipes for stdin and stdout
    int pipe_in[2];
    int pipe_out[2];
    pipe(pipe_in);
    pipe(pipe_out);

    // Redirect stdin
    write(pipe_in[1], input.c_str(), input.size());
    close(pipe_in[1]);              // Close write end after writing
    dup2(pipe_in[0], STDIN_FILENO); // Redirect stdin to read end of the pipe
    close(pipe_in[0]);

    // Redirect stdout
    dup2(pipe_out[1],
         STDOUT_FILENO); // Redirect stdout to write end of the pipe
    close(pipe_out[1]);

    // Call the parent process (this will now read from our redirected stdin and
    // write to stdout)
    Parent("/workspaces/OSystems/build/lab1/child1",
           "/workspaces/OSystems/build/lab1/child2");

    // Capture the output
    char buffer[256];
    ssize_t bytes_read = read(pipe_out[0], buffer, sizeof(buffer));
    buffer[bytes_read] = '\0';
    output = std::string(buffer);

    // Restore the original stdin and stdout
    dup2(original_stdin, STDIN_FILENO);
    dup2(original_stdout, STDOUT_FILENO);
    close(original_stdin);
    close(original_stdout);
}

TEST(ParentChildIntegrationTests, ParentChild1Child2Test) {
    std::string input = "Hello World!"; // Simulated input
    std::string output;

    // Redirect input and output for the parent-child pipeline
    redirectInputOutput(input, output);

    // Remove "Enter your text: " from the captured output
    size_t pos = output.find("Enter your text: ");
    if (pos != std::string::npos) {
        output.erase(pos, strlen("Enter your text: "));
    }

    EXPECT_EQ(output, "hello_world!\n");
}

// Main entry point for tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
