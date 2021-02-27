#include "window.h"

bool Window::init()
{
    if(!glfwInit())
    {
        std::cout << "GLFW failed to initialize" << "\n";
        return -1;
    }

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if(!window)
    {
        std::cout << "No window :(" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwMakeContextCurrent(window);

    return 0;

}

void Window::mouseButtonCallback(GLFWmousebuttonfun callback)
{
    glfwSetMouseButtonCallback(window, callback);
}

void Window::loop(void update(void))
{
    while(!glfwWindowShouldClose(window))
    {
        update();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}