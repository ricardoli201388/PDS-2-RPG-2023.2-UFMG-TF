#include "player.hpp"
#include <ncurses.h>

// Construtor da classe Player para inicializar seus atributos
Player::Player(std::string n, int h, int a, char c) : name(n), health(h), attack(a), potionCount(3), level(1), defending(false), classe(c) {}
