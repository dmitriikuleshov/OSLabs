#include "parent.hpp"
#include "utils.hpp"
#include <fcntl.h>
#include <gtest/gtest.h>
#include <unistd.h>

const char *PATH_TO_CHILD1 = getenv("PATH_TO_CHILD1");
const char *PATH_TO_CHILD2 = getenv("PATH_TO_CHILD2");

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

void SimulateInputOutputForParent(const std::string &testInput,
                                  std::string &output) {
    // Redirect input
    std::istringstream inputStream(testInput);
    std::streambuf *originalCinBuffer = std::cin.rdbuf(inputStream.rdbuf());
    // Redirect output
    std::ostringstream outputStream;
    std::streambuf *originalCoutBuffer = std::cout.rdbuf(outputStream.rdbuf());

    Parent(PATH_TO_CHILD1, PATH_TO_CHILD2);

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

void RunParentChildIntegrationTest(const std::string &input,
                                   const std::string &expectedOutput) {
    std::string output;
    SimulateInputOutputForParent(input, output);
    EXPECT_EQ(output, expectedOutput);
}

TEST(ParentChildIntegrationTests, ParentChild1Child2Test1) {
    RunParentChildIntegrationTest("Hello World", "hello_world\n");
}

TEST(ParentChildIntegrationTests, ParentChild1Child2Test2) {
    RunParentChildIntegrationTest("1 2 3 4 5 6", "1_2_3_4_5_6\n");
}

TEST(ParentChildIntegrationTests, ParentChild1Child2Test3) {
    RunParentChildIntegrationTest("A_A aaa   bb cd ", "a_a_aaa___bb_cd_\n");
}

TEST(ParentChildIntegrationTests, ParentChild1Child2Test4) {
    RunParentChildIntegrationTest(" ", "_\n");
}

TEST(ParentChildIntegrationTests, ParentChild1Child2Test5) {
    RunParentChildIntegrationTest("", "\n");
}
// Main entry point for tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
