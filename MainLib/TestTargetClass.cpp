#include "stdafx.h"
#include "TestTargetClass.h"

TestTargetClass::TestTargetClass(Dx * dxlib) : dxlib(dxlib)
{
}

TestTargetClass::~TestTargetClass()
{
}

int TestTargetClass::GetNumber()
{
	return 100;
}

int TestTargetClass::ifElseTest(int n)
{
	if (n == 0) {
		return 0;
	}
	if (n == 1)return 1;
	if (n == 2 || n == 3) {
		return n;
	}
	if (n >= 10 && n <= 20) {
		return 15;
	}
	return 0;
}

int TestTargetClass::NotTestCode()
{
	return 0;
}

void TestTargetClass::DrawTestString()
{
	dxlib->DrawString(0, 0, "test", 0);
}
