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
	void DrawTestString();
};

