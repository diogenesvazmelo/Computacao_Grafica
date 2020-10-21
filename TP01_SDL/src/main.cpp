/// g++ -o main.cpp -lSDLmain -lSDL -lGL
/// Design: piskel.com

// codeblocks linker flags - diogenes: -lmingw32 -lSDLmain -lSDL -lopengl32
// -lglu32 codeblocks linker flags - nicholas: -lSDL -lglut -lSOIL -lGLU -lGL

#if __linux__
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "SDL/SDL_opengl.h"
#elif _WIN32
#include <SDL.h>

#include "SDL_opengl.h"
#endif

#include <iostream>
#include <vector>

#include "../include/colors.hpp"
#include "../include/drawings.hpp"
#include "../include/spaceship.hpp"
#include "../include/utils.hpp"

const float WINDOW_WIDTH = 1280;
const float WINDOW_HEIGHT = 720;
const float DEFAULT_SHIP_WIDTH = 50.0;
const float DEFAULT_SHIP_HEIGHT = 50.0;
const float DEFAULT_ENEMY_SPACE = 100;
const float DEFAULT_PADDING = (DEFAULT_ENEMY_SPACE - DEFAULT_SHIP_WIDTH) /
                              2;  // space of movement of the enemy
const int ENEMY_AMOUNT = (int)(WINDOW_WIDTH / DEFAULT_ENEMY_SPACE);
bool ENEMY_DIRECTION = true;  // Right/true and Left/false !

Color VERMELHO = Color(1, 0, 0);
Color VERDE = Color(0, 1, 0);
Color AZUL = Color(0, 0, 1);
Color PRETO = Color(0, 0, 0);
Color BRANCO = Color(1, 1, 1);

SDL_Surface *screen;
SDL_Surface *pause_image;

bool init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
    return false;
  }
  /* Clean up on exit */
  atexit(SDL_Quit);

  // Nome da janela
  SDL_WM_SetCaption("Space Invanders", NULL);
  // Tamanho da janela
  screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_OPENGL);
  if (screen == NULL) {
    fprintf(stderr, "Couldn't set %.0f x %.0f x 32 video mode: %s\n",
            WINDOW_WIDTH, WINDOW_HEIGHT, SDL_GetError());
    return false;
  }
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  // Cor inicial -> color & opacity
  glClearColor(PRETO.r, PRETO.g, PRETO.b, 1.0);
  // area exibida
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  // sombra
  glShadeModel(GL_SMOOTH);  // sombreamento

  // 2D
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();  // desenho geometrico

  // 3D
  glDisable(GL_DEPTH_TEST);
  //-----------------------------------------------------------------

  // INITIALIZING IMAGE SUPPORT
  int flags = IMG_INIT_JPG | IMG_INIT_PNG;
  int initted = IMG_Init(flags);
  if ((initted & flags) != flags) {
    fprintf(stderr, "IMG_Init: Failed to init required jpg and png support!\n");
    fprintf(stderr, "IMG_Init: %s\n", IMG_GetError());
    return false;
  }

  return true;
}

