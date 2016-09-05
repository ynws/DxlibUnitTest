#include "stdafx.h"
#include <gtest/gtest.h>

TEST(GTestSample, Assert) {
	EXPECT_EQ(1, 1);
}

TEST(GTestSample, AssertNGSample) {
	EXPECT_EQ(2, 3);
}