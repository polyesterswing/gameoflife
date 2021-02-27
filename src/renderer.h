#ifndef RENDERER_H
#define RENDERER_H

#include <array>
#include <vector>
#include <unordered_map>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "utils.h"
#include "window.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "shader.h"

class Renderer
{
    public:
        glm::mat4 proj = glm::ortho(0.0f, 600.0f, 600.0f, 0.0f);
        bool wireframe;
        glm::vec4 clearColor = {0.0f, 0.0f, 0.0f, 0.0f};
        // Shader shader;
        std::unordered_map<Shader* , std::vector<std::array<Vertex, 6>>> oneDraw;


        // std::vector<oneDrawCall> toDraw;
        // std::vector<std::array<Vertex, 6>> quads;
        VertexArrayObject vao;
        VertexBufferObject vbo;

        void init();
        void setClearColor(glm::vec4 &clearColor);
        void DrawQuad(std::array<Vertex, 6> vertices, Shader &shader);

        void update();

        void deinit();
        void clear();
    
};

#endif