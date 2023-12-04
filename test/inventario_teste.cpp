#include "doctest.hpp"
#include "inventario.hpp"
#include "player.hpp"
#include <ncurses.h>
#include <string>


TEST_CASE("Teste da classe Inventario") {
    Player player("TestPlayer", 100, 20, '1');
    Inventario inventario;

    SUBCASE("Teste do construtor") {
        CHECK(inventario.curaCount == 1);
        CHECK(inventario.danoCount == 1);
    }

    SUBCASE("Teste do método usarCura") {
        SUBCASE("Usar poção de cura com poções restantes") {
            inventario.usarCura(player);
            CHECK(player.health == 150); // health inicial + cura (50)
            CHECK(inventario.curaCount == 0);
        }

        SUBCASE("Usar poção de cura sem poções restantes") {
            inventario.usarCura(player); // Usando a única poção inicial
            inventario.usarCura(player); // Tentando usar outra
            CHECK(player.health == 150); // Não deve ter aumentado
            CHECK(inventario.curaCount == 0); // Não deve ter diminuído
        }
    }

    SUBCASE("Teste do método usarDano") {
        SUBCASE("Usar poção de dano com poções restantes") {
            inventario.usarDano(player);
            CHECK(player.attack == 30); // attack inicial + dano (10)
            CHECK(inventario.danoCount == 0);
        }

        SUBCASE("Usar poção de dano sem poções restantes") {
            inventario.usarDano(player); // Usando a única poção inicial
            inventario.usarDano(player); // Tentando usar outra
            CHECK(player.attack == 30); // Não deve ter aumentado
            CHECK(inventario.danoCount == 0); // Não deve ter diminuído
        }
    }
}
