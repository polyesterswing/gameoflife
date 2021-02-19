#include <stddef.h>
#include <GL/glew.h>
#include "utils.h"

class VertexArrayObject
{
    public:
        unsigned int ID;

        void create();
        void bind();
        void unbind();
        void destroy();
        void addPointer();
        void enable(int n);

};