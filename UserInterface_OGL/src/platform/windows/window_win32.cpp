#include "window_win32.h"
#include "system/log.h"
#include "window/input.h"
#include <GL/glew.h>
#include <GL/wglew.h>

namespace ho {

WindowWin32::WindowWin32(int nCmdShow, HINSTANCE hInstance,
	int width, int height, const char* className, const char* windowTitle)
	: Window(windowTitle, width, height), m_hInstance(hInstance)
{
	// Register Class
	m_wcex.cbSize = sizeof(WNDCLASSEX);
	m_wcex.style = CS_HREDRAW | CS_VREDRAW;
	m_wcex.lpfnWndProc = WndProc;
	m_wcex.cbClsExtra = 0;
	m_wcex.cbWndExtra = 0;
	m_wcex.hInstance = hInstance;
	m_wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(0));
	m_wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	m_wcex.lpszMenuName = NULL;
	m_wcex.lpszClassName = className;
	m_wcex.hIconSm = LoadIcon(m_wcex.hInstance, MAKEINTRESOURCE(IDI_ERROR));

	if (!RegisterClassEx(&m_wcex))
		log::fatal("Error registering window class.");


	// Adjust size of window
	RECT wr = { 0, 0, width, height };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	m_hWnd = CreateWindowEx(
		NULL,
		className,
		m_WindowTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL, NULL, m_hInstance, NULL
		);

	if (!m_hWnd)
		log::fatal("Error creating the window.");

	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	Window::m_CurrentWindow = this;
}

void WindowWin32::InitOpenGL()
{
	int PixelFormat;
	m_hDC = GetDC(m_hWnd);

	PIXELFORMATDESCRIPTOR pfd;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	pfd.cDepthBits = 32;
	pfd.cColorBits = 24;
	pfd.iPixelType = PFD_TYPE_RGBA;

	PixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	if (!SetPixelFormat(m_hDC, PixelFormat, &pfd))
		log::fatal("Error initializing OpenGL");

	m_hRC = wglCreateContext(m_hDC);		// Create the context
	wglMakeCurrent(m_hDC, m_hRC);			// Make the context current

	glewExperimental = true;
	GLenum err = glewInit();
	if (err != GLEW_OK)
		log::fatal("Error initializing GLEW.");

	EnableVsync();							// Vsync Enabled by default
}

LRESULT CALLBACK WindowWin32::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
		//std::cout << LOWORD(lParam) << " " << HIWORD(lParam) << std::endl;
		Input::mouse_pos = glm::vec2(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		SetCapture(hWnd);
		Input::SetLeftMouse(true);
		break;
	case WM_LBUTTONUP:
		ReleaseCapture();
		Input::SetLeftMouse(false);
		Input::left_click = true;
		break;
	case WM_KEYDOWN:
		//log::print(wParam);
		if(wParam < NUM_KEYS)
			Input::Keys[wParam] = true;
		break;
	case WM_KEYUP:
		if (wParam < NUM_KEYS)
			Input::Keys[wParam] = false;
		break;
	case WM_CHAR:
		//std::cout << lParam << std::endl;
		//std::cout << (char)wParam;
		break;
	case WM_SIZE:
		if (m_CurrentWindow)
		{
			m_CurrentWindow->SetWidth(LOWORD(lParam));
			m_CurrentWindow->SetHeight(HIWORD(lParam));

			for (auto subs : m_CurrentWindow->m_ResizeSubs)
				*subs = true;
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}

void WindowWin32::HandleMessages()
{
	while (PeekMessage(&m_Msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		if (m_Msg.message == WM_QUIT)
			*m_appCloseState = true;
		TranslateMessage(&m_Msg);
		DispatchMessage(&m_Msg);
	}
}

void WindowWin32::ContextSwap()
{
	SwapBuffers(m_hDC);
}

void WindowWin32::EnableVsync()
{
	wglSwapIntervalEXT(1);
}

void WindowWin32::DisableVsync()
{
	wglSwapIntervalEXT(0);
}

void WindowWin32::SubscribeResizeEvent(bool* e)
{
	m_ResizeSubs.push_back(e);
}

}	// namespace ho