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

// Definição da classe Player para representar o personagem do jogador
class Player {
public:
    string name;
    int health;
    int attack;
    int potionCount;
    int level;
    bool defending;


// Construtor da classe Player para inicializar seus atributos
    Player(string n, int h, int a) : name(n), health(h), attack(a), potionCount(3), level(1), defending(false) {}
};

// Definição da classe Enemy para representar os inimigos
class Enemy {
public:
    string name;
    int health;
    int attack;

// Construtor da classe Enemy para inicializar seus atributos
    Enemy(string n, int h, int a) : name(n), health(h), attack(a) {}
};

// Função para retornar um valor booleano aleatório baseado em uma probabilidade
bool getRandomBool(double probability) {
    return (rand() / static_cast<double>(RAND_MAX)) < probability;
}

// Função para imprimir o status do jogador e do inimigo na tela
void printStatus(Player& player, Enemy& enemy) {
    clear(); // Limpa a tela

    // Imprime uma caixa de menu com as informações de saúde (HP) do jogador e do inimigo
    box(stdscr, 0, 0);
    mvprintw(1, 1, " Jogo RPG - HP de %s: %d  HP de %s: %d", player.name.c_str(), player.health, enemy.name.c_str(), enemy.health);

    // Imprime o avatar do herói
    mvprintw(3, 1, "Herói: ");
    attron(A_BOLD);
    
    // Desenha o avatar do herói
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

    attroff(A_BOLD); // Desativa o atributo de negrito

     // Imprime a mensagem para escolha de ação
    mvprintw(14, 1, "Escolha uma ação (a = atacar, d = defender, u = usar poção): ");
    refresh();
}

// Função para obter o nome do jogador
void getPlayerName(string& playerName) {
    mvprintw(8, 1, "Digite o nome do jogador: ");// Imprime a mensagem para digitar o nome do jogador
    refresh();// Atualiza a tela
    char buffer[50];
    int i = 0;
    
    while (true) {
        int ch = getch(); // Obtém o próximo caractere digitado pelo usuário

        if (ch == '\n' || ch == '\r') {
            buffer[i] = '\0'; // Termina a string com null character
            break;
        } else if (ch == 127 && i > 0) {
            buffer[--i] = '\0'; // Remove o último caractere digitado (tecla backspace)
        } else if (i < 49) {
            buffer[i++] = ch;// Adiciona o caractere ao buffer
            buffer[i] = '\0';// Termina a string com null character
        }

        clear(); // Limpa a tela
        // Imprime a caixa de menu
        box(stdscr, 0, 0); // Desenha a caixa de menu
        mvprintw(1, 1, " Jogo RPG - Digite o nome do jogador: %s", buffer); // Imprime o nome digitado
        refresh();// Atualiza a tela
    }
    playerName = buffer;  // Atualiza o nome do jogador com o valor digitado
}

// Função que representa a vez do jogador
void playerTurn(Player& player, Enemy& enemy) {
    printStatus(player, enemy); // Mostra o status do jogador e inimigo na tela

    char action = getch(); // Obtém a ação escolhida pelo jogador

    // Verifica a ação escolhida e executa a ação correspondente
    if (action == 'a') {// Ataque
        int dano = player.attack;   // Dano base do jogador
        if (getRandomBool(0.2)) {   // Verifica se houve um golpe crítico (20% de chance)
            dano *= 2;              // Dano dobrado em caso de golpe crítico
            mvprintw(16, 1, "Golpe Crítico! Você atacou %s e causou %d de dano!", enemy.name.c_str(), dano); // Exibe mensagem de golpe crítico
        } else {
            enemy.health -= dano;// Reduz a saúde do inimigo pelo dano
            mvprintw(16, 1, "Você atacou %s e causou %d de dano!", enemy.name.c_str(), dano);
        }
    } else if (action == 'd') {// Defesa
        player.defending = true;// Ativa a defesa do jogador
        mvprintw(16, 1, "Você está se defendendo dos ataques de %s.", enemy.name.c_str());
    } else if (action == 'u') { // Uso de poção
        if (player.potionCount > 0) { 
            int cura = 50; // Quantidade de cura da poção
            player.health += cura; // Aumenta a saúde do jogador
            player.potionCount--; // Decrementa o contador de poções
            mvprintw(16, 1, "Você usou uma poção e recuperou %d de HP. Poções restantes: %d", cura, player.potionCount);// Exibe mensagem de uso de poção
        } else {
            mvprintw(16, 1, "Você não tem mais poções!"); // Exibe mensagem se não houver poções disponíveis
        }
    } else {
        mvprintw(16, 1, "Ação inválida. Tente novamente."); // Mensagem para ação inválida
        refresh();
        return;
    }
    mvprintw(17, 1, "Pressione qualquer tecla para continuar...");// Mensagem para continuar
    getch();// Aguarda entrada do usuário
    refresh();// Atualiza a tela
}
// Função que representa a vez do inimigo
void enemyTurn(Player& player, Enemy& enemy) {
    if (player.health > 0) {  // Verifica se o jogador ainda está vivo
        int dano = enemy.attack; // Dano base do inimigo
        if (player.defending) { // Verifica se o jogador está defendendo
            dano /= 2; // Reduz o dano pela metade se o jogador está defendendo
        }
        player.health -= dano; // Reduz a saúde do jogador pelo dano do inimigo
        mvprintw(18, 1, "%s atacou você e causou %d de dano!", enemy.name.c_str(), dano);// Exibe mensagem de ataque
        mvprintw(19, 1, "Pressione qualquer tecla para continuar...");// Mensagem para continuar
        getch();// Aguarda entrada do usuário
    }
    refresh();// Atualiza a tela
}


