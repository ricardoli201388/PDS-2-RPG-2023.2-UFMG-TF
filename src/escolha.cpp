#include "batalha.hpp"
#include "escolha.hpp"
#include "funcionalidades.hpp"
#include "enemy.hpp"
#include "inventario.hpp"
#include "player.hpp"
#include <ncurses.h>
#include <string>

using namespace std;

// Função para obter o nome do jogador
void getPlayerName(std::string& playerName) {
 
    mvprintw(40, 1,  "              Bem vindo(a) jogador(a)!");
    mvprintw(41, 1,  "Para começar sua aventura, primeiro digite seu nome e dê enter");
    
    mvprintw(43, 1, "Digite o nome do jogador: "); // Imprime o nome digitado
    refresh();

    char buffer[50];
    int i = 0;
   
    while (true) {
        int ch = getch(); // Obtém o próximo caractere digitado pelo usuário

        if (ch == '\n' || ch == '\r') {
            buffer[i] = '\0'; // Termina a string com null character
            break;
        } else if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) {
            if (i > 0) {
                buffer[--i] = '\0'; // Remove o último caractere digitado (tecla backspace)
            }
        } else if (i < 49) {
            buffer[i++] = ch; // Adiciona o caractere ao buffer
            buffer[i] = '\0'; // Termina a string com null character
        }

        box(stdscr, 0, 0); // Desenha a caixa de menu
        mvprintw(43, 1, "Digite o nome do jogador: %s", buffer); // Imprime o nome digitado
        refresh(); // Atualiza a tela
    }

    playerName = buffer; // Atualiza o nome do jogador com o valor digitado

}

void selectCharacter(Player& player) {

    clear(); // Limpa a tela
    mvprintw(2, 1, "Otimo, agora escolha com qual tipo de personagem queira jogar.");
    mvprintw(3, 1, "Quando estiver pronto para escolher, digite o numero correspondente a ele.");
   
    mvprintw(5, 1, "(1) Barbaro: muito forte e sempre energético, sabe muito bem como elaborar");
    mvprintw(6, 1, "    ótimos treinos, porém muitas vezes se surpreende com as inúmeras matérias");
    mvprintw(7, 1, "    que tem durante o dia, pensando seriamente em pular o cardio na academia.");

    mvprintw(9, 1,  "(2) Mago:sempre se interessou pelas coisas ao seu redor, fazendo perguntas");
    mvprintw(10, 1, "    complexas e tentando entender a realidade, porém, muitas vezes, quando vai");
    mvprintw(11, 1, "    ler, se percebe preso em uma página, pois o autor quis dificultar sua vida.");

    mvprintw(13, 1, "(3) Druida: sempre amou a natureza e continua gostando dela, mesmo tendo que");
    mvprintw(14, 1, "    gravar diversas vezes nomes em línguas obscuras como abissal e latim e");
    mvprintw(15, 1, "    entender cada célula de cada ser vivo existente.");

    mvprintw(17, 1, "(4) Bardo: ama a música e as artes, sempre tentando trazer à tona sentimentos");
    mvprintw(18, 1, "    ocultos das pessoas, mesmo que tenha diversas crises e bloqueios criativos,");
    mvprintw(19, 1, "    sempre se perguntando em quem faz o palhaço rir.");

    mvprintw(21, 1, "(5) Inventor: teve de aprender magias puras e a construir geringonças incríveis,");
    mvprintw(22, 1, "    nesse caminho enfrentou várias aventuras difíceis, tais como Cálculo e Física,");
    mvprintw(23, 1, "    quase desistindo do curso e repensando suas escolhas diversas vezes.");


    refresh();

char choice = getch(); // Obtém a escolha do jogador

    switch (choice) {
        case '1':
            player = Player("Barbaro", 350, 30, '1');
            break;
        case '2':
            player = Player("Mago", 200, 45, '2');
            break;
        case '3':
            player = Player("Druida", 300, 25, '3');
            break;
        case '4':
            player = Player("Bardo", 250, 40, '4');
            break;
        case '5':
            player = Player("Inventor", 350, 20, '5');
            break;
        default:
            mvprintw(13, 1, "Personagem inválido. Escolha novamente.");
            refresh();
            selectCharacter(player); // Chama recursivamente se a escolha for inválida
            break;
    } 


}