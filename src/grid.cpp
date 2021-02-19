#include "grid.h"

Grid::Grid(float screen_width, float screen_height, float unit_width) : screen_width(screen_width), screen_height(screen_height), unit_width(unit_width) {
    num_units = screen_width / unit_width;
}

void Grid::scr2grid(double &x, double &y){

    x = (int)(x / (unit_width * 2));
    y = (int)(y / (unit_width * 2));

    std::cout << x << "," << y << "\n";

}