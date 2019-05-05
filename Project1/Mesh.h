#pragma once
#include <glm/glm.hpp>
#include <string>
#include<vector>
#include <glad/glad.h>
#include"shader.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
public:

public:
	/*  网格数据  */
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	/*  函数  */
	Mesh(float vertices[]);
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader* shader);
private:
	/*  渲染数据  */
	unsigned int VAO, VBO, EBO;
	/*  函数  */
	void setupMesh();

};

