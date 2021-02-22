#include "VertexBufferObject.h"

void VertexBufferObject::create(GLsizeiptr size, const void* data )
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void VertexBufferObject::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBufferObject::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::destroy()
{
    glDeleteBuffers(1, &ID);
}

void VertexBufferObject::dynamic_data(GLintptr offset, GLsizeiptr size, const void* data)
{
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}