#pragma once

#include <glm/common.hpp>
#include "core.h"

class Camera3D
{
public:
	virtual void update(Core* core);
	glm::mat4 get_view();
	glm::mat4 get_projection(float w, float h);
protected:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	float yaw = -90.0f;
	float pitch = 0.0f;
	float fov = 90.0f;
};