#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "grid.h"
#include "VertexBufferObject.h"
#include "VertexArrayObject.h"

float SCR_HEIGHT = 600.0f;
float SCR_WIDTH = 600.0f;

// float vertices[] = {
//   -0.5f, -0.5f, 0.0f,   //1
//   -0.5f,  0.5f, 0.0f,   //2
//    0.5f,  0.5f, 0.0f,   //3
//   -0.5f, -0.5f, 0.0f,   //1
//    0.5f,  0.5f, 0.0f,   //3
//    0.5f, -0.5f, 0.0f    //4
// };

glm::mat4 proj = glm::ortho(0.0f, SCR_WIDTH, SCR_HEIGHT, 0.0f);

std::vector<float> square(float a, float x, float y) {
  std::vector<float> positions = {
    x - (a/2), y + (a/2), 0.0f,   //1
    x + (a/2), y + (a/2), 0.0f,   //2
    x - (a/2), y - (a/2), 0.0f,   //3
    x + (a/2), y + (a/2), 0.0f,   //2
    x - (a/2), y - (a/2), 0.0f,   //3
    x + (a/2), y - (a/2), 0.0f,
  };

  return positions;
}

std::vector<float> square_x_y(float a, int x, int y) {
  std::vector<float> positions = square(a, 0.0f + (2 * x + 1)*(a/2), 0.0f + (2 * y + 1)*(a/2));

  return positions;
}

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

std::vector<float> test = square_x_y(20.0f, 0, 0);
Grid grid(SCR_WIDTH, SCR_HEIGHT, 10.0f);

int main()
{

  for(float i: test){

    std::cout<< i << "\n";
  }

  if(!glfwInit())
    return -1;

  GLFWwindow* window;

  window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Fortnite", NULL, NULL);
  if(!window)
  {
    std::cout << "sadge" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
  glfwMakeContextCurrent(window);

  if (glewInit() != GLEW_OK)
    std::cout << "GLEW failed to initialize" << std::endl;

  glfwSetMouseButtonCallback(window, mouse_button_callback);

  Shader shader;

  unsigned int vertex = shader.createShader(vs.c_str(), GL_VERTEX_SHADER);
  unsigned int fragment = shader.createShader(fs.c_str(), GL_FRAGMENT_SHADER);

  shader.makeProgram(vertex, fragment);

  VertexArrayObject vao;
  vao.create();
  vao.bind();

  VertexBufferObject vbo;
  vbo.dynamic = true;
  vbo.create(18*sizeof(float), nullptr);
  vbo.bind();

  vao.addPointer();
  vao.enable(0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  while (!glfwWindowShouldClose(window))
  {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    vao.bind();
    shader.use();
    shader.setMat4("projection", proj);

    vbo.bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, 18*sizeof(float), &test[0]); 

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(window);
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
      std::cout << xpos <<  " " << ypos << std::endl;

      grid.scr2grid(xpos, ypos);
      test = square_x_y(20.0f, xpos, ypos);

    }
}

