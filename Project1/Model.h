#pragma once
#include <glm/glm.hpp>
#include <string>
#include<vector>
#include"Shader.h"
#include"Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "stb_image.h"


class Model
{
public:
	/*  ����   */
	Model(std::string path)
	{
		loadModel(path);
	}
	void Draw(Shader* shader);
private:
	/*  ģ������  */
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;
	/*  ����   */
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
		std::string typeName);
	unsigned int TextureFromFile(const char *path, const std::string &directory);
};

