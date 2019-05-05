#include "LightPoint.h"


LightPoint::LightPoint(glm::vec3 _postion, glm::vec3 _angle, glm::vec3 _color)
{
	postion = _postion;
	angles = _angle;
	color = _color;

	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;

}


LightPoint::~LightPoint()
{
} 