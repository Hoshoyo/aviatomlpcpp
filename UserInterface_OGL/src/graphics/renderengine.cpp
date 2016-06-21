#include "renderengine.h"
#include "platform/platform.h"
#include "system/memory.h"
#include "layers/layer2d.h"
#include "layers/menu.h"

namespace ho {
namespace graphics{

	RenderEngine::RenderEngine()
	{
		SetClearColor(0xaabbccff);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_CCW);
		running = true;
	}

	RenderEngine::~RenderEngine()
	{
	}

	void RenderEngine::Render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		if (((Menu*)layers[1])->quit_game)
		{
			running = false;
			return;
		}

		for (int i = layers.size() - 1; i >= 0; --i)
		{
			if (((Menu*)layers[1])->start_game)
			{
				if (i == 1)
					continue;
			}
			else
			{
				if (i == 0)
					continue;
			}
			if (((Layer2D*)layers[0])->winner != -1)
			{
				log::print(((Layer2D*)layers[0])->winner);
				((Menu*)layers[1])->start_game = false;
				((Menu*)layers[1])->SwitchMenuTexture(((Layer2D*)layers[0])->winner);
				((Layer2D*)layers[0])->winner = -1;
			}
			layers[i]->Update();
			layers[i]->Render();
		}
	}

	void RenderEngine::Update()
	{
	}

	void RenderEngine::PushLayer(Layer* layer)
	{
		layers.push_back(layer);
	}

	void RenderEngine::PopLayer()
	{
		layers.pop_back();
	}

	void RenderEngine::SetClearColor(uint color)
	{
		float red = (color >> 24 & 0xff) / 255.0f;
		float green = (color >> 16 & 0xff) / 255.0f;
		float blue = (color >> 8 & 0xff) / 255.0f;
		float alpha = (color & 0xff) / 255.0f;

		glClearColor(red, green, blue, alpha);
	}

	void RenderEngine::SetClearColor(glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
}}

