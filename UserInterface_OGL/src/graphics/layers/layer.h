#pragma once
#include <common.h>
#include <string>
#include <vector>

#include "graphics/shader/shader.h"

namespace ho {
namespace graphics {

	class HO_API Layer
	{
	public:
		virtual ~Layer(){}
		virtual void Render() = 0;
		virtual void Update() = 0;

		inline Shader& GetShader() { return *m_Shader; }
	protected:
		Shader* m_Shader;
	};

}}