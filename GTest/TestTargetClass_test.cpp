#include "stdafx.h"

#include "MockDxlib.h"
#include "../MainLib/TestTargetClass.h"

TEST(TestTargetClass, GetNumber) {
	EXPECT_EQ(100, TestTargetClass::GetNumber());
}

TEST(TestTargetClass, Dxlib) {
	MockDxlib mockDx;
	EXPECT_CALL(mockDx, DrawString(0, 0, "test", 0)).Times(1);

	TestTargetClass target(&mockDx);
	target.DrawTestString();
}
TEST(TestTargetClass, ifelse) {
	EXPECT_EQ(0, TestTargetClass::ifElseTest(100));
}
