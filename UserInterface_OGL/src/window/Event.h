#pragma once
#include <common.h>
#include <list>

namespace ho {

	class HO_API Event
	{
	public:
		Event();
		~Event();
		static std::list<Event> events;

	private:

	};

}

