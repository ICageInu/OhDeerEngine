#include "OhDeerPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "OhDeer.h"

int main(int, char*[]) {
	OhDeerEngine::OhDeerEngine engine;
	engine.Run();
    return 0;
}