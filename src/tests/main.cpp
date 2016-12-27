/**
 * @file	main.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

/* -- Includes -- */

#include <gtest/gtest.h>

/* -- Test Case -- */

TEST(SampleTestCase, ShouldPass)
{
  ASSERT_EQ(1, 1);
  ASSERT_EQ(2, 2);
}

TEST(SampleTestCase, ShouldFail)
{
  ASSERT_EQ(1, 2);
  ASSERT_EQ(2, 1);
}

/* -- Procedures -- */

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
