# Makefile para compilar o jogo e os testes

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -lncurses

SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = test
BUILD_DIR = build
BIN_DIR = bin

# Arquivos fonte
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)

# Arquivos objeto
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_FILES))

# Nome do executável do jogo
GAME_EXEC = $(BIN_DIR)/game

# Nome do executável dos testes
TEST_EXEC = $(BIN_DIR)/tests

# Alvos padrão
all: game tests

# Compilar o jogo
game: $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $(OBJ_FILES) -o $(GAME_EXEC) $(LDFLAGS)

# Compilar os testes
tests: $(TEST_OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $(TEST_OBJ_FILES) -o $(TEST_EXEC) $(LDFLAGS)
	$(TEST_EXEC)
	

# Alvo para limpar os arquivos gerados
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

run: game
	$(GAME_EXEC)


# Compilar os arquivos fonte para arquivos objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compilar os arquivos de teste para arquivos objeto
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@
	


.PHONY: all game tests clean



