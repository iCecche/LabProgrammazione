#include "gtest/gtest.h"

TEST(Note, test1) {
    ASSERT_EQ (0.0, (0.0));     // success
    EXPECT_EQ (9.0, (3.0*2.0)); // fail, test continues
}

TEST(Note, test2) {
    ASSERT_EQ (0.0, (0.0));     // success
}