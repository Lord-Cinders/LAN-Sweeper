#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include <ctime>

#define WIDTH 200
#define HEIGHT 200
#define MULTIPLIER 4
#define DIFFICULTY 10

void print_line(int width)
{
    for (int i = 0; i < width * 2; i++)
    {
        std::cout << "_";
    }
    std::cout << std::endl;
}

void print_board(char **board, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        print_line(width);
        std::cout << "|";
        for (int j = 0; j < width; j++)
        {
            char temp = board[j][i] > 0 ? board[j][i] : ' ';
            std::cout << temp << "|";
        }
        std::cout << std::endl;
    }
    print_line(width);
}

void generate_random_coordinates(char **board, int count, int width, int height)
{
    int g_count = 0, bx = 0, by = 0;
    srand(time(NULL));
    while (g_count < count)
    {

        bx = rand() % width;
        by = rand() % height;
        if (board[by][bx] != 'B')
        {
            board[by][bx] = 'B';
            g_count += 1;
        }
    }
    print_board(board, width, height);
}


void generate_hints(char ** board, int width, int height) {

    int offsets[8][2] = {
        {-1, -1}, {0, -1}, {1, -1}, // top row
        {-1, 0}, {1, 0},            // same row
        {-1, 1}, {0, 1}, {1, 1}     // bottom row
    };

    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++) {
            
            int count = 0;
            
            if (board[y][x] == 'B') { continue; }

            for (auto &dir : offsets)
            {
                int nr = x + dir[0];
                int nc = y + dir[1];

                if (nr >= 0 && nr < width && nc >= 0 && nc < height )
                {
                    if (board[nc][nr] == 'B')
                    {
                        count++;
                    }
                }
            }
    
            board[y][x] = count + '0';
        }
    }
    print_board(board, width, height);
}

int main(int argv, char **argc)
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        std::cout << "Failed to initialize SDL" << std::endl;
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "LANsweeper",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH * MULTIPLIER,
        HEIGHT * MULTIPLIER,
        0);

    char **board = new char *[DIFFICULTY];
    for (int i = 0; i < DIFFICULTY; i++)
    {
        board[i] = new char[DIFFICULTY];
        for (int j = 0; j < DIFFICULTY; j++)
        {
            board[i][j] = '\0';
        }
    }

    generate_random_coordinates(board, DIFFICULTY, DIFFICULTY, DIFFICULTY);
    generate_hints(board, DIFFICULTY, DIFFICULTY);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    int dx = (WIDTH * MULTIPLIER) / DIFFICULTY;
    int dy = (HEIGHT * MULTIPLIER) / DIFFICULTY;

    // drawing vertical lines
    for (int i = 0; i <= DIFFICULTY; i++)
    {
        int x = i * dx;
        SDL_RenderDrawLine(renderer, x, 0, x, HEIGHT * MULTIPLIER);
    }

    // drawing horizontal lines
    for (int i = 0; i <= DIFFICULTY; i++)
    {
        int y = i * dy;
        SDL_RenderDrawLine(renderer, 0, y, WIDTH * MULTIPLIER, y);
    }

    // draw right and bottom lines incase they are over the screens size
    SDL_RenderDrawLine(renderer, WIDTH * MULTIPLIER - 1, 0, WIDTH * MULTIPLIER - 1, HEIGHT * MULTIPLIER - 1);
    SDL_RenderDrawLine(renderer, 0, HEIGHT * MULTIPLIER - 1, WIDTH * MULTIPLIER - 1, HEIGHT * MULTIPLIER - 1);

    for (int i = 0; i < DIFFICULTY; i += 1)
    {
        for (int j = 0; j < DIFFICULTY; j += 1)
        {
            if (board[j][i] == 'B')
            {
                // std::cout << i << " " << j << std::endl;
                int x1, y1;
                x1 = (j) * dx;
                y1 = (i) * dy;
                // std::cout << x1 << " " << y1 << std::endl;
                SDL_RenderDrawLine(renderer, x1, y1, x1 + dx, y1 + dy);
            }
        }
    }

    SDL_RenderPresent(renderer);
    int mousex, mousey;
    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {

            // math logic to calculate mouse position

            switch (event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&mousex, &mousey);
                    std::cout << "Raw Mouse Position: " << mousex << " " << mousey << std::endl;
                    std::cout << "Relative Mouse Position: " << mousex / dx << " " << mousey / dy << std::endl;
                }
                break;

            case SDL_QUIT:
                running = false;
                break;
            }

            // std::cout << "Game is running" << std::endl;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}