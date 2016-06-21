#pragma once
#include <common.h>
#include "graphics/entities/transform.h"

namespace ho {
namespace graphics {

	class HO_API Renderable
	{
	public:
		virtual void Render() = 0;
	};

}}