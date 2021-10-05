#include "renderer.h"

#define MOST_VERTICES 900 * 6

void Renderer::init()
{

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW failed to initialize" << std::endl;
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    vao.create();
    vao.bind();

    vbo.dynamic = true;
    vbo.create(MOST_VERTICES * sizeof(Vertex), nullptr);
    vbo.bind();

    vao.addPointer();
    vao.enable(0);

    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
}

void Renderer::deinit()
{
    vao.destroy();
    vbo.destroy();
}

void Renderer::update()
{
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);

    vao.bind();
    vbo.bind();

    for(auto i: oneDraw)
    {

        i.first->use();
        i.first->setMat4("projection", proj);

        vbo.dynamic_data(0, i.second.size()*sizeof(std::array<Vertex, 6>), i.second.data());
        glDrawArrays(GL_TRIANGLES, 0, i.second.size()*6);
    }

}

void Renderer::DrawQuad(std::array<Vertex, 6> vertices, Shader &shader)
{
    oneDraw[&shader].push_back(vertices);
}

void Renderer::clear()
{
    oneDraw.clear();
}
