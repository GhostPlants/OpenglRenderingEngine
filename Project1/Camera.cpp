#include "Camera.h"



Camera::Camera(glm::vec3 postion, glm::vec3 target, glm::vec3 worldUp)
{
	Postion = postion;
	WorldUp = worldUp;
	Forward = glm::normalize(target - postion);
	Right = glm::normalize(glm::cross(Forward , WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));


}

Camera::Camera(glm::vec3 postion, float pitch, float yaw, glm::vec3 worldUp)
{
	Postion = postion;
	WorldUp = worldUp;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw)); // ��ע��direction�����������ǰ��(Front)�����ǰ���Ǻͱ��ĵ�һ��ͼƬ�ĵڶ���������ķ����������෴��
	Forward.y = sin(glm::radians(Pitch));
	Forward.z = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Postion,Postion + Forward , WorldUp);
}
void Camera:: CameraUpdateVet()
{
	Forward.x = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw)); // ��ע��direction�����������ǰ��(Front)�����ǰ���Ǻͱ��ĵ�һ��ͼƬ�ĵڶ���������ķ����������෴��
	Forward.y = sin(glm::radians(Pitch));
	Forward.z = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}
void  Camera::PorcessMouseMovement(float x, float y)
{
	Pitch -= y * SenseMouse;
	Yaw -= x * SenseMouse;
	CameraUpdateVet();
}
void Camera::UpdateCameraPos()
{
	Postion +=Forward * SpeedZ + Right * SpeedX + Up * SpeedY;
}


