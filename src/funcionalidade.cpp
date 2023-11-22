//Lugar onde as funcoes de funcionalidades estarao localizados

//#include <string>
//#include <unordered_map>

class Arma {
public:
    std::string nome;
    int dano;

    Arma(const std::string& n, int d) : nome(n), dano(d) {}
};

class WeaponManager {
private:
    std::unordered_map<std::string, Arma> armas;

public:
    WeaponManager() {
        // Adicionando armas e seus danos ao gerenciador de armas
        armas.emplace("Machado de cobre", Arma("Machado de cobre", 12));
        armas.emplace("Machado de ferro", Arma("Machado de ferro", 24));
        armas.emplace("Machado de ouro", Arma("Machado de ouro", 48));

        armas.emplace("Chave inglesa enferrujada", Arma("Chave inglesa enferrujada", 8));
        armas.emplace("Chave inglesa polida", Arma("Chave inglesa polida", 10));
        armas.emplace("Chave inglesa reluzente", Arma("Chave inglesa reluzente", 20));

        armas.emplace("Rapieira de Pedra", Arma("Rapieira de Pedra", 8));
        armas.emplace("Rapieira de Quartzo", Arma("Rapieira de Quartzo", 10));
        armas.emplace("Rapieira de Obsidiana", Arma("Rapieira de Obsidiana", 20));
    }

    // Função para obter uma arma pelo nome
    Arma getArma(const std::string& nomeArma) {
        if (armas.find(nomeArma) != armas.end()) {
            return armas[nomeArma];
        } else {
            // Caso a arma não exista, retornar uma arma padrão (nome vazio e dano 0)
            return Arma("", 0);
        }
    }
};





class Magia {
public:
    std::string nome;
    int dano;

    Magia(const std::string& n, int d) : nome(n), dano(d) {}
};

class Gerenciador_Magia {
private:
    std::unordered_map<std::string, Magia> magias;

public:
    Gerenciador_Magia() {
        // Inventor
        magias.emplace("Raio Chocante", Magia("Raio Chocante", 6));
        magias.emplace("Algoritmo ancestral", Magia("Algoritmo ancestral", 24));

        // Druida
        magias.emplace("Raio Ácido", Magia("Raio Ácido", 6));

        // Mago
        magias.emplace("Projétil Verde", Magia("Projétil Verde", 8));
        magias.emplace("Raio de Gelo", Magia("Raio de Gelo", 6));
        magias.emplace("Ventos uivantes", Magia("Ventos uivantes", 10));
        magias.emplace("Choque Avassalador", Magia("Choque Avassalador", 16));
        magias.emplace("Bola de Fogo", Magia("Bola de Fogo", 48));

        // Bardo
        magias.emplace("Notas falhas", Magia("Notas falhas", 6));
        magias.emplace("Poema ofensivo", Magia("Poema ofensivo", 8));
        magias.emplace("Spray colorido", Magia("Spray colorido", 10));
        magias.emplace("Canção do Terror", Magia("Canção do Terror", 16));
        magias.emplace("Dança Forçada", Magia("Dança Forçada", 48));
    }

    // Função para obter uma magia pelo nome
    Magia getMagia(const std::string& nomeMagia) {
        if (magias.find(nomeMagia) != magias.end()) {
            return magias[nomeMagia];
        } else {
            // Caso a magia não exista, retornar uma magia padrão (nome vazio e dano 0)
            return Magia("", 0);
        }
    }
};