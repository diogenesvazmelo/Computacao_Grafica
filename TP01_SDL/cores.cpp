#include <stdio.h>
#include "include/cores.hpp"

/// Cores Prontas
Cores Vermelho()
{
    Cores vermelho;
    vermelho.cor1 = 1;
    vermelho.cor2 = 0;
    vermelho.cor3 = 0;
    return vermelho;
}

Cores Verde()
{
    Cores verde;
    verde.cor1 = 0;
    verde.cor2 = 1;
    verde.cor3 = 0;
    return verde;
}

Cores Azul()
{
    Cores azul;
    azul.cor1 = 0;
    azul.cor2 = 0;
    azul.cor3 = 1;
    return azul;
}

Cores Preto()
{
    Cores preto;
    preto.cor1 = 0;
    preto.cor2 = 0;
    preto.cor3 = 0;
    return preto;
}

Cores Ciano()
{
    Cores ciano;
    ciano.cor1 = 0;
    ciano.cor2 = 1;
    ciano.cor3 = 1;
    return ciano;
}

Cores Magenta()
{
    Cores magenta;
    magenta.cor1 = 1;
    magenta.cor2 = 0;
    magenta.cor3 = 1;
    return magenta;
}

Cores Amarelo()
{
    Cores amarelo;
    amarelo.cor1 = 1;
    amarelo.cor2 = 1;
    amarelo.cor3 = 0;
    return amarelo;
}

Cores Cinza()
{
    Cores cinza;
    cinza.cor1 = 0.6;
    cinza.cor2 = 0.6;
    cinza.cor3 = 0.6;
    return cinza;
}

Cores Branco()
{
    Cores branco;
    branco.cor1 = 1;
    branco.cor2 = 1;
    branco.cor3 = 1;
    return branco;
}
