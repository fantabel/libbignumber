#include <gtest/gtest.h>
#include "BigIntegerLibrary.hh"

TEST(NumberLikeArray, Constructor) {
  EXPECT_EQ(0, 0);
  NumberlikeArray<int> a;
  std::cout << a.toString();
  std::cout << a.toString();
}
