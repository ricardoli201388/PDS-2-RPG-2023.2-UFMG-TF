#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#include "player.hpp"

// Classe para representar o inventário do jogador
class Inventario {
public:

    int curaCount;
    int danoCount;

    Inventario();



    void usarCura(Player& player);
    void usarDano(Player& player);





    // Outras funções e membros, se necessário
};

#endif // INVENTARIO_HPP
