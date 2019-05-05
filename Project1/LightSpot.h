#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

class LightSpot
{
public:

	glm::vec3 postion;
	glm::vec3 angles;
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);
	glm::vec3 color;

	float constant;
	float linear;
	float quadratic;

	float cosPhyIn = 0.9f;
	float cosPhyOut = 0.85f;

	LightSpot(glm::vec3 _postion, glm::vec3 _angle, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightSpot();

	void UpdateDirection();
};

