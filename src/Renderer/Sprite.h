#pragma once

#include <glad/glad.h>
#include <memory>
#include <glm/vec2.hpp>
#include <string>

#include "VertexBuffer.h";
#include "IndexBuffer.h";
#include "VertexArray.h"

namespace RenderEngine
{
	class Texture2D;
	class ShaderProgram;

	class Sprite
	{

	public:
		struct FrameDescription
		{
			FrameDescription(const glm::vec2 _leftBottomUV, glm::vec2 _rightTopUV, double _duration)
				:leftBottomUV(_leftBottomUV),
				rightTopUV(_rightTopUV),
				duration(_duration)
			{

			}

			glm::vec2 leftBottomUV;
			glm::vec2 rightTopUV;
			double duration;
		};


		Sprite(std::shared_ptr<Texture2D> pTexture,
			std::string initialSubTexture,
			std::shared_ptr<ShaderProgram> pShaderProgram
		);
		~Sprite();

		Sprite(const Sprite&) = delete;
		Sprite& operator = (Sprite&) = delete;

		void render(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer = 0, const size_t frameId = 0) const;

		void insertFrames(std::vector<FrameDescription> framesDescription);
		double getFrameDuration(const double frameId) const;
		size_t getFramesCount();

	protected:
		std::shared_ptr<Texture2D> m_pTexture;
		std::shared_ptr<ShaderProgram> m_pShaderProgram;

		VertexArray m_vertexArray;
		VertexBuffer m_vertexCoordsBuffer;
		VertexBuffer m_textureCoordsBuffer;
		IndexBuffer m_indexBuffer;

		std::vector<FrameDescription> m_framesDescription;
		mutable size_t m_lastFrameId;
	};
}