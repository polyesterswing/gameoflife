#include <iostream>
#include <vector>

#include <glm/glm.hpp>

class Grid
{
    private:
    float screen_width;
    float screen_height;
    float unit_width;
    int num_units;

    public:
        Grid(float screen_width, float screen_height, float unit_width);
        void scr2grid(double &x, double &y);
        std::vector<glm::vec2> board;
};