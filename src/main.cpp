#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <ctime>
#include "Board.h"
#include "Title.h"

#define WIDTH 200
#define HEIGHT 200
#define MULTIPLIER 3
#define DIFFICULTY 15

TTF_Font *font;
SDL_Texture *digitTextures[10];

SDL_Texture *generate_digit_texture(char *digit, SDL_Renderer *renderer)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, digit, {255, 255, 255, 255});
    // SDL_FreeSurface(surface);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void generate_board(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 204, 204, 255, 255);

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
}

void generate_initial_board(SDL_Renderer *renderer)
{

    int dx = (WIDTH * MULTIPLIER) / DIFFICULTY;
    int dy = (HEIGHT * MULTIPLIER) / DIFFICULTY;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < DIFFICULTY; i += 1)
    {
        for (int j = 0; j < DIFFICULTY; j += 1)
        {
            int x1, y1;
            x1 = (j)*dx;
            y1 = (i)*dy;
            SDL_Rect rect = {x1, y1, dx, dy};
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_SetRenderDrawColor(renderer, 204, 204, 255, 255);

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
}

int main(int argv, char **argc)
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        std::cout << "Failed to initialize SDL" << std::endl;
        return -1;
    }

    if (TTF_Init() < 0)
    {
        std::cout << "Failed to initialize SDL TTF: " << SDL_GetError() << std::endl;
    }

    font = TTF_OpenFont("assets/OpenSans.ttf", 20);

    SDL_Window *window = SDL_CreateWindow(
        "LANsweeper",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH * MULTIPLIER,
        HEIGHT * MULTIPLIER,
        0);
    

    // char **board = new char *[DIFFICULTY];
    // for (int i = 0; i < DIFFICULTY; i++)
    // {
    //     board[i] = new char[DIFFICULTY];
    //     for (int j = 0; j < DIFFICULTY; j++)
    //     {
    //         board[i][j] = '\0';
    //     }
    // }

    Board board = Board(DIFFICULTY, DIFFICULTY, DIFFICULTY);
    board.initialize_board();
    board.print_board();

    // generate_random_bombs(board, DIFFICULTY, DIFFICULTY, DIFFICULTY);
    // generate_hints(board, DIFFICULTY, DIFFICULTY);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int rectW, rectH;
    for (int i = 0; i < 9; i++)
    {
        char currDigit[2] = {(i == 0 ? '\0' : (char)('0' + i)), '\0'};
        digitTextures[i] = generate_digit_texture(currDigit, renderer);
        std::cout << "Generated for:" << (char)('0' + i) << std::endl;
        TTF_SizeText(font, currDigit, &rectW, &rectH);
    }

    Title title = Title(window, renderer);

    

    generate_initial_board(renderer);

    title.Draw(WIDTH * MULTIPLIER, HEIGHT * MULTIPLIER);

    // draw bombs
    // for (int i = 0; i < DIFFICULTY; i += 1)
    // {
    //     for (int j = 0; j < DIFFICULTY; j += 1)
    //     {
    //         int x1, y1;
    //         x1 = (j)*dx;
    //         y1 = (i)*dy;
    //         if (board.check_tile(j, i) == 'B') {
    //             // std::cout << i << " " << j << std::endl;

    //             // std::cout << x1 << " " << y1 << std::endl;
    //             SDL_RenderDrawLine(renderer, x1, y1, x1 + dx, y1 + dy);
    //         } else {
    //             SDL_Rect rect = {x1, y1, dx, dy};
    //             SDL_RenderCopy(renderer, digitTextures[board.check_tile(j, i) - '0'], NULL, &rect);
    //         }
    //     }
    // }

    int dx = (WIDTH * MULTIPLIER) / DIFFICULTY;
    int dy = (HEIGHT * MULTIPLIER) / DIFFICULTY;

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
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);

                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

                    SDL_GetMouseState(&mousex, &mousey);
                    // std::cout << "Raw Mouse Position: " << mousex << " " << mousey << std::endl;
                    // std::cout << "Relative Mouse Position: " << mousex / dx << " " << mousey / dy << std::endl;
                    int y = mousey / dy;
                    int x = mousex / dx;
                    if (x >= 0 && x < DIFFICULTY && y >= 0 && y < DIFFICULTY)
                    {
                        if (board.check_tile(x, y) == 'B')
                        {
                            std::cout << "BOOOOOOOOM!!!!!" << std::endl;
                            running = false;
                            break;
                        }
                        else
                        {
                            board.open_space(x, y);
                            board.print_board();
                            for (int i = 0; i < DIFFICULTY; i += 1)
                            {
                                for (int j = 0; j < DIFFICULTY; j += 1)
                                {
                                    int x1, y1;
                                    x1 = (j)*dx;
                                    y1 = (i)*dy;
                                    // std::cout <<"POS: "<<i<<","<<j<< " Tile: " << board.check_tile(j, i) << " Visibility: " << board.get_visibility(j, i) << std::endl;
                                    if (board.get_visibility(j, i))
                                    {
                                        char tile = board.check_tile(j, i);
                                        // std::cout << "Current Tile: " << tile << std::endl;
                                        if (tile >= '0' && tile < '9')
                                        {
                                            // std::cout << "Tile: " << tile << std::endl;
                                            // std::cout << "TTTTTTTTTTTTTTT" << std::endl;
                                            SDL_Rect rect = {(x1 + x1 + dx) / 2 - (rectW / 2), (y1 + y1 + dy) / 2 - (rectH / 2), rectW, rectH};
                                            SDL_RenderCopy(renderer, digitTextures[tile - '0'], NULL, &rect);
                                        }
                                    }
                                    else
                                    {
                                        SDL_Rect rect = {x1, y1, dx, dy};
                                        SDL_RenderFillRect(renderer, &rect);
                                    }
                                }
                            }
                            generate_board(renderer);
                            SDL_RenderPresent(renderer);
                            // explore_board(board, DIFFICULTY, DIFFICULTY, x, y);
                            // print_board(board, DIFFICULTY, DIFFICULTY);
                        }
                    }
                }
                break;

            case SDL_QUIT:
                running = false;
                break;
            }

            // std::cout << "Game is running" << std::endl;
        }
    }
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}