# Compilador
CC = gcc

ifeq ($(OS),Windows_NT)
    # Tenta detectar a versão para montar o caminho automaticamente
    PG_VERSION = $(shell psql --version | awk '{print $$3}' | cut -d. -f1)
    PG_BASE = C:/Program Files/PostgreSQL/$(PG_VERSION)

    PG_CFLAGS = -I"$(PG_BASE)/include"
    # IMPORTANTE: No Windows, passamos o caminho da DLL diretamente em vez de -L e -lpq
    PG_LIBS = "$(PG_BASE)/bin/libpq.dll" -lws2_32 -lsecur32 -ladvapi32 -lshell32
    
    # Comando para criar pasta no Windows (w64devkit usa mkdir -p, então mantemos)
    MKDIR = mkdir -p
else
    PG_CONFIG = pg_config
    PG_CFLAGS = -I$(shell $(PG_CONFIG) --includedir)
    PG_LIBS = -L$(shell $(PG_CONFIG) --libdir) -lpq
    MKDIR = mkdir -p
endif

# Flags de compilação
CFLAGS = -Wall -Wextra -Werror -Iinclude -fexec-charset=UTF-8 -g $(PG_CFLAGS)

# Nome do executável final
TARGET = sistema-de-estoque

# Lista de arquivos .c na pasta src
SRC = src/postgres-storage.c src/main.c src/product.c src/terminal-ui.c src/utils.c

# Converte cada arquivo .c em objeto .o na pasta build
OBJ = $(SRC:src/%.c=build/%.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(PG_LIBS) -o $@

build/%.o: src/%.c
	$(MKDIR) build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET).exe

.PHONY: all clean