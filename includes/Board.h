#pragma once

#include "Box.h"
#include <vector>

class Board {
    public:
        Board(int w, int h, int diff);

        unsigned long get_seed() { return seed; }
        int get_width() { return width; }
        int get_height() { return height; }
        int get_difficulty() { return difficulty; }

        void initialize_board();
        void generate_random_bombs();
        void generate_hints();
        void open_space(int x_pos, int y_pos);
        void set_tile_type(int x_pos, int y_pos, char type);
        bool set_tile_visibilty(int x_pos, int y_pos, bool visiblity);

        bool get_visibility(int x_pos, int y_pos);
        char check_tile(int x_pos, int y_pos);

        void check_win_condition();
        void print_board();

    private:
        int width;
        int height;
        int difficulty;
        unsigned int seed;
        std::vector<std::vector<Box>> board;
};