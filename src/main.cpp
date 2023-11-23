//Lugar onde vamos realmente escrever o funcionamento do jogo usando as bibliotecas disponíveis. Por favor, se atentem a fazer bons comentarios ao longo do codigo! Bom trabalho.
//Grupo 3 - Jogo de RPG - Arthur Augusto Paiva Lemos, Filipe Henrique Nunes, Luisa Canielo de Carvalho, Ricardo Jianhong Li e Thales Eduardo de Castro Andrade

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
// Use esse no Linux:
//#include <ncurses.h>
// Comando para compilação no Linux: g++ -std=c++17 main.cpp -o (nome) -lncurses
// Comando para executar: ./(nome)
//Use esse para Windows:
#include <ncurses/ncurses.h>
// Comando para compilação no windows: g++ main.cpp -o test.exe -lncurses -DNCURSES_STATIC 
// Comando para executar: teste.exe

using namespace std;

class Player {
public:
    string name;
    int health;
    int attack;
    int potionCount;
    int level;
    bool defending;

    Player(string n, int h, int a) : name(n), health(h), attack(a), potionCount(3), level(1), defending(false) {}
};

class Enemy {
public:
    string name;
    int health;
    int attack;

    Enemy(string n, int h, int a) : name(n), health(h), attack(a) {}
};

bool getRandomBool(double probability) {
    return (rand() / static_cast<double>(RAND_MAX)) < probability;
}

void printStatus(Player& player, Enemy& enemy) {
    clear();

    // Imprime a caixa de menu
    box(stdscr, 0, 0);
    mvprintw(1, 1, " Jogo RPG - HP de %s: %d  HP de %s: %d", player.name.c_str(), player.health, enemy.name.c_str(), enemy.health);

    // Imprime o avatar do herói
    mvprintw(3, 1, "Herói: ");
    attron(A_BOLD);
    mvprintw(3, 7, R"(
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

    attroff(A_BOLD);

    // Imprime o conteúdo do jogo
    mvprintw(14, 1, "Escolha uma ação (a = atacar, d = defender, u = usar poção): ");
    refresh();
}

void getPlayerName(string& playerName) {
    mvprintw(8, 1, "Digite o nome do jogador: ");
    refresh();
    char buffer[50];
    int i = 0;
    while (true) {
        int ch = getch();

        if (ch == '\n' || ch == '\r') {
            buffer[i] = '\0';
            break;
        } else if (ch == 127 && i > 0) {
            buffer[--i] = '\0';
        } else if (i < 49) {
            buffer[i++] = ch;
            buffer[i] = '\0';
        }

        clear();
        // Imprime a caixa de menu
        box(stdscr, 0, 0);
        mvprintw(1, 1, " Jogo RPG - Digite o nome do jogador: %s", buffer);
        refresh();
    }
    playerName = buffer;
}

void playerTurn(Player& player, Enemy& enemy) {
    printStatus(player, enemy);

    char action = getch();

    if (action == 'a') {
        int dano = player.attack;
        if (getRandomBool(0.2)) {
            dano *= 2;
            mvprintw(16, 1, "Golpe Crítico! Você atacou %s e causou %d de dano!", enemy.name.c_str(), dano);
        } else {
            enemy.health -= dano;
            mvprintw(16, 1, "Você atacou %s e causou %d de dano!", enemy.name.c_str(), dano);
        }
    } else if (action == 'd') {
        player.defending = true;
        mvprintw(16, 1, "Você está se defendendo dos ataques de %s.", enemy.name.c_str());
    } else if (action == 'u') {
        if (player.potionCount > 0) {
            int cura = 50;
            player.health += cura;
            player.potionCount--;
            mvprintw(16, 1, "Você usou uma poção e recuperou %d de HP. Poções restantes: %d", cura, player.potionCount);
        } else {
            mvprintw(16, 1, "Você não tem mais poções!");
        }
    } else {
        mvprintw(16, 1, "Ação inválida. Tente novamente.");
        refresh();
        return;
    }
    mvprintw(17, 1, "Pressione qualquer tecla para continuar...");
    getch();
    refresh();
}

void enemyTurn(Player& player, Enemy& enemy) {
    if (player.health > 0) {
        int dano = enemy.attack;
        if (player.defending) {
            dano /= 2;
        }
        player.health -= dano;
        mvprintw(18, 1, "%s atacou você e causou %d de dano!", enemy.name.c_str(), dano);
        mvprintw(19, 1, "Pressione qualquer tecla para continuar...");
        getch();
    }
    refresh();
}

void levelUp(Player& player) {
    player.level++;
    player.attack += 5;
    mvprintw(16, 1, "Parabéns! Você subiu para o nível %d!", player.level);
    mvprintw(17, 1, "Pressione qualquer tecla para continuar...");
    getch();
    refresh();
}

void battle(Player& player, Enemy& enemy) {
    mvprintw(16, 1, "Você está em batalha com %s!", enemy.name.c_str());
    refresh();

    while (player.health > 0 && enemy.health > 0) {
        playerTurn(player, enemy);
        if (enemy.health <= 0) {
            mvprintw(16, 1, "Você derrotou %s. Parabéns!", enemy.name.c_str());
            if (player.health > 0 && player.level < 3) {
                levelUp(player);
            }
            break;
        }

        enemyTurn(player, enemy);
        if (player.health <= 0) {
            mvprintw(16, 1, "Você foi derrotado por %s. Fim de Jogo!", enemy.name.c_str());
            break;
        }
    }
}



int main() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    mvprintw(1, 1, " RPG Game - Torre UFMG!");

    string playerName;
    getPlayerName(playerName);

    Player player(playerName, 200, 20);
    Enemy enemy("Enemy", 80, 15);

    mvprintw(3, 1, "Voce entrou num mundo de aventuras!");

    srand(time(0));

    while (player.health > 0 && player.level < 3) {
        battle(player, enemy);

        if (player.health > 0 && player.level < 3) {
            mvprintw(15, 1, "Voce prepara para proxima batalha!");
            refresh();
            string enemyNames[] = { "Orc", "Dragon", "Skeleton" };
            string randomEnemyName = enemyNames[rand() % 3];
            int randomEnemyHealth = rand() % 100 + 50;
            int randomEnemyAttack = rand() % 20 + 10;

            enemy = Enemy(randomEnemyName, randomEnemyHealth, randomEnemyAttack);

            mvprintw(15, 1, "Voce encontra um %s!", enemy.name.c_str());
            refresh();
        }
    }

    if (player.level == 3) {
        mvprintw(16, 1, "Parabens! Voce atingiu o nivel maximo e completou o jogo!");
    } else {
        mvprintw(16, 1, "Game Over!");
    }

    refresh();
    getch();
    endwin();

    return 0;
}


