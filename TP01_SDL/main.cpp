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

#include <stdio.h>
#include "cores.c"

#define LARGURA_JANELA 600
#define ALTURA_JANELA 400

#define COMPRIMENTO_PESON 50
#define ALTURA_PESON 30

#define COMPRIMENTO_INIMIGO 50
#define ALTURA_INIMIGO 50

#define COMPRIMENTO_TIRO 20
#define ALTURA_TIRO 20

#define VELOCIDADE_LATERAL 0.1
#define FATOR_DIVISAO_VELOCIDADE_INIMIGO 5      // A velocidade lateral do inimigo ser� X vezes menor que a velocidade lateral da nossa nave
#define FATOR_MULTIPLICACAO_DESCIDA_INIMIGO 100 // Inimigo desce com uma velocidade 100 superior ao movimento lateral da nave

#define QUANTIDADE_DE_INIMIGOS 5

float VELOCIDADE_LATERAL_INIMIGO = VELOCIDADE_LATERAL / FATOR_DIVISAO_VELOCIDADE_INIMIGO;

float espaco_entre_inimigos = (LARGURA_JANELA - (COMPRIMENTO_INIMIGO * QUANTIDADE_DE_INIMIGOS)) / (QUANTIDADE_DE_INIMIGOS + 1);

bool gEsquerda = false; // Movimento da nave para a esquerda
bool gDireita = false;  // Movimento da nave para a direita

bool gTiro = false; // Movimento do tiro

typedef struct
{
    float x;
    float y;
} Coordenada;

typedef struct
{
    Coordenada inicial;
    Coordenada incremento;
    bool vivo;
} Inimigo;

void desenhaQuadradoIncremento(Coordenada primeira, Coordenada incremento, Cores cor);
void desenhaQuadradoAbs(Coordenada primeira, Coordenada ultima, Cores cor);
void desenhaLinha(Coordenada primeira, Coordenada ultima, Cores cor);
void desenhaTiro(Coordenada primeira);

void movimentaLateralmente(SDL_Event eventos, float posicao);
void movimentaLateralmente2(SDL_Event eventos);

void movimentoInimigo(Coordenada *inimigo, Coordenada *incremento, float auxiliar_velocidade_l, int qual_inimigo);

void movimentoTiro(Coordenada *tiro);

Coordenada atira(SDL_Event eventos, Coordenada posicao, Coordenada incremento);

