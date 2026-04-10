# Compilador
CC = gcc

ifeq ($(OS),Windows_NT)
    # Se a variável MSYSTEM estiver definida, estamos no MSYS2 (GitHub Actions)
    ifdef MSYSTEM
        PG_CONFIG = pg_config
        PG_CFLAGS = -I$(shell $(PG_CONFIG) --includedir)
        PG_LIBS = -L$(shell $(PG_CONFIG) --libdir) -lpq
        MKDIR = mkdir -p
    else
        # Ambiente local do desenvolvedor (Windows nativo)
        PG_VERSION = $(shell psql --version | awk '{print $$3}' | cut -d. -f1)
        PG_BASE = C:/Program Files/PostgreSQL/$(PG_VERSION)
        PG_CFLAGS = -I"$(PG_BASE)/include"
        PG_LIBS = "$(PG_BASE)/bin/libpq.dll" -lws2_32 -lsecur32 -ladvapi32 -lshell32
        MKDIR = mkdir -p
    endif
else
    # Configuração Padrão Linux
    PG_CONFIG = pg_config
    PG_CFLAGS = -I$(shell $(PG_CONFIG) --includedir)
    PG_LIBS = -L$(shell $(PG_CONFIG) --libdir) -lpq
    MKDIR = mkdir -p
endif

CVERSION = c23

# Flags de compilação
CFLAGS = -Wall -Wextra -Werror -Iinclude -fexec-charset=UTF-8 -g $(PG_CFLAGS) -std=$(CVERSION)

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