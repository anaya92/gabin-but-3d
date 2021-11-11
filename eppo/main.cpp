#include <iostream>
#include <algorithm>
#include "core.h"
#include "buffer.h"
#include "shader.h"
#include "texture2d.h"
#include "rendertexture2d.h"
#include "camera3d.h"
#include "ecs.h"

#include "predef_shaders.h"

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex
{
	float x, y, z;
    float s, t;
};

static std::string vert_source = \
R"(#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 st;

out vec2 texture_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    texture_coords = st;
	gl_Position = projection * view * model * vec4(pos.x, pos.y, pos.z, 1.0f);
})";

static std::string frag_source = \
R"(#version 330 core

in vec2 texture_coords;
out vec4 FragColor;

uniform sampler2D the_texture;

void main () {
    FragColor = texture(the_texture, texture_coords);
})";

//class GabinCube : public Entity
//{
//public:
//    GabinCube(std::vector<Vertex> cube_data) : mesh(cube_data, vertex_attributes), texture("gabin.png")
//    {
//        name = "Gabin";
//        std::cout << "a gabin was created\n";
//    }
//
//    ~GabinCube() override
//    {
//        std::cout << "a gabin was disposed\n";
//    }
//
//    void draw() override
//    {
//        texture.bind();
//        mesh.draw();
//    }
//private:
//    Buffer<Vertex> mesh;
//    Texture2D texture;
//
//    const std::vector<VertexAttributes> vertex_attributes = {
//        { 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0 },
//        { 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 3 * sizeof(float) }
//    };
//};

class CustomCamera : public Camera3D
{
public:
    void update(Core* core) override
    {
        Camera3D::update(core);

        desired_fov = core->input_manager.get_mouseb(MouseButton::RightButton).down ? zoom_fov : regular_fov;

        if (fov != desired_fov)
        {
            fov += ((desired_fov - fov) * 3) * core->get_delta();
            fov = std::clamp(fov, zoom_fov, regular_fov);
        }
    }

    const float zoom_fov = 45.0f;
    const float regular_fov = 90.0f;
    float desired_fov = 90.0f;
};

int main(int argc, char* argv[])
{
	Core* core = new Core();
    // ECS* ecs = new ECS();

    // plane
    const std::vector<Vertex> plane_data = {
        { 5.0f, -1.0f, 5.0f, 5.0f, 5.0f },
        { 5.0f, -1.0f, -5.0f, 5.0f, 0.0f },
        { -5.0f, -1.0f, 5.0f, 0.0f, 5.0f },
        { -5.0f, -1.0f, -5.0f, 0.0f, 0.0f },
        { 5.0f, -1.0f, -5.0f, 5.0f, 0.0f },
        { -5.0f, -1.0f, 5.0f, 0.0f, 5.0f },
    };

	// triangle one
    const std::vector<Vertex> vertex_data = {
        { -0.5f, -0.5f, -0.5f,  0.0f, 0.0f },
        { 0.5f, -0.5f, -0.5f,  1.0f, 0.0f },
        { 0.5f,  0.5f, -0.5f,  1.0f, 1.0f },
        { 0.5f,  0.5f, -0.5f,  1.0f, 1.0f },
        { -0.5f,  0.5f, -0.5f,  0.0f, 1.0f },
        { -0.5f, -0.5f, -0.5f,  0.0f, 0.0f },

        { -0.5f, -0.5f,  0.5f,  0.0f, 0.0f },
        { 0.5f, -0.5f,  0.5f,  1.0f, 0.0f },
        { 0.5f,  0.5f,  0.5f,  1.0f, 1.0f },
        { 0.5f,  0.5f,  0.5f,  1.0f, 1.0f },
        { -0.5f,  0.5f,  0.5f,  0.0f, 1.0f },
        { -0.5f, -0.5f,  0.5f,  0.0f, 0.0f },

        { -0.5f,  0.5f,  0.5f,  1.0f, 0.0f },
        { -0.5f,  0.5f, -0.5f,  1.0f, 1.0f },
        { -0.5f, -0.5f, -0.5f,  0.0f, 1.0f },
        { -0.5f, -0.5f, -0.5f,  0.0f, 1.0f },
        { -0.5f, -0.5f,  0.5f,  0.0f, 0.0f },
        { -0.5f,  0.5f,  0.5f,  1.0f, 0.0f },

        { 0.5f,  0.5f,  0.5f,  1.0f, 0.0f },
        { 0.5f,  0.5f, -0.5f,  1.0f, 1.0f },
        { 0.5f, -0.5f, -0.5f,  0.0f, 1.0f },
        { 0.5f, -0.5f, -0.5f,  0.0f, 1.0f },
        { 0.5f, -0.5f,  0.5f,  0.0f, 0.0f },
        { 0.5f,  0.5f,  0.5f,  1.0f, 0.0f },

        { -0.5f, -0.5f, -0.5f,  0.0f, 1.0f },
        { 0.5f, -0.5f, -0.5f,  1.0f, 1.0f },
        { 0.5f, -0.5f,  0.5f,  1.0f, 0.0f },
        { 0.5f, -0.5f,  0.5f,  1.0f, 0.0f },
        { -0.5f, -0.5f,  0.5f,  0.0f, 0.0f },
        { -0.5f, -0.5f, -0.5f,  0.0f, 1.0f },

        { -0.5f,  0.5f, -0.5f,  0.0f, 1.0f },
        { 0.5f,  0.5f, -0.5f,  1.0f, 1.0f },
        { 0.5f,  0.5f,  0.5f,  1.0f, 0.0f },
        { 0.5f,  0.5f,  0.5f,  1.0f, 0.0f },
        { -0.5f,  0.5f,  0.5f,  0.0f, 0.0f },
        { -0.5f,  0.5f, -0.5f,  0.0f, 1.0f }
    };

    const std::vector<VertexAttributes> vertex_attributes = {
        { 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0 },
        { 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 3 * sizeof(float) }
    };

    Buffer<Vertex> plane(plane_data, vertex_attributes);
    Buffer<Vertex> mesh(vertex_data, vertex_attributes);
    Texture2D maiya("image0.png");
    Texture2D floor("image2.jpg");

	// shader
	Shader shader(vert_source, frag_source);

    // render texture
    RenderTexture2D rt(640, 480);
    // Shader rt_s = rt.create_default_shader();
    Shader postprocess_shader(Predefined::Shaders::Postprocess::GenericVertex, Predefined::Shaders::Postprocess::DitheringFragment);

    // camera
    CustomCamera camera;

    core->cursor_locked(true);

	while (core->valid())
	{
		core->update();
        camera.update(core);

        if (core->input_manager.get_key(Key::Escape).down)
        {
            core->invalidate();
        }

        glm::mat4 view = camera.get_view();
        glm::mat4 projection = camera.get_projection(640.0f, 480.0f);

        // ecs->update();

        {
            rt.start_drawing();
            rt.clear((float)49 / 255, (float)71 / 255, (float)107 / 255, 1.0f);
            /*rt.clear(0.2f, 0.2f, 0.2f, 1.0f);*/
            shader.use();
   
            shader.set_uniform("view", view);
            shader.set_uniform("projection", projection);
            
            glm::mat4 model = glm::mat4(1.0f);
            shader.set_uniform("model", model);
            floor.bind();
            plane.draw();
         
            model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 0.0f));
            shader.set_uniform("model", model);
            maiya.bind();
            mesh.draw();
            
            rt.finish_drawing(core, postprocess_shader);
        }

		core->present();
	}

    // delete ecs;
	delete core;
	return 0;
}