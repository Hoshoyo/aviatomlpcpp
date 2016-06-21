#pragma once
#include <common.h>
#include "platform/platform.h"
#include "graphics/renderengine.h"

namespace ho {

	class HO_API Application
	{
	public:
		Application(Window* window, const char* name);
		~Application();

		void Update();
		void Run(uint fps, uint tickSpeed);

		inline bool IsRunning()const { return m_isRunning; }
		inline graphics::RenderEngine* GetRenderEngine() { return m_RenderEngine; }
	private:
		bool m_isRunning;
		bool m_shouldClose;

		uint m_FPS;
		graphics::RenderEngine* m_RenderEngine;
	protected:
		const char* m_AppName;
		Window* m_Window;

	};

}