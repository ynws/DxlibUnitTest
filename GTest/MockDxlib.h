#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "..\MainLib\Dx.h"

class MockDxlib : public Dx {
public:
	MOCK_METHOD4(DrawString, int(int x, int y, std::string str, unsigned int Color));
};