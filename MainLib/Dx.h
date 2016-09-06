#pragma once
#include <string>

class Dx
{
public:
	virtual ~Dx() {};
	virtual int DrawString(int x, int y, std::string str, unsigned int Color) = 0;
};

