#include "enemy.hpp"
#include <ncurses.h>

// Construtor da classe Enemy para inicializar seus atributos
Enemy::Enemy(std::string n, int h, int a) : name(n), health(h), attack(a) {}
