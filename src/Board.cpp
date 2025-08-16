#include "Board.h"
#include "Box.h"

#include <ctime>
#include <vector>
#include <iostream>

#define VISIBLE true
#define HIDDEN false

Board::Board(int w, int h, int diff) {
    width = w;
    height = h;
    difficulty = diff;
    seed = static_cast<unsigned int>(time(NULL));
    board.resize(height, std::vector<Box>(width, Box()));
}

void Board::set_tile_type(int x_pos, int y_pos, char type) {
    board[y_pos][x_pos].set_type(type);
}

bool Board::set_tile_visibilty(int x_pos, int y_pos, bool visiblity) {
    return board[y_pos][x_pos].set_visibility(visiblity);
}

char Board::check_tile(int x_pos, int y_pos) {
    return board[y_pos][x_pos].get_tile_type();
}

bool Board::get_visibility(int x_pos, int y_pos) {
    return board[y_pos][x_pos].get_tile_visibility();
}

void Board::generate_hints()
{

    int offsets[8][2] = {
        {-1, -1}, {0, -1}, {1, -1},   // top row
        {-1, 0},           {1, 0},    // same row
        {-1, 1},  {0, 1},  {1, 1}     // bottom row
    };  

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

            int count = 0;

            if (check_tile(x, y) == 'B')
            {
                continue;
            }

            for (auto &dir : offsets)
            {
                int nr = x + dir[0];
                int nc = y + dir[1];

                if (nr >= 0 && nr < width && nc >= 0 && nc < height)
                {
                    if (check_tile(nr, nc) == 'B')
                    {
                        count++;
                    }
                }
            }

            set_tile_type(x, y, count + '0');
        }
    }
}

void Board::generate_random_bombs()
{
    int count = static_cast<int>(width * height * (difficulty / 100.0));
    int g_count = 0, bx = 0, by = 0;
    srand(seed);
    while (g_count < count)
    {

        bx = rand() % width;
        by = rand() % height;
        if (check_tile(bx, by) != 'B')
        {
            set_tile_type(bx, by, 'B');
            std::cout << "Set Bomb on: " << bx << " " << by << std::endl;
            g_count += 1;
        }
    }
    print_board();
}


void Board::initialize_board() {
    generate_random_bombs();
    generate_hints();
}

void Board::open_space(int x_pos, int y_pos) {
    int offsets[8][2] = {
        {-1, -1}, {0, -1}, {1, -1}, // top row
        {-1, 0},  {1, 0},           // same row
        {-1, 1}, {0, 1}, {1, 1}     // bottom row
    };

    if (check_tile(x_pos, y_pos) != '0' && check_tile(x_pos, y_pos) != 'B')
    {
        set_tile_visibilty(x_pos, y_pos, VISIBLE);
        return;
    }

    set_tile_type(x_pos, y_pos, '\0');
    set_tile_visibilty(x_pos, y_pos, VISIBLE);
    // std::cout << "Current x, y: " << x_pos << " " << y_pos << std::endl;

    for (auto &dir : offsets)
    {
        int ny = y_pos + dir[1];
        int nx = x_pos + dir[0];

        if (nx >= 0 && nx < width && ny >= 0 && ny < height)
        {
            open_space(nx, ny);
        }
    }
}

void Board::check_win_condition() {

}


void print_line(int width)
{
    for (int i = 0; i < width * 2; i++)
    {
        std::cout << "_";
    }
    std::cout << std::endl;
}

void Board::print_board(){
    for (int i = 0; i < height; i++)
    {
        print_line(width);
        std::cout << "|";
        for (int j = 0; j < width; j++)
        {
            char temp = board[i][j].get_tile_type() > 0 ? board[i][j].get_tile_type() : ' ';
            std::cout << temp << "|";
        }
        std::cout << std::endl;
    }
    print_line(width);
}
