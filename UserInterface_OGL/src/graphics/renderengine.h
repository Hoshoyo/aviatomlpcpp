#pragma once
#include <common.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "layers/layer.h"

namespace ho {
namespace graphics {

	class HO_API RenderEngine
	{
	public:
		RenderEngine();
		~RenderEngine();
		void Render();
		void Update();

		void SetClearColor(uint color);
		void SetClearColor(glm::vec4& color);
		
		void PopLayer();
		void PushLayer(Layer* layer);

		bool running;
	private:
		bool handleResize;
		std::vector<Layer*> layers;
	};

}}


