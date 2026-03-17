# Compilador
CC = gcc

ifeq ($(OS),Windows_NT)
	PG_VERSION = $(shell psql --version | awk '{print $$3}' | cut -d. -f1)
	PG_BASE = C:/Program Files/PostgreSQL/$(PG_VERSION)
	
	PG_CFLAGS = -I"$(PG_BASE)/include"
	PG_LIBS = "$(PG_BASE)/bin/libpq.dll" -lws2_32 -lsecur32 -ladvapi32 -lshell32
	MKDIR = mkdir -p
else
	PG_CONFIG = pg_config
	PG_CFLAGS = -I$(shell $(PG_CONFIG) --includedir)
	PG_LIBS = -L$(shell $(PG_CONFIG) --libdir) -lpq
	MKDIR = mkdir -p
endif

# --- NOVAS CONFIGURAÇÕES DO GTK4 ---
GTK_CFLAGS = $(shell pkg-config --cflags gtk4)
GTK_LIBS = $(shell pkg-config --libs gtk4)

# Flags de compilação base (agora inclui as flags do GTK)
CFLAGS = -Wall -Wextra -Werror -Iinclude -fexec-charset=UTF-8 -g $(PG_CFLAGS) $(GTK_CFLAGS)

# Nomes dos executáveis finais
TARGET_CLI = sistema-de-estoque
TARGET_GUI = sistema-de-estoque-gui

# 1. Arquivos centrais (Lógica e Banco de Dados) compartilhado por ambos
SRC_CORE = src/postgres-storage.c src/product.c src/utils.c

# 2. Arquivos exclusivos do Terminal
SRC_CLI = src/main.c src/terminal-ui.c $(SRC_CORE)
OBJ_CLI = $(SRC_CLI:src/%.c=build/%.o)

# 3. Arquivos exclusivos da Interface Gráfica
SRC_GUI = src/main-gtk.c $(SRC_CORE)
OBJ_GUI = $(SRC_GUI:src/%.c=build/%.o)

# Regra padrão compila ambos
all: cli gui

# Regra para compilar apenas o terminal
cli: $(TARGET_CLI)

# Regra para compilar apenas a interface gráfica
gui: $(TARGET_GUI)

# Como "linkar" o executável do Terminal
$(TARGET_CLI): $(OBJ_CLI)
	$(CC) $(OBJ_CLI) $(PG_LIBS) -o $@

# Como "linkar" o executável da Interface Gráfica (Adiciona o GTK_LIBS)
$(TARGET_GUI): $(OBJ_GUI)
	$(CC) $(OBJ_GUI) $(PG_LIBS) $(GTK_LIBS) -o $@

# Regra genérica para transformar .c em .o
build/%.o: src/%.c
	$(MKDIR) build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET_CLI).exe $(TARGET_GUI).exe $(TARGET_CLI) $(TARGET_GUI)

.PHONY: all cli gui clean