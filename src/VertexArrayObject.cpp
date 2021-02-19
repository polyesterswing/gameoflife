#include "VertexArrayObject.h"

void VertexArrayObject::create()
{
    glGenVertexArrays(1, &ID);
}

void VertexArrayObject::bind()
{
    glBindVertexArray(ID);
}

void VertexArrayObject::unbind()
{
    glBindVertexArray(0);
}

void VertexArrayObject::addPointer()
{
    glVertexAttribPointer(0, sizeof(Vertex) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, position));
}

void VertexArrayObject::enable(int n)
{
    glEnableVertexAttribArray(n);
}

void VertexArrayObject::destroy()
{
    glDeleteVertexArrays(1, &ID);
}
