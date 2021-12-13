#include "Sprite.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Renderer.h"

#include "glm//mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace RenderEngine
{
	Sprite::Sprite(std::shared_ptr<Texture2D> pTexture,
					std::string initialSubTexture,
					std::shared_ptr<ShaderProgram> pShaderProgram)
		: m_pTexture(std::move(pTexture)),
		m_pShaderProgram(std::move(pShaderProgram)),
		m_lastFrameId(0)
	{
		const GLfloat vertexCoords[] = {
			//1  2	   
			//| /|
			//0  3			
			//X  Y
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,
		};

		auto subTexture = m_pTexture->getSubTexture(std::move(initialSubTexture));

		const GLfloat textureCoords[] = {
			//U   V
			subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
		};

		const GLuint indexes[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_vertexCoordsBuffer.init(vertexCoords, 2 * 4 * sizeof(GLfloat));
		VertexBufferLayout vertexCoordsLayout;
		vertexCoordsLayout.addElementLayoutFloat(2, false);
		m_vertexArray.addBuffer(m_vertexCoordsBuffer, vertexCoordsLayout);

		m_textureCoordsBuffer.init(textureCoords, 2 * 4 * sizeof(GLfloat));
		VertexBufferLayout textureCoordsLayout;
		textureCoordsLayout.addElementLayoutFloat(2, false);
		m_vertexArray.addBuffer(m_textureCoordsBuffer, textureCoordsLayout);

		m_indexBuffer.init(indexes, 6);

		m_vertexArray.unbind();
		m_indexBuffer.unbind();
	}

	Sprite::~Sprite()
	{
		
	}

	void Sprite::render(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer, const size_t frameId) const
	{
		if (m_lastFrameId != frameId)
		{
			m_lastFrameId = frameId;

			const FrameDescription& currentFrameDescription = m_framesDescription[frameId];

			const GLfloat textureCoords[] = {
				//U   V
				currentFrameDescription.leftBottomUV.x, currentFrameDescription.leftBottomUV.y,
				currentFrameDescription.leftBottomUV.x, currentFrameDescription.rightTopUV.y,
				currentFrameDescription.rightTopUV.x, currentFrameDescription.rightTopUV.y,
				currentFrameDescription.rightTopUV.x, currentFrameDescription.leftBottomUV.y,
			};

			m_textureCoordsBuffer.update(textureCoords, 2 * 4 * sizeof(GLfloat));
		}


		m_pShaderProgram->use();

		glm::mat4 model(1.f);
		model = glm::translate(model, glm::vec3(position, 0.f));
		model = glm::translate(model, glm::vec3(size.x / 2.f, size.y / 2.f, 0.f));
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));
		model = glm::translate(model, glm::vec3(-size.x / 2.f, -size.y / 2.f, 0.f));
		model = glm::scale(model, glm::vec3(size, 1.f));

		//m_vertexArray.bind();
		m_pShaderProgram->setMatrix4("modelMat", model);
		m_pShaderProgram->setFloat("layer", layer);

		glActiveTexture(GL_TEXTURE0);
		m_pTexture->bind();

		/*glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		m_vertexArray.unbind();*/

		Renderer::draw(m_vertexArray, m_indexBuffer, *m_pShaderProgram);
	}

	void Sprite::insertFrames(std::vector<FrameDescription> framesDescription)
	{
		m_framesDescription = std::move(framesDescription);
	}

	double Sprite::getFrameDuration(const double frameId) const
	{
		return m_framesDescription[frameId].duration;
	}

	size_t Sprite::getFramesCount()
	{
		return m_framesDescription.size();
	}

}