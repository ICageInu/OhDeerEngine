#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif
#include <SDL.h>
#include "OhDeer.h"
#include "MainGame.h"

#undef main
//int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) 
int main()
{
	MainGame engine;
	engine.Run();
	return 0;
}