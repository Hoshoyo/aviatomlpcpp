#include "application.h"
#include "platform/platform.h"
#include "system/log.h"
#include "system/memory.h"

namespace ho {

Application::Application(Window* window, const char* name)
	: m_Window(window), m_AppName(name)
{ 
	m_Window->InitOpenGL();
	m_isRunning = true;
	m_shouldClose = false;
	window->SetAppCloseState(&m_shouldClose);
	m_RenderEngine = honew graphics::RenderEngine();
}

Application::~Application()
{
	hodelete m_Window;
	hodelete m_RenderEngine;
}

void Application::Update()
{
	m_Window->HandleMessages();
	m_RenderEngine->Update();
}

void Application::Run(uint fps, uint tickSpeed)
{
	Timer timer, renderTimer;
	double gametime = 0;
	double rendertime = 0;
	double fpscounter = 0;
	double sumrendertime = 0;
	m_FPS = 60;

	while (!m_shouldClose)
	{
		double elapsed = timer.ElapsedTime();
		gametime += elapsed;
		fpscounter += elapsed;
		rendertime += elapsed;

		if (!m_RenderEngine->running)
			return;

		timer.StartTimer();
		
		if (fpscounter >= 1.0)
		{
#ifdef _DEBUG
			std::cout <<  "FPS: " << m_FPS << ", Render time(ms):" << sumrendertime*1000 / m_FPS << std::endl;
#endif
			sumrendertime = 0;
			fpscounter = 0;
			m_FPS = 0;
		}

		// Game and Input update
		if (gametime >= 1.0 / tickSpeed)
		{
			Update();
		}

		// Game render
		if (rendertime >= 1.0 / (fps + 10))
		{		
			rendertime = 0;
			renderTimer.StartTimer();
			m_RenderEngine->Render();
			sumrendertime += renderTimer.ElapsedTime();
			m_FPS++;
		}

		m_Window->ContextSwap();
	}
}

}