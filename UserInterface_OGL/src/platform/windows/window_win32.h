#pragma once
#include <common.h>
#include <windows.h>
#include "window/window.h"

namespace ho {

	class HO_API WindowWin32 : public Window
	{
	public:
		WindowWin32(int nCmdShow, HINSTANCE hInstance, int width, int height, const char* className, const char* windowTitle);
		virtual ~WindowWin32() {}

		virtual void InitOpenGL();
		virtual void HandleMessages();
		virtual void ContextSwap();
		virtual void EnableVsync();
		virtual void DisableVsync();

		virtual void SubscribeResizeEvent(bool*);

	private:
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		// Data
		HWND m_hWnd;
		HDC m_hDC;
		HGLRC m_hRC;
		HINSTANCE m_hInstance;
		WNDCLASSEX m_wcex;
		MSG m_Msg;

	public:
		// Getters and Setters
		inline HDC GetHDC() const { return this->m_hDC; }
		inline MSG GetMsg() const { return this->m_Msg; }

	private:
		// Not copyable
		WindowWin32(WindowWin32& w) = delete;
		WindowWin32& operator=(WindowWin32& w) = delete;
	};

}