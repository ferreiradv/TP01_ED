CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g -I include

BIN_DIR = bin
EXEC = $(BIN_DIR)/tp1.out

# Define as pastas
OBJ_DIR = obj
SRC_DIR = src

# Define caminho dos aruivos .o
OBJS = $(OBJ_DIR)/Main.o $(OBJ_DIR)/Acao.o $(OBJ_DIR)/Cliente.o $(OBJ_DIR)/array_dinamico.o $(OBJ_DIR)/Ranking.o

# comando make all
all: $(EXEC)

$(EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