bool colisaoInimigos(Coordenada obj1, Coordenada obj1_incremento, Coordenada obj2, Coordenada obj2_incremento);

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
    SDL_WM_SetCaption("TP01_SDL", NULL);

    // Tamanho da janela
    SDL_SetVideoMode(LARGURA_JANELA, ALTURA_JANELA, 32, SDL_OPENGL); // 600x400. 32 � relativo a bits por pixel

    // Cor inicial
    glClearColor(1.0, 1.0, 1.0, 1.0); //preto

    // �rea exibida
    glViewport(0, 0, LARGURA_JANELA, ALTURA_JANELA);

    // Sombra
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
    person.x = (LARGURA_JANELA / 2) - (COMPRIMENTO_PESON / 2);
    person.y = ALTURA_JANELA - 50;
    Coordenada person_incremento;
    person_incremento.x = COMPRIMENTO_PESON;
    person_incremento.y = ALTURA_PESON;

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
            if (eventos.type == SDL_QUIT || (eventos.type == SDL_KEYUP && eventos.key.keysym.sym == SDLK_ESCAPE))
            {
                executando = false;
            }

            // Anda lateralmente
            else
            {
                movimentaLateralmente(eventos, person.x);
                coord_tiro = atira(eventos, person, person_incremento);
            }
        }

        /// L�GICA

        /// Movimento

        // Movimento lateral do personagem (nave)
        if (gEsquerda == true)
        {
            person.x -= VELOCIDADE_LATERAL; // Ajusta a velocidade lateral
        }
        else if (gDireita == true)
        {
            person.x += VELOCIDADE_LATERAL; // Ajusta a velocidade lateral
        }

        // Movimento do inimigo
        for (int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++)
        {
            movimentoInimigo(&inimigo[i].inicial, &inimigo[i].incremento, VELOCIDADE_LATERAL_INIMIGO, i);
            if (inimigo[i].inicial.x <= ((((i + 0) * COMPRIMENTO_INIMIGO) + ((i + 0) * espaco_entre_inimigos))) || (inimigo[i].inicial.x + inimigo[i].incremento.x >= ((((i + 1) * COMPRIMENTO_INIMIGO) + ((i + 1) * espaco_entre_inimigos)) + espaco_entre_inimigos)))
            {
                for (int j = 0; j < QUANTIDADE_DE_INIMIGOS; j++)
                {
                    inimigo[j].inicial.y += VELOCIDADE_LATERAL * FATOR_MULTIPLICACAO_DESCIDA_INIMIGO; // Inimigo desce com uma velocidade 100 superior ao movimento lateral da nave
                }
                VELOCIDADE_LATERAL_INIMIGO = -VELOCIDADE_LATERAL_INIMIGO;
            }
            if (inimigo[i].vivo == true)
            {
                if (colisaoInimigos(inimigo[i].inicial, inimigo[i].incremento, person, person_incremento) == true)
                {
                    executando = false; // Sai do jogo
                }
            }
        }

        // Movimento do tiro;
        if (gTiro == true)
        {
            movimentoTiro(&coord_tiro);

            Coordenada incremento_tiro;
            incremento_tiro.x = COMPRIMENTO_TIRO;
            incremento_tiro.y = ALTURA_TIRO;

            for (int i = 0; i < QUANTIDADE_DE_INIMIGOS; i++)
            {
                if (colisaoInimigos(coord_tiro, incremento_tiro, inimigo[i].inicial, inimigo[i].incremento) == true)
                {
                    if (inimigo[i].vivo == true)
                    {
                        inimigo[i].vivo = false;
                        gTiro = false;
                    }
                }
            }
        }

        /// RENDERIZA��O
        glClear(GL_COLOR_BUFFER_BIT); //Limpa o buffer

        // Inicia matriz
        glPushMatrix();

        // Dimensoes da Matriz
        glOrtho(0, LARGURA_JANELA, ALTURA_JANELA, 0, -1, 1);

        // Cor
        // Op��es:
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
                desenhaQuadradoIncremento(inimigo[i].inicial, inimigo[i].incremento, Azul());
            }
        }

        // Desenha a nave do personagem
        desenhaQuadradoIncremento(person, person_incremento, Vermelho());

        // Desenha tiros
        if (gTiro == true)
        {
            desenhaTiro(coord_tiro);
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

void desenhaQuadradoAbs(Coordenada primeira, Coordenada ultima, Cores cor)
{
    glColor3f(cor.cor1, cor.cor2, cor.cor3);
    // Desenha um pol�gono por seus v�rtices

    glBegin(GL_TRIANGLE_FAN);
    // NOVIDADE: antes os valores eram -0.5, 0.5
    glVertex3f(primeira.x, primeira.y, 0.0);
    glVertex3f(ultima.x, primeira.y, 0.0);
    glVertex3f(ultima.x, ultima.y, 0.0);
    glVertex3f(primeira.x, ultima.y, 0.0);
    glEnd();
}

void desenhaQuadradoIncremento(Coordenada primeira, Coordenada incremento, Cores cor)
{
    glColor3f(cor.cor1, cor.cor2, cor.cor3);
    // Desenha um pol�gono por seus v�rtices

    glBegin(GL_TRIANGLE_FAN);
    // NOVIDADE: antes os valores eram -0.5, 0.5
    glVertex3f(primeira.x, primeira.y, 0.0);
    glVertex3f(primeira.x + incremento.x, primeira.y, 0.0);
    glVertex3f(primeira.x + incremento.x, primeira.y + incremento.y, 0.0);
    glVertex3f(primeira.x, primeira.y + incremento.y, 0.0);
    glEnd();
}

void desenhaTiro(Coordenada primeira)
{
    Coordenada incremento;
    incremento.x = COMPRIMENTO_TIRO;
    incremento.y = ALTURA_TIRO;

    primeira.x += (COMPRIMENTO_PESON / 2) - (incremento.x / 2);

    Cores cor = Preto();
    glColor3f(cor.cor1, cor.cor2, cor.cor3);

    // Desenha um pol�gono por seus v�rtices

    glBegin(GL_TRIANGLE_FAN);
    // NOVIDADE: antes os valores eram -0.5, 0.5
    glVertex3f(primeira.x, primeira.y, 0.0);
    glVertex3f(primeira.x + incremento.x, primeira.y, 0.0);
    glVertex3f(primeira.x + incremento.x, primeira.y + incremento.y, 0.0);
    glVertex3f(primeira.x, primeira.y + incremento.y, 0.0);
    glEnd();
}

void desenhaLinha(Coordenada primeira, Coordenada ultima, Cores cor)
{
    glColor3f(cor.cor1, cor.cor2, cor.cor3);
    // Desenha um pol�gono por seus v�rtices

    glBegin(GL_LINES); // GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGOM
    glVertex3f(primeira.x, primeira.y, 0.0);
    glVertex3f(ultima.x, ultima.y, 0.0);
    glEnd();
}

void movimentaLateralmente(SDL_Event eventos, float posicao)
{
    //if (posicao <= 0)
    {
        //gEsquerda == false;
    }
    //else if (posicao >= LARGURA_JANELA)
    {
        //gDireita == false;
    }
    //else
    {
        if (eventos.type == SDL_KEYDOWN)
        {
            if (eventos.key.keysym.sym == SDLK_LEFT && eventos.key.keysym.sym == SDLK_RIGHT)
            {
                gEsquerda = false;
                gDireita = false;
            }
            else if (eventos.key.keysym.sym == SDLK_LEFT)
            {
                gEsquerda = true;
            }
            else if (eventos.key.keysym.sym == SDLK_RIGHT)
            {
                gDireita = true;
            }
        }
        else if (eventos.type == SDL_KEYUP)
        {
            if (eventos.key.keysym.sym == SDLK_LEFT)
            {
                gEsquerda = false;
            }
            if (eventos.key.keysym.sym == SDLK_RIGHT)
            {
                gDireita = false;
            }
        }
    }
}

Coordenada atira(SDL_Event eventos, Coordenada posicao, Coordenada incremento)
{
    //    if (eventos.type == SDL_KEYDOWN)
    //    {
    //        if (eventos.key.keysym.sym == SDLK_SPACE)
    //        {
    //            gTiro = true;
    //            posicao.y -= incremento.y + 5;
    //
    //            return (posicao);
    //        }
    //    }
    if (eventos.type == SDL_KEYUP && eventos.key.keysym.sym == SDLK_SPACE)
    {
        gTiro = true;
        posicao.y -= incremento.y + 5;

        return (posicao);
    }
    else
    {
        Coordenada origem;
        origem.x = 0;
        origem.y = 0;

        return origem;
    }
}

void movimentaLateralmente2(SDL_Event eventos)
{
    if (eventos.type == SDL_KEYDOWN)
    {
        //if (eventos.key.keysym.sym == SDLK_LEFT && eventos.key.keysym.sym == SDLK_RIGHT)
        //{
        //    gEsquerda = false;
        //    gDireita = false;
        //}
        if (eventos.key.keysym.sym == SDLK_LEFT)
        {
            gEsquerda = true;
        }
        else if (eventos.key.keysym.sym == SDLK_RIGHT)
        {
            gDireita = true;
        }
    }
    else if (eventos.type == SDL_KEYUP)
    {
        if (eventos.key.keysym.sym == SDLK_LEFT)
        {
            gEsquerda = false;
        }
        if (eventos.key.keysym.sym == SDLK_RIGHT)
        {
            gDireita = false;
        }
    }
}

void movimentoTiro(Coordenada *tiro)
{
    tiro->y += (VELOCIDADE_LATERAL * (-1));

    if (tiro->y < 0)
    {
        gTiro = false;
    }
}

void movimentoInimigo(Coordenada *inimigo, Coordenada *incremento, float auxiliar_velocidade_l, int qual_inimigo)
{
    inimigo->x += auxiliar_velocidade_l;
}

bool colisaoInimigos(Coordenada obj1, Coordenada obj1_incremento, Coordenada obj2, Coordenada obj2_incremento)
{
    if (obj1.y + obj1_incremento.y < obj2.y)
    {
        return false;
    }
    else if (obj1.y > obj2.y + obj2_incremento.y)
    {
        return false;
    }
    else if (obj1.x + obj1_incremento.x < obj2.x)
    {
        return false;
    }
    else if (obj1.x > obj2.x + obj2_incremento.x)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool colisaoTiros(Coordenada obj1, Coordenada obj1_incremento, Coordenada obj2, Coordenada obj2_incremento)
{
    if (obj1.y + obj1_incremento.y < obj2.y)
    {
        return false;
    }
    else if (obj1.y > obj2.y + obj2_incremento.y)
    {
        return false;
    }
    else if (obj1.x + obj1_incremento.x < obj2.x)
    {
        return false;
    }
    else if (obj1.x > obj2.x + obj2_incremento.x)
    {
        return false;
    }
    else
    {
        return true;
    }
}