int main(int argc, char *args[]) {
  if (!init()) exit(1);

  // SCREENS
  pause_image = IMG_Load("./imgs/mario.png");
  if (!pause_image) printf("ERROR IN IMAGE\n");

  // VARIABLES
  bool executando = true;
  SDL_Event eventos;
  // TODO: REMOVE THIS
  std::vector<bool> playerDirection(2, false);
  utils::STATES GAME_STATE = utils::PLAYING;
  bool blastExists = false;
  bool isPaused = false;

  // Nave -> (x, y, h, w)
  Spaceship player = Spaceship((WINDOW_WIDTH / 2), WINDOW_HEIGHT - 50, 30.0,
                               DEFAULT_SHIP_WIDTH, 5);
  Blast playerBlast;

  // Inimigos
  std::vector<Spaceship> enemies(ENEMY_AMOUNT);
  std::vector<float> origCoord(ENEMY_AMOUNT);
  for (int i = 0; i < ENEMY_AMOUNT; i++) {
    // adapts the space according to the enemy amount
    float enem_x = DEFAULT_PADDING * 2 * i + DEFAULT_PADDING +
                   DEFAULT_SHIP_WIDTH * i + DEFAULT_SHIP_WIDTH / 2;
    enem_x += (WINDOW_WIDTH - (ENEMY_AMOUNT * DEFAULT_ENEMY_SPACE)) / 2;

    enemies[i] = Spaceship(enem_x, DEFAULT_SHIP_HEIGHT + 30);
    origCoord[i] = enem_x;
  }

  /// Loop do Jogo
  while (executando) {
    // Eventos - teclado
    while (SDL_PollEvent(&eventos)) {
      utils::checkState(eventos, GAME_STATE, isPaused);
      utils::checkPlayerDirection(eventos, playerDirection);
      utils::shot(eventos, blastExists, playerBlast, player);
    }

    switch (GAME_STATE) {
      case utils::PLAYING: {
        /// LOGICA
        if (playerDirection[0] &&
            player.getX() - player.getSpeed() - player.getWidth() / 2 > 0)
          player.moveLeft();
        if (playerDirection[1] &&
            player.getX() + player.getSpeed() + player.getWidth() / 2 <
                WINDOW_WIDTH)
          player.moveRight();
        if (blastExists) {
          playerBlast.moveUp();
          // TODO: check out of bounds
          if (utils::outOfBounds(playerBlast, WINDOW_WIDTH, WINDOW_HEIGHT)) {
            blastExists = false;
          }
          // Check colission with enemies
          for (int i = 0; i < ENEMY_AMOUNT; i++) {
            if (!enemies[i].isDestroyed() &&
                utils::collision(playerBlast, enemies[i])) {
              blastExists = false;
              enemies[i].setDestroyed(true);
              break;
            }
          }
        }

        for (int i = 0; i < ENEMY_AMOUNT; i++) {
          if (!enemies[i].isDestroyed()) {
            utils::enemyMovement(enemies[i], origCoord[i] - DEFAULT_PADDING,
                                 origCoord[i] + DEFAULT_PADDING,
                                 ENEMY_DIRECTION);
            if (utils::outOfBounds(enemies[i], WINDOW_WIDTH, WINDOW_HEIGHT))
              GAME_STATE = utils::GAME_OVER;
            if (utils::collision(player, enemies[i]))
              GAME_STATE = utils::GAME_OVER;
          }
        }

        // TODO: check if enemy got to the bottom of the screen.

        drws::resetScreen(WINDOW_WIDTH, WINDOW_HEIGHT);

        // Desenho
        for (int i = 0; i < ENEMY_AMOUNT; i++) {
          if (!enemies[i].isDestroyed()) drws::drawsSpaceship(enemies[i], AZUL);
          enemies[i].moveDown();
        }

        // Desenha a nave do personagem
        drws::drawsSpaceship(player, VERMELHO);

        if (blastExists) {
          drws::drawsBlast(playerBlast, BRANCO);
        }
        break;
      }
      case utils::PAUSED: {
        //   Spaceship(float _x, float _y, float _height, float _width);
        Spaceship teste =
            Spaceship(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 300.0, 300.0);
        drws::resetScreen(WINDOW_WIDTH, WINDOW_HEIGHT);
        drws::drawsSpaceship(teste, BRANCO);
        break;
      }
      case utils::GAME_OVER: {
        //   Spaceship(float _x, float _y, float _height, float _width);
        Spaceship teste =
            Spaceship(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 300.0, 300.0);
        drws::resetScreen(WINDOW_WIDTH, WINDOW_HEIGHT);
        drws::drawsSpaceship(teste, VERDE);
        break;
      }
      case utils::EXIT:
        executando = false;
        break;

      default:
        std::cout << "SOMETHING WENT WRONG!\n";
        break;
    }

    // Fecha matriz
    glPopMatrix();
    /// Animacao
    SDL_GL_SwapBuffers();
  }

  // ------------------------------------------------------------------

  glDisable(GL_BLEND);  // Para Windows apenas
  SDL_Quit();

  return 0;
}