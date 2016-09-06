#include "stdafx.h"
#include "RealDxlib.h"
#include "DxLib.h"

RealDxlib::RealDxlib()
{
}


RealDxlib::~RealDxlib()
{
}

int RealDxlib::DrawString(int x, int y, std::string str, unsigned int Color)
{
	return DxLib::DrawString(x, y, str.c_str(), Color);
}
