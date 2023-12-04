#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
// Definição da classe Player para representar o personagem do jogador
class Player {
public:
    std::string name;
    int health;
    int attack;
    int potionCount;
    int level;
    bool defending;
    char classe;

    Player(std::string n, int h, int a, char c);

 
};

#endif // PLAYER_HPP
