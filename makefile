# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -Werror -Iinclude

# Nome do executável final
TARGET = sistema-de-estoque.exe

# Lista de arquivos .c na pasta src
SRC = src/file-storage.c src/main.c src/product.c src/terminal-ui.c src/utils.c

# Converte cada arquivo .c em objeto .o na pasta build
OBJ = $(SRC:src/%.c=build/%.o)

# Alvo padrão
all: $(TARGET)

# Gera o executável a partir dos objetos
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

# Regra para compilar cada arquivo .c em .o
build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	del /Q build\*.o $(TARGET)

.PHONY: all clean
