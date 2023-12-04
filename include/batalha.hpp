#ifndef BATALHA_HPP
#define BATALHA_HPP

#include "player.hpp"
#include "enemy.hpp"
#include "inventario.hpp"
#include "funcionalidades.hpp"

bool getRandomBool(double probability);// Função para retornar um valor booleano aleatório baseado em uma probabilidade 
void playerTurn(Player& player, Enemy& enemy, Inventario& inventario);// Função que representa a vez do jogador 
void enemyTurn(Player& player, Enemy& enemy);// Função que representa a vez do inimigo 
void battle(Player& player, Enemy& enemy, Inventario& inventario);// Função que representa a batalha entre o jogador e o inimigo 
void ganharPocao(Player& player, Inventario& inventario);// Função que dá ao jogador poções em condições específicas

#endif // BATALHA_HPP