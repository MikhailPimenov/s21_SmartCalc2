// #include <gtest/gtest.h>
#include "../googletest_build/include/gtest/gtest.h"

// GCOVR_EXCL_START

int main(int argument_counter, char **arguments) {
  ::testing::InitGoogleTest(&argument_counter, arguments);
  return RUN_ALL_TESTS();
}

// GCOVR_EXCL_STOP