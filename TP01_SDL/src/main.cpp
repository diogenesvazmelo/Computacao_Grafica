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
#include "../include/colors.hpp"
#include "../include/drawings.hpp"

float LARGURA_JANELA = 1280;
float ALTURA_JANELA = 720;

float COMPRIMENTO_PERSON = 50;
float ALTURA_PERSON = 30;

float COMPRIMENTO_INIMIGO = 50;
float ALTURA_INIMIGO = 50;

float COMPRIMENTO_TIRO = 20;
float ALTURA_TIRO = 20;

float VELOCIDADE_LATERAL = 2;
float FATOR_DIVISAO_VELOCIDADE_INIMIGO = 5;
float FATOR_MULTIPLICACAO_DESCIDA_INIMIGO = 100;

int QUANTIDADE_DE_INIMIGOS = 5;

float VELOCIDADE_LATERAL_INIMIGO = VELOCIDADE_LATERAL / FATOR_DIVISAO_VELOCIDADE_INIMIGO;
float espaco_entre_inimigos = (LARGURA_JANELA - (COMPRIMENTO_INIMIGO * QUANTIDADE_DE_INIMIGOS)) / (QUANTIDADE_DE_INIMIGOS + 1);

bool gEsquerda = false; // Movimento da nave para a esquerda
bool gDireita = false;  // Movimento da nave para a direita
bool gTiro = false;     // Movimento do tiro

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
    SDL_SetVideoMode(LARGURA_JANELA, ALTURA_JANELA, 32, SDL_OPENGL); // 720p. 32 -> relativo a bits por pixel

    // Cor inicial -> color & opacity
    glClearColor(PRETO.r, PRETO.g, PRETO.b, 1.0);

    // area exibida
    glViewport(0, 0, LARGURA_JANELA, ALTURA_JANELA);

    // sombra
    glShadeModel(GL_SMOOTH); //sombreamento

    // 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); //desenho geometrico

    // 3D
    glDisable(GL_DEPTH_TEST);
    //-----------------------------------------------------------------

    bool executando = true;

    SDL_Event eventos;

    // Nave
    Coordenada person;
    person.x = (LARGURA_JANELA / 2) - (COMPRIMENTO_PERSON / 2);
    person.y = ALTURA_JANELA - 50;
    Coordenada person_incremento;
    person_incremento.x = COMPRIMENTO_PERSON;
    person_incremento.y = ALTURA_PERSON;

    // Inimigos
    Inimigo inimigo[QUANTIDADE_DE_INIMIGOS];
    if (espaco_entre_inimigos < 5) // Espa�o m�nimo entre inimigos
    {
        espaco_entre_inimigos = 5;
    }
    for (int i = 0, x = espaco_entre_inimigos, y = 10; i < QUANTIDADE_DE_INIMIGOS; i++, x += (COMPRIMENTO_INIMIGO + espaco_entre_inimigos))
    {
        if (x > (LARGURA_JANELA - espaco_entre_inimigos - COMPRIMENTO_INIMIGO))
        {
            y += ALTURA_INIMIGO + 30;
            x = espaco_entre_inimigos;
        }
        inimigo[i].inicial.x = x;
        inimigo[i].inicial.y = y;
        inimigo[i].incremento.x = COMPRIMENTO_INIMIGO;
        inimigo[i].incremento.y = ALTURA_INIMIGO;
        inimigo[i].vivo = true;
    }

    Coordenada coord_tiro;
    coord_tiro.x = 0;
    coord_tiro.y = 0;

    /// Loop do Jogo
    while (executando)
    {
        // Eventos
        while (SDL_PollEvent(&eventos))
        {
            // Fecha com o x da janela ou com esc
            if (eventos.type == SDL_QUIT ||
                (eventos.type == SDL_KEYUP && eventos.key.keysym.sym == SDLK_ESCAPE))
            {
                executando = false;
            }
            // Anda lateralmente
            else
            {
                drws::movimentaLateralmente(eventos, person.x, gEsquerda, gDireita);
                coord_tiro = drws::atira(eventos,
                                         person,
                                         person_incremento,
                                         gTiro,
                                         gEsquerda,
                                         gDireita);
            }
        }

        /// LOGICA

        /// Movimento

        // Movimento lateral do personagem (nave)
        if (gEsquerda == true)
        {
            person.x -= VELOCIDADE_LATERAL;
        }
        else if (gDireita == true)
        {
            person.x += VELOCIDADE_LATERAL;
        }

        // Movimento do inimigo
        for (int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++)
        {
            drws::movimentoInimigo(&inimigo[i].inicial, &inimigo[i].incremento, VELOCIDADE_LATERAL_INIMIGO, i);
            if (inimigo[i].inicial.x <= ((((i + 0) * COMPRIMENTO_INIMIGO) + ((i + 0) * espaco_entre_inimigos))) ||
                (inimigo[i].inicial.x + inimigo[i].incremento.x >= ((((i + 1) * COMPRIMENTO_INIMIGO) + ((i + 1) * espaco_entre_inimigos)) + espaco_entre_inimigos)))
            {
                for (int j = 0; j < QUANTIDADE_DE_INIMIGOS; j++)
                {
                    // Inimigo desce com uma velocidade 100 superior ao movimento lateral da nave
                    inimigo[j].inicial.y += VELOCIDADE_LATERAL * FATOR_MULTIPLICACAO_DESCIDA_INIMIGO;
                }
                VELOCIDADE_LATERAL_INIMIGO = -VELOCIDADE_LATERAL_INIMIGO;
            }
            if (inimigo[i].vivo == true)
            {
                if (drws::colisaoInimigos(inimigo[i].inicial, inimigo[i].incremento, person, person_incremento) == true)
                {
                    executando = false; // Sai do jogo
                }
            }
        }

        // Movimento do tiro;
        if (gTiro == true)
        {
            drws::movimentoTiro(&coord_tiro, VELOCIDADE_LATERAL, gTiro);

            Coordenada incremento_tiro;
            incremento_tiro.x = COMPRIMENTO_TIRO;
            incremento_tiro.y = ALTURA_TIRO;

            for (int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++)
            {
                if (drws::colisaoInimigos(coord_tiro, incremento_tiro, inimigo[i].inicial, inimigo[i].incremento) == true)
                {
                    if (inimigo[i].vivo == true)
                    {
                        inimigo[i].vivo = false;
                        gTiro = false;
                    }
                }
            }
        }

        /// RENDERIZACAO
        glClear(GL_COLOR_BUFFER_BIT); //Limpa o buffer

        // Inicia matriz
        glPushMatrix();

        // Dimensoes da Matriz
        glOrtho(0, LARGURA_JANELA, ALTURA_JANELA, 0, -1, 1);

        // Cor
        // Opcoes:
        // glColor3d (1 ou 0)
        // glColor3f (decimais)
        // glColor3ub (R, G, B) - 0 at� 255 cada um
        // glColor4ub (R, G, B, A) - 0 at� 255 cada um
        //glColor4ub (255, 0, 0, 255); // vermelho m�ximo

        // Inicia desenho

        // Desenha os inimigos
        for (int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++)
        {
            if (inimigo[i].vivo == true)
            {
                drws::desenhaQuadradoIncremento(inimigo[i].inicial, inimigo[i].incremento, AZUL);
            }
        }

        // Desenha a nave do personagem
        drws::desenhaQuadradoIncremento(person, person_incremento, VERMELHO);

        // Desenha tiros
        if (gTiro == true)
        {
            drws::desenhaTiro(coord_tiro,
                              COMPRIMENTO_TIRO,
                              ALTURA_TIRO,
                              COMPRIMENTO_PERSON,
                              BRANCO);
        }

        // Fecha matriz
        glPopMatrix();

        /// Anima��o
        SDL_GL_SwapBuffers();
    }

    ///-----------------------------------------------------------

    // ------------------------------------------------------------------

    glDisable(GL_BLEND); //Para Windows apenas

    SDL_Quit();

    return 0;
}