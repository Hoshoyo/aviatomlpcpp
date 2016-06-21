#include <common.h>
#include "platform/platform.h"
#include "application.h"
#include "graphics/layers/layer2d.h"
#include "graphics/layers/menu.h"
#include "system/memory.h"
#include "game/game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	using namespace ho;

#if 1
	Debug debugger;		// Alocate console for debugging
#endif

	Application app(honew WindowWin32(nCmdShow, hInstance, 1200, 720, "HoWindowAPI", "Aviato"), "Aviato");

	game::Game* game = honew game::Game();

	graphics::Layer2D* l = honew graphics::Layer2D(game);
	graphics::Menu* m = honew graphics::Menu();
	app.GetRenderEngine()->PushLayer(l);
	app.GetRenderEngine()->PushLayer(m);

	app.Run(60, 60);

	hodelete l;
	hodelete m;
	hodelete game;

	return ((const WindowWin32&)Window::GetCurrentWindow()).GetMsg().wParam;
}
