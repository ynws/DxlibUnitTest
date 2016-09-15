#include "stdafx.h"
#include "DxLib.h"
#include "TestTargetClass.h"
#include "RealDxlib.h"

#ifndef _ROGEBREAZ_TEST
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);
	SetBackgroundColor(255, 255, 255);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	RealDxlib dxlib;
	TestTargetClass target(&dxlib);

	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		target.DrawTestString();
		ScreenFlip();
	}

	DxLib_End();
	return 0;
}
#endif