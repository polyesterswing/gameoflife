/* 1. Any live cell with two or three live neighbours survives.
 * 2. Any dead cell with three live neighbours becomes a live cell.
 * 3. All other live cells die in the next generation. Similarly all other dead cells stay dead.*/

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>
#include <vector>
#include <Windows.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "grid.h"
#include "VertexBufferObject.h"
#include "VertexArrayObject.h"
#include "window.h"
#include "utils.h"

float SCR_HEIGHT = 600.0f;
float SCR_WIDTH = 600.0f;
const float unitlength = 20.0f;

Vertex vertices[] = {
  {0.0f, 0.0f},
  {0.0f, 600.0f},
  {600.0f, 0.0f},
  {0.0f, 600.0f},
  {600.0f, 600.0f},
  {600.0f, 0.0f}
};

Window window;

std::vector<Vertex> verticesToRender;

glm::mat4 proj = glm::ortho(0.0f, SCR_WIDTH, SCR_HEIGHT, 0.0f);

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

std::string vs =
  R"(
#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 vertexColor;

uniform mat4 projection;

void main()
{
   gl_Position = projection * vec4(aPos, 1.0);
   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
}
)";

std::string fs =
  R"(
#version 330 core
out vec4 FragColor;

in vec4 vertexColor;

void main()
{
  FragColor = vertexColor;
}
)";

std::string fs2 =
  R"(
#version 330 core
#define PI 3.141592

out vec4 FragColor;

in vec4 vertexColor;

void main()
{
  if(cos((PI/10.0)*gl_FragCoord.x) > 0.9 || cos((PI/10.0)*gl_FragCoord.y) > 0.9)
  {
    FragColor = vec4(1.0, 1.0, 1.0, 0.4);
  }
  else
  {
    FragColor = vec4(0.0, 0.0, 0.0, 0.0);
  }
}
)";

Grid grid(SCR_WIDTH, SCR_HEIGHT, 20.0f);

VertexArrayObject vao;
VertexBufferObject vbo;

int main()
{

  window.width = SCR_WIDTH;
  window.height = SCR_HEIGHT;
  window.title = "Game of Life";
  window.init();

  if (glewInit() != GLEW_OK)
    std::cout << "GLEW failed to initialize" << std::endl;

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );

  window.mouseButtonCallback(mouse_button_callback);

  Shader shader;

  unsigned int vertex = shader.createShader(vs.c_str(), GL_VERTEX_SHADER);
  unsigned int fragment = shader.createShader(fs.c_str(), GL_FRAGMENT_SHADER);

  shader.makeProgram(vertex, fragment);

  Shader lines;

  unsigned int fragment2 = lines.createShader(fs2.c_str(), GL_FRAGMENT_SHADER);

  lines.makeProgram(vertex, fragment2);

  vao.create();
  vao.bind();

  vbo.dynamic = true;
  vbo.create(900*6*sizeof(Vertex), nullptr);
  vbo.bind();

  vao.addPointer();
  vao.enable(0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  while (!glfwWindowShouldClose(window.window))
  {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    vao.bind();
    shader.setMat4("projection", proj);

    vbo.bind();
    vbo.dynamic_data(0, verticesToRender.size()*sizeof(decltype(verticesToRender)::value_type), &verticesToRender[0]);

    glDrawArrays(GL_TRIANGLES, 0, verticesToRender.size());

    lines.use();
    lines.setMat4("projection", proj);

    vbo.dynamic_data(0, 6 * sizeof(Vertex), &vertices);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(window.window);
    glfwPollEvents();
  }

  vao.destroy();
  vbo.destroy();

  return 0;
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
  if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
  {
    double xpos, ypos;

    glfwGetCursorPos(window, &xpos, &ypos);

    grid.scr2grid(xpos, ypos);

    grid.cells[(int)xpos][(int)ypos] = !(grid.cells[(int)xpos][(int)ypos]);

    verticesToRender.clear();

    for(unsigned int i = 0; i < grid.num_units; i++)
    {
      for(unsigned int j = 0; j < grid.num_units; j++)
      {
        if(grid.cells[i][j])
        {
          std::vector<Vertex> tmp = grid.cell_x_y(i, j);
          verticesToRender.insert(verticesToRender.end(), tmp.begin(), tmp.end());
        }
      }
    }

  }
  if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
  {
    grid.checkNeighbours();

    verticesToRender.clear();

    for(unsigned int i = 0; i < grid.num_units; i++)
    {
      for(unsigned int j = 0; j < grid.num_units; j++)
      {
        if(grid.cells[i][j])
        {
          std::vector<Vertex> tmp = grid.cell_x_y(i, j);
          verticesToRender.insert(verticesToRender.end(), tmp.begin(), tmp.end());
        }
      }
    }
  }
}
