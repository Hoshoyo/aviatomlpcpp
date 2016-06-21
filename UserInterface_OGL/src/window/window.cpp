#include "window.h"

namespace ho {

Window* Window::m_CurrentWindow = nullptr;

Window::Window(const char* windowTitle, int width, int height)
	: m_WindowTitle(windowTitle), m_Width(width), m_Height(height)
{ }

}