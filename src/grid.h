#include <iostream>
#include <vector>
#include <array>

#include <glm/glm.hpp>

#include "utils.h"

class Grid
{
    private:
        float screen_width;
        float screen_height;

        float unit_width;

        std::vector<Vertex> cell_vertices(int x, int y);

    public:
        unsigned int num_units;
        std::array<std::array<bool, 30>, 30> cells;

        Grid(float screen_width, float screen_height, float unit_width);
        void scr2grid(double &x, double &y);
        std::vector<Vertex> cell_x_y(int x, int y);
        bool getCell( int i, int j);
        void checkNeighbours();
};