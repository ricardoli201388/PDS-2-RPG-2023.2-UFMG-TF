//Lugar onde vamos realmente escrever o funcionamento do jogo usando as bibliotecas disponíveis. Por favor, se atentem a fazer bons comentarios ao longo do codigo! Bom trabalho.
//Grupo 3 - Jogo de RPG - Arthur Augusto Paiva Lemos, Filipe Henrique Nunes, Luisa Canielo de Carvalho, Ricardo Jianhong Li e Thales Eduardo de Castro Andrade

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "player.hpp"
#include "enemy.hpp"
#include "inventario.hpp"
#include "funcionalidades.hpp"
#include "batalha.hpp"
#include "escolha.hpp"

// Use esse no Linux:
#include <ncurses.h>



using namespace std;

int main() {
   
    // Inicialização do ambiente ncurses
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    box(stdscr, 0, 0);

// Mensagem de início do jogo
    mvprintw(1, 50, R"(
                    ####################################################################
                    #    _      _____                     ___            _       _ _   #
                    #   / \    |_   _|__  _ __ _ __ ___  |_ _|_ __   ___(_)_ __ (_) |_ #
                    #  / _ \     | |/ _ \| '__| '__/ _ \  | || '_ \ / __| | '_ \| | __|#
                    # / ___ \    | | (_) | |  | | |  __/  | || | | | (__| | |_) | | |_ #
                    #/_/   \_\_ _|_|\___/|_|  |_|  \___| |___|_| |_|\___|_| .__/|_|\__|#
                    #\ \   / (_) |_ __ _  | \ | | _____   ____ _          |_|          #
                    # \ \ / /| | __/ _` | |  \| |/ _ \ \ / / _` |                      #
                    #  \ V / | | || (_| | | |\  | (_) \ V / (_| |                      #
                    #   \_/  |_|\__\__,_| |_| \_|\___/ \_/ \__,_|                      #
                    ####################################################################

                        `,.      .   .        *   .    .      .  _    ..          .
                        \,~-.         *           .    .       ))       *    .
                            \ *          .   .   |    *  . .  ~    .      .  .  ,
                    ,          `-.  .            :               *           ,-
                    -             `-.        *._/_\_.       .       .   ,-'
                    -                 `-_.,     |n|     .      .       ;
                        -                  \ ._/_,_\_.  .          . ,'         ,
                        -                   `-.|.n.|      .   ,-.__,'         -
                        -                   ._/_,_,_\_.    ,-'              -
                        -                     |..n..|-`'-'                -
                        -                  ._/_,_,_,_\_.                 -
                            -              ,-|...n...|                  -
                            -          ,-'._/_,_,_,_,_\_.              -
                               -  ,-=-'     |....n....|              -
                                -;       ._/_,_,_,_,_,_\_.         -
                               ,-          |.....n.....|          -
                             ,;         ._/_,_,_,_,_,_,_\_.         -
                                          |     UFMG    |
                    `,  '.  `.  ".  `,  '.| n   ,-.   n |  ",  `.  `,  '.  `,  ',
                  ,.:;..;;..;;.,:;,.;:,o__|__o !.|.! o__|__o;,.:;.,;;,,:;,.:;,;;:
                    [  ][  ][  ][  ][  |_i_i_H_|_|_|_H_i_i_|  ][  ][  ][  ][  ][
                                       |     //=====\\     |
                                       |____//=======\\____|
                                           //=========\\

                        )");


// Obter o nome do jogador
string playerName;
getPlayerName(playerName);
Player player("", 0, 0, '1'); // Inicializa um jogador vazio
Enemy enemy("Fantasma da Ansiedade", 45, 6);
selectCharacter(player); // Obtém a escolha do personagem
player.name = playerName; // Define o nome do jogador

// Mensagem introdutória
clear();
mvprintw(1, 1, "Uma noite, depois de um longo dia, %s se encontra na famosa taverna Kabraoos para ", player.name.c_str());
mvprintw(2, 1, "se deliciar com uma cerveja barata e um ambiente caloroso numa costumeira quinta-feira.");
mvprintw(3, 1, "Então, para sua surpresa, recebe um pombo correio de seu instrutor Luigi, dizendo:");
mvprintw(4, 1, "Caro aprendiz, percebo que avançou esses anos todos cumprindo da melhor forma possível suas tarefas na UFMG, ");
mvprintw(5, 1, "vulgo Universidade Fantastica de Magia e Guerra, porém agora tenho um ultimo desafio.");
mvprintw(6, 1, "Por séculos, os alunos da UFMG, assim como outras universidades, ");
mvprintw(7, 1, "sao desafiados a enfrentarem a TCC, Torre de Conclusão de Curso, ");
mvprintw(8, 1, "na qual provam seu valor e podem demonstrar tudo que foi aprendido nas aulas, treinos e provas.");
mvprintw(9, 1, "Amanha, você deverá seguir viagem para a Torre de Incipit Vita Nova, lugar onde enfrentará inúmeros inimigos por toda extensao da mesma. ");
mvprintw(10, 1, "Estarei te esperando na torre para lhe dar instruções, boa viagem!");
mvprintw(11, 1, "------------------------------------------------------------------------");
mvprintw(12, 1, "E assim, você segue uma árdua viagem até a temida Torre de Conclusão de Curso. ");
mvprintw(13, 1, "Depois de alguns dias, finalmente vê o altivo portão de madeira de lei e, ao se aproximar, ");
mvprintw(14, 1, "o mesmo abre e é possível ver seu instrutor Luigi o esperando lá dentro.");
mvprintw(15, 1, "-------------------------------------------------------------------------");
mvprintw(16, 1, "- Finalmente chegou! Imagino que a viagem tenha sido cansativa...");
mvprintw(17, 1, "- Estamos no primeiro andar da torre, onde vou explicar mais sobre como seu teste funcionará. ");
mvprintw(18, 1, "Cada andar apresenta um inimigo que deverá ser derrotado para seguir em frente.");
mvprintw(19, 1, "- Em alguns andares, você poderá receber itens ao derrotar os monstros, como uma poção de cura e uma poção de dano.");
mvprintw(20, 1, "- Além disso, no decorrer do jogo, voce podera melhorar seu ataque e sua vida total!");
mvprintw(21, 1, "- No seu turno, você pode escolher usar algum item ou então atacar. Para usar um item, digite (u), para atacar digite (a).");
mvprintw(22, 1, "- Assim que escolher uma dessas opções, outras vão aparecer, ");
mvprintw(23, 1, "cada uma com a respectiva letra que deverá ser digitada para se escolher um item e realizar a ação.");
mvprintw(24, 1, "- Não se esqueça de dar enter para concluir sua ação e seguir o jogo!");
mvprintw(25, 1, "- Acredito que seja isso... E se lembre, o último andar é guardado por um monstro terrível! ");
mvprintw(26, 1, "Ao derrotá-lo, poderá ficar com seu tesouro e terá completado com sucesso essa Torre. Boa sorte e bom jogo!");

mvprintw(29, 1, "Pressione enter para prosseguir...");
mvprintw(30, 1, R"(
                                 _______________
                            ()==(              (@==()
                                '______________'|
                                  |             |
                                  |             |
                                __)_____________|
                            ()==(               (@==()
                                 '--------------'
)");
refresh();
getch(); // Aguarda a tecla Enter


// Inicialização do jogador e inimigo
    Inventario inventario; // Cria o inventário do jogador


// Mensagem de entrada no mundo de aventuras
    refresh();
    mvprintw(45, 1, "Voce entrou num mundo de aventuras!");


// Semente para gerar números aleatórios
    srand(time(0));

int currentLevel; // Nível inicial do jogador



// Loop principal do jogo enquanto o jogador está vivo e não atingiu o nível máximo
while (player.health > 0 && player.level < 10) {
       
        // Lógica das batalhas
        battle(player, enemy, inventario); // Passando o nível atual para a função battle

        // Lógica de uso do inventário
        playerTurn(player, enemy, inventario);

        // Lógica para preparar para a próxima batalha
            if (player.health > 0 && player.level < 10) {
                    mvprintw(22, 1, "Você se prepara para a batalha!");
                    refresh();
                    currentLevel = player.level;
                    // Definindo inimigos específicos para cada nível
                    string enemyName;
                    int enemyHealth, enemyAttack;

                    switch (currentLevel) {      
                        case 2:
                            enemyName = "Zumbi Estudante";
                            enemyHealth = 55;
                            enemyAttack = 8;
                            break;
                        case 3:
                            enemyName = "Esqueleto Ritalinado";
                            enemyHealth = 65;
                            enemyAttack = 8;
                            break;
                        case 4:
                            enemyName = "Cálculo I";
                            enemyHealth = 70;
                            enemyAttack = 10;
                            break;
                        case 5:
                            enemyName = "Final de semestre";
                            enemyHealth = 80;
                            enemyAttack = 12;
                            break;
                        case 6:
                            enemyName = "Cérbero Caramelo";
                            enemyHealth = 95;
                            enemyAttack = 16;
                            break;
                        case 7:
                            enemyName = "Grifo";
                            enemyHealth = 105;
                            enemyAttack = 16;
                            break;
                        case 8:
                            enemyName = "Cálculo II ";
                            enemyHealth = 135;
                            enemyAttack = 12;
                            break;
                        case 9:
                            enemyName = "Bender: O controlador";
                            enemyHealth = 250;
                            enemyAttack = 40;
                            break;

                    }

                    // Criando o inimigo com base nos parâmetros definidos para o nível atual
                    enemy = Enemy(enemyName, enemyHealth, enemyAttack);

                    // Mensagem sobre o encontro do jogador com o novo inimigo
                    mvprintw(15, 1, "Você encontrou um %s!", enemy.name.c_str());
                    refresh();
                    }
                        
                            refresh();
                            ganharPocao(player, inventario);

    
                        
                        
                        refresh();


            }



// Mensagem final do jogo dependendo do resultado
    if (player.level == 10) {
        clear();
        mvprintw(2, 1, "Wooooow, parabéns!");
        mvprintw(3, 1, "Você matou o Dragão e completou a TCC! Pode ficar com o tesouro, você merece :D");
        mvprintw(4, 1, R"(
*******************************************************************************
          |                   |                  |                     |       
 _________|________________.=""_;=.______________|_____________________|_______
|                   |  ,-"_,=""     `"=.|                  |                   
|___________________|__"=._o`"-._        `"=.______________|___________________
          |                `"=._o`"=._      _`"=._                     |       
 _________|_____________________:=._o "=._."_.-="'"=.__________________|_______
|                   |    __.--" , ; `"=._o." ,-"""-._ ".   |                   
|___________________|_._"  ,. .` ` `` ,  `"-._"-._   ". '__|___________________
          |           |o`"=._` , "` `; .". ,  "-._"-._; ;              |       
 _________|___________| ;`-.o`"=._; ." ` '`."\` . "-._ /_______________|_______
|                   | |o;    `"-.o`"=._``  '` " ,__.--o;   |                   
|___________________|_| ;     (#) `-.o `"=.`_.--"_o.-; ;___|___________________
____/______/______/___|o;._    "      `".o|o_.--"    ;o;____/______/______/____
/______/______/______/_"=._o--._        ; | ;        ; ;/______/______/______/_
____/______/______/______/__"=._o--._   ;o|o;     _._;o;____/______/______/____
/______/______/______/______/____"=._o._; | ;_.--"o.--"_/______/______/______/_
____/______/______/______/______/_____"=.o|o_.--""___/______/______/______/____
/______/______/______/______/______/______/______/______/______/______/______/_
*******************************************************************************
)");
        mvprintw(28, 1, "Tesouro: Um diploma da UFMG e 1000 moedas de ouro!");
        mvprintw(29, 1, "Agora você finalmente completou seu desafio e concluiu a Universidade");
        mvprintw(30, 1, "Fantástica de Magia e Guerra. Você é um herói que provou poder seguir");
        mvprintw(31, 1, "aventuras mais desafiadoras e cansativas, como arrumar uma guilda para se");
        mvprintw(32, 1, "afiliar. Tenho certeza que seu futuro será brilhante pela frente!");
        mvprintw(35, 1, "(pressione enter para finalizar)");

getch(); // Aguarda a tecla Enter


clear();
        mvprintw(10, 1, "Obrigado por jogar!");
        mvprintw(11, 1, "FIM");
        mvprintw(35, 1, "(pressione enter para finalizar)");

getch(); // Aguarda a tecla Enter

clear();
        mvprintw(10, 1, "Créditos:");
        mvprintw(11, 1, "Arthur Augusto Paiva Lemos");
        mvprintw(12, 1, "Filipe Henrique Nunes");
        mvprintw(13, 1, "Luísa Canielo de Carvalho");
        mvprintw(14, 1, "Ricardo Jianhong Li");
        mvprintw(15, 1, "Thales Eduardo de Castro Andrade");
        mvprintw(35, 1, "(pressione enter para finalizar)");

getch(); // Aguarda a tecla Enter

    } else {
clear();       

        mvprintw(5, 1, "Ah não… Parece que você morreu! ;-;");
        
        mvprintw(8, 1, "A banca do TCC se reuniu e decidiu que voce nao e DIGNO!");
        mvprintw(10, 1, R"(
             *********
           *************
          *****     *****
         ***           ***
        ***             ***
        **    0     0    **
        **               **                  ____
        ***             ***             //////////
        ****           ****        ///////////////  
        *****         *****    ///////////////////
        ******       ******/////////         |  |
      *********     ****//////               |  |
   *************   **/////*****              |  |
  *************** **///***********          *|  |*
 ************************************    ****| <=>*
*********************************************|<===>* 
*********************************************| <==>*
***************************** ***************| <=>*
******************************* *************|  |*
********************************** **********|  |*   
*********************************** *********| 

)");




        mvprintw(35, 1, "(pressione enter para finalizar)");



getch(); // Aguarda a tecla Enter  

main();
    }

    refresh();
    getch();
    endwin();

    return 0;
}          
