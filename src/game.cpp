#include "game.h"

Game::Game(float width, float height, float unit_width, Renderer &renderer, Window &window): grid(width, height, unit_width), renderer(&renderer), window(&window)
{
    window.width = 600.0f;
    window.height = 600.0f;
    window.title = "Game of Life";
    window.init();

    renderer.clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
    renderer.init();

    unsigned int vertex = shader.createShader(vs.c_str(), GL_VERTEX_SHADER);
    unsigned int fragment = shader.createShader(fs.c_str(), GL_FRAGMENT_SHADER);

    shader.makeProgram(vertex, fragment);

    unsigned int fragment2 = lines.createShader(fs2.c_str(), GL_FRAGMENT_SHADER);

    lines.makeProgram(vertex, fragment2);

}

int Game::checkNeighbours(unsigned int x, unsigned int y)
{
    int livers = 0;

    if( grid.getCell(x+1, y) ) { livers++;}
    if( grid.getCell(x, y+1) ) { livers++;}
    if( grid.getCell(x+1, y+1) ) { livers++;}
    if( grid.getCell(x-1, y) ) { livers++;}
    if( grid.getCell(x, y-1) ) { livers++;}
    if( grid.getCell(x-1, y-1) ) { livers++;}
    if( grid.getCell(x-1, y+1) ) { livers++;}
    if( grid.getCell(x+1, y-1) ) { livers++;}

    return livers;
}

bool Game::applyRule(unsigned int x, unsigned int y)
{
    int livers = checkNeighbours(x, y);
    if(grid.getCell(x, y))
    {
        if(livers == 2 || livers == 3)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if(livers == 3)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void Game::updateGrid()
{
    std::array< std::array<bool, 30>, 30> internalBoard = grid.cells;

    for(unsigned int i = 0; i < 30; i++)
    {
        for(unsigned int j = 0; j < 30; j++)
        {
            internalBoard[i][j] = applyRule(i, j);
        }

    }

    grid.cells = internalBoard;

}

void Game::toggleCell(int x, int y)
{
    grid.cells[x][y] = !(grid.cells[x][y]);
}

void Game::Draw()
{
    std::array<Vertex, 6> tmp;
    renderer->DrawQuad(vertices, lines);

    for(int i = 0; i < grid.num_units; i++)
    {
        for(int j = 0; j < grid.num_units; j++)
        {

            tmp = grid.cell_x_y(i, j);

            if(grid.getCell(i, j))
            {
                renderer->DrawQuad(tmp, shader);
            }
        }
    }

    renderer->update();
}