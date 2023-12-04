#include "inventario.hpp"
#include <ncurses.h>

Inventario::Inventario() : curaCount(1), danoCount(1) {}

    void Inventario::usarCura(Player& player) {
        if (curaCount > 0) {
            int cura = 50; // Quantidade de cura da poção
            player.health += cura; // Aumenta a saúde do jogador
            curaCount--; // Decrementa o contador de poções de cura
            mvprintw(23, 1, "Você usou uma poção de cura e recuperou %d de HP. Poções de cura restantes: %d", cura, curaCount);
        } else {
            mvprintw(23, 1, "Você não tem mais poções de cura!");
        }
    }


    void Inventario::usarDano(Player& player) {
        if (danoCount > 0) {
            player.attack += 10; // Aumenta o poder de ataque do jogador temporariamente
            danoCount--; // Decrementa o contador de poções de dano
            mvprintw(23, 1, "Você usou uma poção de dano! Seu ataque foi aumentado temporariamente. Poções de dano restantes: %d", danoCount);
        } else {
            mvprintw(23, 1, "Você não tem mais poções de dano!");
        }
    }