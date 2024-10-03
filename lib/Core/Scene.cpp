#include "eregion/Core/Scene.h"

using namespace eregion;

namespace eregion {
Scene::Scene() : Scene(new Camera({0.0f, 0.0f})) {};

Scene::Scene(Camera* camera) : camera(camera) {};

Scene::~Scene() { delete camera; }

void Scene::init() {
    // // Create vertex buffer
    // info("Creating vertex buffer.");
    // GLuint vertex_buffer;
    // glGenBuffers(1, &vertex_buffer);
    // glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // // Load assets
    // auto vertRes = AssetPool::getShader("../assets/shaders/example.vert");

    // if (vertRes.isError()) {
    //     return Result<void>(Error{"Error loading vertex shader!"});
    // }

    // auto fragRes = AssetPool::getShader("../assets/shaders/example.frag");

    // if (fragRes.isError()) {
    //     return Result<void>(Error{"Error loading fragment shader!"});
    // }

    // // Create Program
    // auto progRes = ShaderProgram::compile(vertRes.getValue(), fragRes.getValue());

    // if (progRes.isError()) {
    //     return Result<void>(Error{"Error creating GL Program!"});
    // }

    // ShaderProgram* shaderProgram = progRes.getValue();

    // shaderProgram->use();

    // GLuint programId = shaderProgram->getProgramId();

    // const GLint mvp_location = glGetUniformLocation(programId, "MVP");
    // const GLint vpos_location = glGetAttribLocation(programId, "vPos");
    // const GLint vcol_location = glGetAttribLocation(programId, "vCol");

    // info("Creating vertex array.");
    // GLuint vertex_array;
    // glGenVertexArrays(1, &vertex_array);
    // glBindVertexArray(vertex_array);
    // glEnableVertexAttribArray(vpos_location);
    // glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    // glEnableVertexAttribArray(vcol_location);
    // glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));
}

void Scene::update(float dt) {

    // for (Entity entity : entities) {
    //     entity.update(dt);
    // }

    // TODO: All of this needs to be pushed down to rendering.
    // // Render
    // int width, height;
    // glfwGetFramebufferSize(this->glWindow, &width, &height);
    // const float ratio = width / (float)height;

    // glViewport(0, 0, width, height);
    // glClear(GL_COLOR_BUFFER_BIT);

    // mat4x4 m, p, mvp;
    // mat4x4_identity(m);
    // mat4x4_rotate_Z(m, m, (float)glfwGetTime());
    // mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    // mat4x4_mul(mvp, p, m);

    // glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp);
    // glBindVertexArray(vertex_array);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
}

} // namespace eregion