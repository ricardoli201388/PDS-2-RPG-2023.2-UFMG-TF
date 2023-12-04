#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <string>
// Definição da classe Enemy para representar os inimigos
class Enemy {
public:
    std::string name;
    int health;
    int attack;

    Enemy(std::string n, int h, int a);

    // Outras funções e membros, se necessário
};

#endif // ENEMY_HPP
