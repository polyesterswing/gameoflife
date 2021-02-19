#include "shader.h"
#include <iostream>

unsigned int Shader::createShader(const char *source, GLenum type) {
  unsigned int shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, 0);
  glCompileShader(shader);

  int compiled;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

  if (compiled != GL_TRUE){

    int infoLogLength = 0;
    char message[1024];
    glGetShaderInfoLog(shader, 1024, &infoLogLength, message);

    std::cout << message << std::endl;

  }

  return shader;
}

unsigned int Shader::makeProgram(unsigned int vertexShader, unsigned int fragmentShader) {
  ID = glCreateProgram();

  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);

  glLinkProgram(ID);

  return ID;
}

void Shader::use() {
  glUseProgram(ID);
}

void Shader::setMat4(const std::string &name, glm::mat4 value) {
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
  
}
