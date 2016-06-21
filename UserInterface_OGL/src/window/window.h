#pragma once
#include <common.h>
#include <vector>

namespace ho {

	class HO_API Window
	{
	public:
		virtual ~Window() {}

		virtual void InitOpenGL() = 0;
		virtual void HandleMessages() = 0;
		virtual void ContextSwap() = 0;
		virtual void EnableVsync() = 0;
		virtual void DisableVsync() = 0;

		virtual void SubscribeResizeEvent(bool*) = 0;

		inline static  Window& GetCurrentWindow() { return *m_CurrentWindow; }
		inline const int GetWidth()const { return m_Width; }
		inline const int GetHeight()const { return m_Height; }
		inline void SetWidth(int width) { m_Width = width; }
		inline void SetHeight(int height) { m_Height = height; }
		inline const char* GetWindowTitle() const { return m_WindowTitle; }
		inline void SetAppCloseState(bool* state) { this->m_appCloseState = state; }

		std::vector<bool*> m_ResizeSubs;
	protected:
		Window(const char* windowTitle, int m_Width, int m_Height);
		static Window* m_CurrentWindow;

		const char* m_WindowTitle;
		int m_Width, m_Height;
		bool* m_appCloseState;
	};

}