// Função para evoluir o jogador de nível
void levelUp(Player& player) {
    player.level++;// Incrementa o nível do jogador
    player.attack += 5; // Aumenta o poder de ataque do jogador
    mvprintw(16, 1, "Parabéns! Você subiu para o nível %d!", player.level);// Exibe mensagem de evolução de nível
    mvprintw(17, 1, "Pressione qualquer tecla para continuar...");// Mensagem para continuar
    getch();// Aguarda entrada do usuário
    refresh();// Atualiza a tela
}

// Função que representa a batalha entre o jogador e o inimigo
void battle(Player& player, Enemy& enemy) {
    mvprintw(16, 1, "Você está em batalha com %s!", enemy.name.c_str());// Mensagem de início de batalha
    refresh();// Atualiza a tela

    while (player.health > 0 && enemy.health > 0) { // Enquanto ambos (jogador e inimigo) estiverem vivos
        playerTurn(player, enemy);// Vez do jogador
        if (enemy.health <= 0) {// Se o inimigo estiver derrotado
            mvprintw(16, 1, "Você derrotou %s. Parabéns!", enemy.name.c_str());  // Mensagem de vitória
            if (player.health > 0 && player.level < 3) {
                levelUp(player); // Evolui o jogador se ainda não atingiu o nível máximo
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
    
    // Inicialização do ambiente ncurses
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

// Mensagem de início do jogo
    mvprintw(1, 1, " RPG Game - Torre UFMG!");

// Obter o nome do jogador
    string playerName;
    getPlayerName(playerName);

// Inicialização do jogador e inimigo
    Player player(playerName, 200, 20);
    Enemy enemy("Enemy", 80, 15);

// Mensagem de entrada no mundo de aventuras
    mvprintw(3, 1, "Voce entrou num mundo de aventuras!");

// Semente para gerar números aleatórios
    srand(time(0));

// Loop principal do jogo enquanto o jogador está vivo e não atingiu o nível máximo
    while (player.health > 0 && player.level < 3) {
         // Lógica das batalhas
        battle(player, enemy);


// Lógica para preparar para a próxima batalha
        if (player.health > 0 && player.level < 3) {
            mvprintw(15, 1, "Voce prepara para proxima batalha!");
            refresh();
            string enemyNames[] = { "Orc", "Dragon", "Skeleton" };
            string randomEnemyName = enemyNames[rand() % 3];
            int randomEnemyHealth = rand() % 100 + 50;
            int randomEnemyAttack = rand() % 20 + 10;

// Geração aleatória do inimigo para a próxima batalha
            enemy = Enemy(randomEnemyName, randomEnemyHealth, randomEnemyAttack);

// Mensagem sobre o encontro do jogador com o novo inimigo
            mvprintw(15, 1, "Voce encontra um %s!", enemy.name.c_str());
            refresh();
        }
    }

// Mensagem final do jogo dependendo do resultado
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


