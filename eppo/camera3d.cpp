#include "camera3d.h"

#include <cmath>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Camera3D::update(Core* core)
{
    float delta = core->get_delta();

    float cameraSpeed = 4.0f * delta; // adjust accordingly
    if (core->input_manager.get_key(Key::W).down) position += cameraSpeed * front;
    if (core->input_manager.get_key(Key::S).down) position -= cameraSpeed * front;
    if (core->input_manager.get_key(Key::A).down) position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
    if (core->input_manager.get_key(Key::D).down) position += glm::normalize(glm::cross(front, up)) * cameraSpeed;

    // mouse stuff
    static glm::vec2 old_mouse;
    static glm::vec2 new_mouse;
    static float sensitivity = 0.1f;
    static bool first_mouse = false;

    new_mouse = core->input_manager.get_mouse_pos();

    if (first_mouse)
    {
        old_mouse = new_mouse;
        first_mouse = true;
    }

    glm::vec2 mouse_delta(new_mouse.x - old_mouse.x, old_mouse.y - new_mouse.y);
    old_mouse = new_mouse;
    mouse_delta *= sensitivity;

    yaw += mouse_delta.x;
    pitch += mouse_delta.y;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);
}

glm::mat4 Camera3D::get_view()
{
	return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera3D::get_projection(float w, float h)
{
    return glm::perspective(glm::radians(fov / 2), w / h, 0.1f, 100.0f);
}
