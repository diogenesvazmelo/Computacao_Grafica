#ifndef MY_UTILS_HPP
#define MY_UTILS_HPP

#if __linux__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL2/SDL.h>
#endif

#include <vector>

#include "../include/spaceship.hpp"

namespace utils {
enum STATES { PLAYING, VICTORY, PAUSED, GAME_OVER, EXIT };
SDL_Rect makeRect(int _x, int _y, int _h, int _w);
void reset(Spaceship &player, std::vector<Spaceship> &enemies,
           float window_width, float window_height, float padding,
           float enemyArea);

bool checkWinCondition(std::vector<Spaceship> sps);

bool collision(Spaceship player, Spaceship enemy);
bool collision(Blast blast, Spaceship enemy);
void enemyMovement(Spaceship &sp, float tConst, float leftLimit,
                   float rightLimit, bool &direction);

bool canGoLeft(Spaceship player, float movConst);
bool canGoRight(Spaceship player, float movConst, float window_width);
bool outOfBounds(Spaceship sp, float SCREEN_WIDTH, float SCREEN_HEIGHT);
bool outOfBounds(Blast b, float SCREEN_WIDTH, float SCREEN_HEIGHT);
}  // namespace utils
#endif
