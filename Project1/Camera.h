#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm:: vec3 postion, glm::vec3 target , glm::vec3 worldUp);
	Camera(glm::vec3 postion, float pitch, float yaw, glm::vec3 worldUp);

	glm::vec3 Postion;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	float Pitch;
	float Yaw;
	float SenseMouse = 0.05;
	float SpeedZ = 0;
	float SpeedY = 0;
	float SpeedX = 0;


	glm::mat4 GetViewMatrix();
	void PorcessMouseMovement(float x, float y);
	void UpdateCameraPos();

private:
	void CameraUpdateVet();
};

