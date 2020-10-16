/// g++ -o main.cpp -lSDLmain -lSDL -lGL
/// Design: piskel.com

// codeblocks linker flags - diogenes: -lmingw32 -lSDLmain -lSDL -lopengl32 -lglu32
// codeblocks linker flags - nicholas: -lSDL -lglut -lSOIL -lGLU -lGL

#if __linux__
#include <SDL/SDL.h>
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
const float DEFAULT_PADDING = (DEFAULT_ENEMY_SPACE - DEFAULT_SHIP_WIDTH) / 2; //space of movement of the enemy
const int ENEMY_AMOUNT = (int)(WINDOW_WIDTH / DEFAULT_ENEMY_SPACE);
bool ENEMY_DIRECTION = true; // Right/true and Left/false !

Color VERMELHO = Color(1, 0, 0);
Color VERDE = Color(0, 1, 0);
Color AZUL = Color(0, 0, 1);
Color PRETO = Color(0, 0, 0);
Color BRANCO = Color(1, 1, 1);

int main(int argc, char *args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    //glDisable(GL_BLEND); //Para Windows apenas

    //memoria
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16); //Usado em coisas 3D
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Nome da janela
    SDL_WM_SetCaption("Space Invanders", NULL);
    // Tamanho da janela
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_OPENGL); // 720p. 32 -> relativo a bits por pixel
    // Cor inicial -> color & opacity
    glClearColor(PRETO.r, PRETO.g, PRETO.b, 1.0);
    // area exibida
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    // sombra
    glShadeModel(GL_SMOOTH); //sombreamento

    // 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); //desenho geometrico

    // 3D
    glDisable(GL_DEPTH_TEST);
    //-----------------------------------------------------------------

    // VARIABLES
    bool executando = true;
    SDL_Event eventos;
    // TODO: REMOVE THIS
    std::vector<bool> playerDirection(2, false);
    utils::STATES GAME_STATE = utils::PLAYING;
    bool isPaused = false;

    // Nave -> (x, y, h, w)
    Spaceship player = Spaceship((WINDOW_WIDTH / 2), WINDOW_HEIGHT - 50, DEFAULT_SHIP_WIDTH, 30.0);

    // Inimigos
    std::vector<Spaceship> enemies(ENEMY_AMOUNT);
    std::vector<float> origCoord(ENEMY_AMOUNT);
    for (int i = 0; i < ENEMY_AMOUNT; i++)
    {
        // adapts the space according to the enemy amount
        float enem_x = DEFAULT_PADDING * 2 * i + DEFAULT_PADDING + DEFAULT_SHIP_WIDTH * i + DEFAULT_SHIP_WIDTH / 2;
        enem_x += (WINDOW_WIDTH - (ENEMY_AMOUNT * DEFAULT_ENEMY_SPACE)) / 2;

        enemies[i] = Spaceship(enem_x, DEFAULT_SHIP_HEIGHT + 30);
        origCoord[i] = enem_x;
    }

    /// Loop do Jogo
    while (executando)
    {
        // is space pressed
        bool attemptShot = false;

        // Eventos - teclado
        while (SDL_PollEvent(&eventos))
        {
            utils::checkState(eventos, GAME_STATE, isPaused);
            utils::checkPlayerDirection(eventos, playerDirection);
            attemptShot = utils::shot(eventos);
        }

        switch (GAME_STATE)
        {
        case utils::PLAYING:
        {
            if (playerDirection[0])
                player.moveLeft();
            if (playerDirection[1])
                player.moveRight();

            /// LOGICA

            for (int i = 0; i < ENEMY_AMOUNT; i++)
                utils::enemyMovement(enemies[i], origCoord[i] - DEFAULT_PADDING, origCoord[i] + DEFAULT_PADDING, ENEMY_DIRECTION);

            if (attemptShot)
                player.fireBlast();
            if (player.blastExists())
                player.getBlast()->moveUp();
            // TODO: check if enemy got to the bottom of the screen.

            drws::resetScreen(WINDOW_WIDTH, WINDOW_HEIGHT);

            // Desenho
            for (int i = 0; i < ENEMY_AMOUNT; i++)
            {
                if (!enemies[i].isDestroyed())
                    drws::drawsSpaceship(enemies[i], AZUL);
                enemies[i].moveDown();
            }

            // Desenha a nave do personagem
            drws::drawsSpaceship(player, VERMELHO);

            if (player.blastExists())
            {
                drws::drawsBlast(*(player.getBlast()), BRANCO);
            }

            // // Desenha tiros
            // if (gTiro == true)
            // {
            //     drws::desenhaTiro(coord_tiro,
            //                       COMPRIMENTO_TIRO,
            //                       ALTURA_TIRO,
            //                       COMPRIMENTO_PERSON,
            //                       BRANCO);
            // }
            break;
        }
        case utils::PAUSED:
        {
            //   Spaceship(float _x, float _y, float _height, float _width);
            Spaceship teste = Spaceship(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 300.0, 300.0);
            drws::resetScreen(WINDOW_WIDTH, WINDOW_HEIGHT);
            drws::drawsSpaceship(teste, BRANCO);
            break;
        }
        case utils::GAME_OVER:
        {
            //   Spaceship(float _x, float _y, float _height, float _width);
            Spaceship teste = Spaceship(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 300.0, 300.0);
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

    glDisable(GL_BLEND); //Para Windows apenas
    SDL_Quit();

    return 0;
}