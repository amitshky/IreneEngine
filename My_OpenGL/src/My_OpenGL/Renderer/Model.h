#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "Mesh.h"

namespace myo {

	class Model
	{
	public:
		Model(const std::string& path, bool gamma = false);
		~Model() {}
		void Draw(Ref<Shader>& shader);

	private:
		std::vector<Ref<Texture2D>> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
		void LoadModel(const std::string& path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	private:
		std::vector<Mesh> m_Meshes;
		std::vector<Ref<Texture2D>> m_TexturesLoaded;
		std::string m_Directory;
		bool m_GammaCorrection;

		std::vector<Texture> m_TexturesLoaded2;
	};

}
