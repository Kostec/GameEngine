#pragma once

#include "ShaderProgram.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include <string>

namespace RenderEngine
{
	class Renderer
	{
	public:
		static void draw(const VertexArray& VertexArray, const IndexBuffer& indexBuffer, const ShaderProgram& shader);
		static void setClearColor(float r, float g, float b, float a);
		static void setDepth(const bool enable);
		static void clear();
		static void setVieport(unsigned int width, unsigned int height, unsigned int leftOffset = 0, unsigned int bottomOffset = 0);
		static std::string getRendererStr();
		static std::string getVersionStr();
	};

}