#include <iostream>
#include "gtest/gtest.h"

using namespace std;

int main(int argc, char **argv) {
  // ::testing::GTEST_FLAG(output) = "xml:/home/user/test.xml";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

