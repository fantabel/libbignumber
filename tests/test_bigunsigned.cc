#include <climits>
#include <gtest/gtest.h>
#include "BigIntegerLibrary.hh"

TEST(BigUnsigned, Constructor) {

  EXPECT_EQ(BigInteger(0), 0);
  EXPECT_EQ(BigInteger(1), 1);
  EXPECT_EQ(BigInteger(10), 10);

  EXPECT_EQ(BigInteger(), 0);

  BigUnsigned::Blk myBlocks[3];

  myBlocks[0] = 3;
  myBlocks[1] = 4;
  myBlocks[2] = 0;
  BigUnsigned bu(myBlocks, 3);

  if (bu == 17179869187) {
    std::cout << "egaux" << std::endl;
  }

  try {
    std::cout << "Depart " << std::endl << bu.toString() << std::endl;
    EXPECT_EQ(10, bu.toUnsignedLongLong());
  } catch (char const* s) {
    //std::cout << "Exception " << s << std::endl;
  }

}

TEST(BigUnsigned, Destructor) {
  EXPECT_TRUE(true);
}

