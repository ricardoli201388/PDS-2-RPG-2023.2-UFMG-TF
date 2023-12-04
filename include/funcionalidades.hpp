#ifndef FUNCIONALIDADES_HPP
#define FUNCIONALIDADES_HPP

#include "player.hpp"
#include "enemy.hpp"
#include "inventario.hpp"


void printStatus(Player& player, Enemy& enemy, Inventario& inventario);// Função para imprimir o status do jogador e do inimigo na tela
void levelUp(Player& player);// Função para evoluir o jogador de nível

#endif // FUNCIONALIDADES_HPP
