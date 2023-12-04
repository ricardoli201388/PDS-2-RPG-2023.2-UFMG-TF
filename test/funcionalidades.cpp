#include "funcionalidades.hpp"
#include "enemy.hpp"
#include "inventario.hpp"
#include "player.hpp"
#include <ncurses.h>
#include <string>

using namespace std;

// Função para imprimir o status do jogador e do inimigo na tela
void printStatus(Player& player, Enemy& enemy, Inventario& inventario) {
  
char test = player.classe;

//char test = selectCharacter(player);

    clear(); // Limpa a tela
    // Imprime uma caixa de menu com as informações de saúde (HP) do jogador e do inimigo
    box(stdscr, 0, 0);
    mvprintw(1, 1, " Nome: %s ", player.name.c_str());
    mvprintw(3, 1, " HP %d",player.health);
    mvprintw(4, 1, " Nível:%d", player.level);
    mvprintw(5, 1, " Pocao Cura:%d ", inventario.curaCount);
    mvprintw(6, 1, " Pocao Dano:%d ", inventario.danoCount);
    mvprintw(1, 30, " Inimigo: %s", enemy.name.c_str());
    mvprintw(2, 30, " HP: %d ", enemy.health);
   
    // Imprime o avatar do herói
      attron(A_BOLD);

    // Desenha o avatar do herói
      switch (test) {
        case '1':
        mvprintw(2, 1, " Heroi: Barbaro");
        mvprintw(7, 1, R"(
   ,   A           {}
  / \, | ,        .--.
 |    =|= >      /.--.\
  \ /` | `       |====|
   `   |         |`::`|  
       |     .-;`\..../`;_.-^-._
      /\\/  /  |...::..|`   :   `|
      |:'\ |   /'''::''|   .:.   |
       \ /\;-,/\   ::  |..:::::..|
       |\ <` >  >._::_.| ':::::' |
       | `""`  /   ^^  |   ':'   | 
        )");
           break;

       case '2':
        mvprintw(2, 1, " Heroi: Mago");
        mvprintw(7,1, R"(
              _,-'|
           ,-'._  |
 .||,      |####\ |
\.`',/     \####| |
= ,. =      |###| |
/ || \    ,-'\#/,'`.
  ||     ,'   `,,. `.S
  ,|____,' , ,;' \| |
 (3|\    _/|/'   _| |
  ||/,-''  | >-'' _,\\
  ||'      ==\ ,-'  ,'
    )");
            break;

        case '3':
        mvprintw(2, 1, " Heroi: Druida");
        mvprintw(7, 1, R"(
               _,._      
              /   /|  
 \.`',/      |'L'| |    
 = ,. =      | -,| L    
 / || \    ,-'\"/,'`.   
   ||     ,'   `,,. `.  
   ,|____,' , ,;' \| |  
  (3|\    _/|/'   _| |  
   ||       |      |
   ||'      ==\ ,-'  ,' 
   ||       |  V \ ,| 
    )");
            break;
        case '4':
        mvprintw(2, 1, " Heroi: Bardo");
        mvprintw(7, 1, R"(
     \\||//
     ~~..'~
     (  \ )
      \ c/
     __\/__
    /      \
  _< .   _  \
  \`\ \-'/ \ \   ,,,_
   >|""O[|||||nn[:::<
  /_,---._\      '''~ 
    )");
            break;
        
        case '5':
        mvprintw(2, 1, " Heroi: Inventor");
        mvprintw(7, 1, R"(
          .,::::..
         ';''':';:.
          (o  o |;
          | <   );
          \ --' |
        ___'-.  |____
      .'    -  -     `'.
    ,'_      :          '.
   : [_]  ,  :  ,         :
   : :  ) --' '--- :`'... '.
   :   / \:: : :: /    :   :
    '''  |'' , ''|     : .'
    )");
            break;

    }

    attroff(A_BOLD); // Desativa o atributo de negrito

     // Imprime a mensagem para escolha de ação
    mvprintw(20, 1, "Escolha uma ação: ");
    mvprintw(21, 1, "(a)  atacar     (d)  defender    (u)  usar poção ");
    refresh();
}


// Função para evoluir o jogador de nível
void levelUp(Player& player) {
    player.level++;// Incrementa o nível do jogador
    mvprintw(26, 1, "Parabéns! Você subiu para o nível %d!", player.level);// Exibe mensagem de evolução de nível
    mvprintw(27, 1, "Pressione qualquer tecla para continuar...");// Mensagem para continuar

          if(player.level== 3 ||player.level==  7 ){
              attron(A_BOLD);
              mvprintw(28, 1, "Você ganhou uma pocao de cura");// Exibe mensagem de evolução de nível
              refresh();
          }
          if(player.level== 5 ||player.level== 9){
              attron(A_BOLD);
              mvprintw(28, 1, "Você ganhou uma pocao de dano");// Exibe mensagem de evolução de nível
              refresh();
          }  
  
       
        if (player.level == 9){

            player.attack*=2;
            player.health+=100;
              attron(A_BOLD);
              mvprintw(28, 1, "Depois de um árduo caminho pela torre, você foi agraciado por um poder divino e seu dano e saude aumentaram.");// Exibe mensagem de evolução de nível
              refresh();

        }

    getch();// Aguarda entrada do usuário
    refresh();// Atualiza a tela
}