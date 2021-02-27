#include <string>
#include <array>
#include <algorithm>

#include "grid.h"
#include "renderer.h"

class Game
{
    public:
        int width, height;
        int unit_width;
        Grid grid;
        Shader shader;
        Shader lines;

        std::string vs =
        R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        out vec4 vertexColor;
        uniform mat4 projection;
        void main()
        {
        gl_Position = projection * vec4(aPos, 1.0);
        vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
        }
        )";

        std::string fs =
        R"(
        #version 330 core
        out vec4 FragColor;
        in vec4 vertexColor;
        void main()
        {
        FragColor = vertexColor;
        }
        )";

        std::string fs2 =
        R"(
        #version 330 core
        #define PI 3.141592
        out vec4 FragColor;
        in vec4 vertexColor;
        void main()
        {
        if(cos((PI/10.0)*gl_FragCoord.x) > 0.9 || cos((PI/10.0)*gl_FragCoord.y) > 0.9)
        {
            FragColor = vec4(1.0, 1.0, 1.0, 0.4);
        }
        else
        {
            FragColor = vec4(0.0, 0.0, 0.0, 0.0);
        }
        }
        )";

        std::array<Vertex, 6> vertices = {
            {0.0f, 0.0f,
            0.0f, 600.0f,
            600.0f, 0.0f,
            0.0f, 600.0f,
            600.0f, 600.0f,
            600.0f, 0.0}
        };

        Renderer *renderer;
        Window *window;

        Game(float width, float height, float unit_length, Renderer &renderer, Window &window);

        // returns the amount of living cells around 1 cell
        int checkNeighbours(unsigned int x, unsigned int y);

        // Checks the number of neighbours and returns whether a cell should be alive or not
        bool applyRule(unsigned int x, unsigned int y);

        // checks neighbours and applies the rule and gives back a board
        void updateGrid();

        void toggleCell(int x, int y);

        void Draw();

};