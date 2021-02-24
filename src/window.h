#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
    public:
        int width;
        int height;
        std::string title;
        GLFWwindow* window;
        
        bool init();
        void mouseButtonCallback(GLFWmousebuttonfun callback);
};