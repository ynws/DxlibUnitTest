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

int TestTargetClass::NotTestCode()
{
	return 0;
}

void TestTargetClass::DrawTestString()
{
	dxlib->DrawString(0, 0, "test", 0);
}
