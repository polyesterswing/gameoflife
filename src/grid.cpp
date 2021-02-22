#include "grid.h"

Grid::Grid(float screen_width, float screen_height, float unit_width) : screen_width(screen_width), screen_height(screen_height), unit_width(unit_width) {
    num_units = screen_width / unit_width;
    cells = { {false} };
}

void Grid::scr2grid(double &x, double &y){

    x = (int)(x / (unit_width));
    y = (int)(y / (unit_width));

}

std::vector<Vertex> Grid::cell_x_y(int x, int y)
{
  std::vector<Vertex> positions = cell_vertices(0.0f + (2 * x + 1)*(unit_width/2), 0.0f + (2 * y + 1)*(unit_width/2));
  return positions;
}

std::vector<Vertex> Grid::cell_vertices(int x, int y)
{
  std::vector<Vertex> positions = {
    {x - (unit_width/2), y + (unit_width/2)},   //1
    {x + (unit_width/2), y + (unit_width/2)},   //2
    {x - (unit_width/2), y - (unit_width/2)},   //3
    {x + (unit_width/2), y + (unit_width/2)},   //2
    {x - (unit_width/2), y - (unit_width/2)},   //3
    {x + (unit_width/2), y - (unit_width/2)}
  };

  return positions;
}

bool Grid::getCell(int i, int j)
{
  if( i > -1 && i < num_units && j > -1 && j < num_units)
  {
    return cells[i][j];
  }
  else
  {
    return false;
  }
}

void Grid::checkNeighbours()
{
  decltype(cells) internalBoard;

  for(unsigned int i = 0; i < num_units; i++)
  {
    for(unsigned int j = 0; j < num_units; j++)
    {
      int livers = 0;

      if( getCell(i+1, j) ) { livers++;}
      if( getCell(i, j+1) ) { livers++;}
      if( getCell(i+1, j+1) ) { livers++;}
      if( getCell(i-1, j) ) { livers++;}
      if( getCell(i, j-1) ) { livers++;}
      if( getCell(i-1, j-1) ) { livers++;}
      if( getCell(i-1, j+1) ) { livers++;}
      if( getCell(i+1, j-1) ) { livers++;}

      if(cells[i][j])
      {
        if(livers == 2 || livers == 3)
        {
          internalBoard[i][j] = true;
        }
        else
        {
          internalBoard[i][j] = false;
        }
      }
      else
      {
        if(livers == 3)
        {
          internalBoard[i][j] = true;
        }
        else
        {
          internalBoard[i][j] = false;
        }
      }

    }
  }

  cells = internalBoard;

}