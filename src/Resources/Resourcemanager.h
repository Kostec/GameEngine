#pragma once
#include <string>
#include <memory>
#include <map>
#include <vector>

namespace RenderEngine
{
	class ShaderProgram;
	class Texture2D;
	class Sprite;
}

class ResourceManager
{
public:
	// @executablePath - ���� � ����� � .exe
	//ResourceManager(const std::string& executablePath);
	static void setExecutablePath(const std::string& executablePath);
	static void unloadAllResources();


	~ResourceManager() = delete;
	ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator = (const ResourceManager&) = delete;
	ResourceManager& operator = (const ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	static std::shared_ptr<RenderEngine::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexpath, const std::string& fragmentPath);
	static std::shared_ptr<RenderEngine::ShaderProgram> getShaderProgram(const std::string& shaderName);

	static std::shared_ptr<RenderEngine::Texture2D> loadTexture(const std::string& textureName, const std::string& texturepath);
	static std::shared_ptr<RenderEngine::Texture2D> getTexture(const std::string& textureName);

	static std::shared_ptr<RenderEngine::Sprite> loadSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const std::string& subTextureName = "DefaultSubTexture");
	static std::shared_ptr<RenderEngine::Sprite> getSprite(const std::string& spriteName);

	static std::shared_ptr<RenderEngine::Texture2D> loadTextureAtlas(const std::string textureName,
		const std::string texturePath,
		std::vector<std::string> subTextures,
		const unsigned int subTextureWidth,
		const unsigned int subTextureHeight);

	static bool loadJSONResources(const std::string& JSONpath);

	static const std::vector<std::vector<std::string>>& getlevels() { return m_levels; }

private:
	static std::string getFileString(const std::string& relativeFilePath);
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgram>> ShaderProgramsMap;
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>> TexturesMap;
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> SpritesMap;

	static ShaderProgramsMap m_sharedPrograms;
	static TexturesMap m_textures;
	static SpritesMap m_sprites;

	static std::vector<std::vector<std::string>> m_levels;

	static std::string m_path;
};