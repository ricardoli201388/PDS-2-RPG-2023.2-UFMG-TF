#include "funcionalidades.hpp"
#include "escolha.hpp"
#include "batalha.hpp"
#include "enemy.hpp"
#include "inventario.hpp"
#include "player.hpp"
#include <ncurses.h>
#include <string>

using namespace std;

bool getRandomBool(double probability) {
    return (rand() / static_cast<double>(RAND_MAX)) < probability;
}

// Função que representa a vez do jogador
void playerTurn(Player& player, Enemy& enemy, Inventario& inventario) {
    printStatus(player, enemy, inventario); // Mostra o status do jogador e inimigo na tela

    char action = getch(); // Obtém a ação escolhida pelo jogador
   
   
    // Verifica a ação escolhida e executa a ação correspondente
    if (action == 'a') {// Ataque
        int dano = player.attack;   // Dano base do jogador
        if (getRandomBool(0.3)) {   // Verifica se houve uma falha crítica (golpe errado - 20% de chance)
            mvprintw(23, 1, "EEeerrooouuuu! Você não causou dano!"); // Exibe mensagem de erro crítico
        } else {
            enemy.health -= dano;// Reduz a saúde do inimigo pelo dano
            mvprintw(23, 1, "Você atacou %s e causou %d de dano!", enemy.name.c_str(),dano);
                if (enemy.health <= 0) enemy.health = 0;
        }
   
    } else if (action == 'd') {// Defesa
        player.defending = true;// Ativa a defesa do jogador
        mvprintw(23, 1, "Você está se defendendo dos ataques de %s.", enemy.name.c_str());
      

 } else if (action == 'u') { // Uso de itens do inventário
        mvprintw(22, 1, "Escolha um item: (c) café da cura     (p) pão de queijo do dano) ");
       
        char itemAction = getch();

        switch (itemAction) {
           
            case 'c':
                inventario.usarCura(player);
                break;
            case 'p':
                inventario.usarDano(player);
                break;
            default:
                mvprintw(23, 1, "Item inválido. Tente novamente.");
                refresh();
                getch();// Aguarda entrada do usuário
                playerTurn(player, enemy, inventario);
                break;
        }


    } else {
        mvprintw(23, 1, "Ação inválida. Tente novamente."); // Mensagem para ação inválida
        refresh();
        getch();// Aguarda entrada do usuário
        playerTurn(player,enemy,inventario);
    }
    mvprintw(30, 1, "Pressione qualquer tecla para continuar...");// Mensagem para continuar
    getch();// Aguarda entrada do usuário
    refresh();// Atualiza a tela

          
}

// Função que representa a vez do inimigo
void enemyTurn(Player& player, Enemy& enemy) {
    if (player.health > 1) {  // Verifica se o jogador ainda está vivo
        int dano = enemy.attack; // Dano base do inimigo
        if (player.defending) { // Verifica se o jogador está defendendo
            dano /= 4; // Reduz pela quarta parte do dano se o jogador está defendendo
            enemy.health -= dano;
        mvprintw(24, 1, "O ataque refletiu e causou dano de %d  no %s", dano, enemy.name.c_str());// Exibe mensagem de ataque
        
        }
        player.health -= dano; // Reduz a saúde do jogador pelo dano do inimigo
        mvprintw(27, 1, "%s atacou você e causou %d de dano!", enemy.name.c_str(), dano);// Exibe mensagem de ataque
        mvprintw(30, 1, "Pressione qualquer tecla para continuar...");// Mensagem para continuar
        getch();// Aguarda entrada do usuário
    }
    refresh();// Atualiza a tela
}





// Função que representa a batalha entre o jogador e o inimigo
void battle(Player& player, Enemy& enemy, Inventario& inventario){
  
    while (player.health > 0 && enemy.health > 0) { // Enquanto ambos (jogador e inimigo) estiverem vivos
       playerTurn(player, enemy, inventario);// Vez do jogador
        if (enemy.health <= 0) {// Se o inimigo estiver derrotado
            mvprintw(30, 1, "Você derrotou %s. Parabéns!", enemy.name.c_str());  // Mensagem de vitória
            if (player.health > 0 && player.level < 10) {
                levelUp(player); // Evolui o jogador se ainda não atingiu o nível máximo
            }
            break;
        }


        enemyTurn(player, enemy);
        if (player.health <= 0) {
            mvprintw(35, 1, "Você foi derrotado por %s. Fim de Jogo!", enemy.name.c_str());
            break;
        }
    }
    if (player.health <= 0) player.health = 0;
}


// Função para ganhar itens
    void ganharPocao(Player& player,Inventario& inventario){
        if(player.level== 3 ||player.level==  7 ){

            inventario.curaCount++;
            mvprintw(34, 1, "Você ganhou um café da cura");// Exibe mensagem de evolução de nível
            refresh();
        }
        if(player.level== 5 ||player.level== 9){

            inventario.danoCount++;
            mvprintw(34, 1, "Você ganhou um pão de queijo do dano");// Exibe mensagem de evolução de nível
            refresh();
        }
    }