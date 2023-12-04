#include "doctest.hpp"
#include "funcionalidades.hpp"
#include "escolha.hpp"
#include "batalha.hpp"
#include "enemy.hpp"
#include "inventario.hpp"
#include "player.hpp"
#include <ncurses.h>
#include <string>

TEST_CASE("Teste da função ganharPocao") {
    Player player("TestPlayer", 100, 20, '1');
    Inventario inventario;

    SUBCASE("Ganhar poção de cura ao atingir níveis 3 e 7") {
        player.level = 3;
        ganharPocao(player, inventario);
        CHECK(inventario.curaCount == 2);

        player.level = 7;
        ganharPocao(player, inventario);
        CHECK(inventario.curaCount == 3);
    }

    SUBCASE("Ganhar poção de dano ao atingir níveis 5 e 9") {
        player.level = 5;
        ganharPocao(player, inventario);
        CHECK(inventario.danoCount == 2);

        player.level = 9;
        ganharPocao(player, inventario);
        CHECK(inventario.danoCount == 3);
    }

    SUBCASE("Não ganhar poção em outros níveis") {
        player.level = 1;
        ganharPocao(player, inventario);
        CHECK(inventario.curaCount == 1);
        CHECK(inventario.danoCount == 1);

        player.level = 4;
        ganharPocao(player, inventario);
        CHECK(inventario.curaCount == 1);
        CHECK(inventario.danoCount == 1);
    }
}


