#pragma once
#include <windows.h>
#include <common.h>

namespace ho {

	class HO_API Timer
	{
	public:
		Timer() 
		{
			g_timerInitialized = false;
		}
	private:
		double g_freq;
		bool g_timerInitialized;

		double m_start;
	public:
		double GetTime()
		{
			if (!g_timerInitialized)
			{
				LARGE_INTEGER li;
				QueryPerformanceFrequency(&li);

				g_freq = double(li.QuadPart);
				g_timerInitialized = true;
			}

			LARGE_INTEGER li;
			QueryPerformanceCounter(&li);

			return double(li.QuadPart) / g_freq;
		}

		void StartTimer()
		{
			m_start = GetTime();
		}

		double ElapsedTime()
		{
			return GetTime() - m_start;
		}
	};

}