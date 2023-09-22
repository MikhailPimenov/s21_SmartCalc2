#include <gtest/gtest.h>

int main(int argument_counter, char **arguments) {
  ::testing::InitGoogleTest(&argument_counter, arguments);
  return RUN_ALL_TESTS();
}