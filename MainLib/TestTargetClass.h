#pragma once
#include "Dx.h"
class TestTargetClass
{
private:
	Dx* dxlib;
public:
	TestTargetClass(Dx* dxlib);
	~TestTargetClass();

	static int GetNumber();
	static int ifElseTest(int n);
	static int NotTestCode();
	void DrawTestString();
};

