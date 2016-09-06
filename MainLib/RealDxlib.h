#pragma once
#include "Dx.h"
class RealDxlib :
	public Dx
{
public:
	RealDxlib();
	~RealDxlib();
	int DrawString(int x, int y, std::string str, unsigned int Color);
};

