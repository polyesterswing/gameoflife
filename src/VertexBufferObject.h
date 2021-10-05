#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VertexBufferObject
{
    public:
        unsigned int ID;
        bool dynamic;

        void create(GLsizeiptr size, const void* data );
        void dynamic_data(GLintptr offset, GLsizeiptr size, const void* data);
        void bind();
        void unbind();
        void destroy();

};

#endif