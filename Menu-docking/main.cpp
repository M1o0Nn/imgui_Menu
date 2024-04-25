#include <Windows.h>
#include "Imgui.hpp"

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	bool enable = true;
	CreateWnd(hInst, &enable);
	return 0;
}