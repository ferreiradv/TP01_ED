CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g -I include
EXEC = tp

# Define as pastas
OBJ_DIR = obj
SRC_DIR = src

# Define caminho dos aruivos .o
OBJS = $(OBJ_DIR)/Main.o $(OBJ_DIR)/Acao.o $(OBJ_DIR)/Cliente.o $(OBJ_DIR)/array_dinamico.o

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(EXEC)