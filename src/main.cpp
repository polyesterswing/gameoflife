/* 1. Any live cell with two or three live neighbours survives.
 * 2. Any dead cell with three live neighbours becomes a live cell.
 * 3. All other live cells die in the next generation. Similarly all other dead cells stay dead.*/

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>
#include <string>
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
#include "game.h"
#include "renderer.h"

float SCR_HEIGHT = 600.0f;
float SCR_WIDTH = 600.0f;
const float unitlength = 20.0f;

Renderer renderer;
Window window;

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

void update();

Game game(SCR_WIDTH, SCR_HEIGHT, 20.0f, renderer, window);

int main()
{
    // if (glewInit() != GLEW_OK)
    //   std::cout << "GLEW failed to initialize" << std::endl;

    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_BLEND);

    window.mouseButtonCallback(mouse_button_callback);

    // vao.create();
    // vao.bind();

    // vbo.dynamic = true;
    // vbo.create(900 * 6 * sizeof(Vertex), nullptr);
    // vbo.bind();

    // vao.addPointer();
    // vao.enable(0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    window.loop(update);

    // vao.destroy();
    // vbo.destroy();

    renderer.deinit();

    return 0;
}


void update()
{
    renderer.clear();
    game.Draw();
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;

        glfwGetCursorPos(window, &xpos, &ypos);

        game.grid.scr2grid(xpos, ypos);

        game.toggleCell(xpos, ypos);
    }

    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        game.updateGrid();
    }

    game.Draw();
}
