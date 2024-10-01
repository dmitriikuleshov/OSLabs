#include "parent.hpp"

int main() {
    const char *PATH_TO_CHILD1 = getenv("PATH_TO_CHILD1");
    const char *PATH_TO_CHILD2 = getenv("PATH_TO_CHILD2");
    Parent(PATH_TO_CHILD1, PATH_TO_CHILD2);
    return 0;
}