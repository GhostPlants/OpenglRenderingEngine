#include "LightDir.h"



LightDir::LightDir(glm::vec3 _postion, glm::vec3 _angle, glm::vec3 _color)
{
	postion = _postion;
	angles = _angle;
	color = _color;
	UpdateDirection();
}


LightDir::~LightDir()
{
}

void LightDir::UpdateDirection()
{
	direction = glm::vec3(0, 0, 1.0f);
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
	direction = -1.0f * direction;
}
