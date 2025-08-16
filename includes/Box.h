#pragma once

class Box {
    public:
        Box() : _x(0), _y(0), type('0'), visible(false) {};
        Box(int x, int y, char box_type, bool box_visibility) : _x(x), _y(y),  type(box_type), visible(box_visibility) {};

        inline bool set_visibility(bool visiblity) {
            visible = visiblity;
            return visible;
        }

        inline void set_type(char tile_type) {
            type = tile_type;
        }

        inline char get_tile_type() { return type; }
        inline bool get_tile_visibility() { return this->visible; }

    private:
        int _x;
        int _y;
        char type;
        bool visible;
};