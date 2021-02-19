#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

class Shader
{
 public:
  unsigned int ID;
  unsigned int createShader(const char* source, GLenum type);
  unsigned int makeProgram(unsigned int vertexShader, unsigned int fragmentShader);
  void use();
  void setMat4(const std::string &name, glm::mat4 value);
};