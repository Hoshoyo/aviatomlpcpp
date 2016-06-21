#pragma once
#include <common.h>
#include "graphics/entities/Irenderable.h"
#include <GL/glew.h>

namespace ho {
namespace graphics {

	class HO_API Line : public Renderable
	{
	private:
		glm::vec3 line_segment;
		const float force_display_quotient = 4.0f;
		const float initial_x = -300.0f;
		const float initial_y = 100.0f;

	public:

		virtual void Render()
		{
			glBegin(GL_LINES);
			glVertex3f(line_segment.x, line_segment.y, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glEnd();
		}

		void UpdateLine(float force)
		{
			line_segment.x = initial_x * force / force_display_quotient;
			line_segment.y = initial_y * force / force_display_quotient;
			line_segment.z = 0.0f;
		}

	};

}}