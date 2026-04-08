# Sistem de Estoque C

Este é um sistema de estoque simples desenvolvido na linguagem C.

As funcionalidade atuais do sistema incluem:

- Cadastro de itens
- Listagem de itens
- Busca de item
- Entrada de itens no estoque
- Saída de itens do estoque

## Estrutura do projeto

O projeto foi dividido em vários arquivo para ser mais escalavel e de fácil manutênção

### Cabeçalhos

Na pasta `include` estão os arquivos de cabeçalho do projeto, que definem as interfaces para as diferentes partes do sistema e as estruturas de dados utilizadas:

- `product.h` -> definição da estrutura de dados do produto e funções relacionadas
- `ui.h` -> definição das funções relacionadas a interface de usuário
- `storage.h` -> definição das funções relacionadas ao armazenamento dos dados
- `utils.h` -> definição de funções utilitárias para o sistema

### Fontes

Na pasta `src` estão os arquivos de código fonte do projeto, que implementam as funcionalidades definidas nos cabeçalhos:

- `main.c` -> fluxo principal da aplicação
- `product.c` -> implmenetação do cabelalho `product.h`
- `terminal-ui.c` -> implementação do cabeçalho `ui.h` para uma interface de terminal
- `postgres-storage.c` -> implementação do cabeçalho `storage.h` para armazenamento em um banco de dados PostgreSQL
- `file-storage.c` -> implementação do cabeçalho `storage.h` para armazenamento em arquivos (Não utilizado atualmente)
- `utils.c` -> implementação do cabeçalho `utils.h`

## Compilação

O `makefile` pode ser executado para compilar o projeto. Para isso é apenas necessário ter instalado o compilador **GCC** e o utilitário **make**.

```bash
make
```

## Execução

Crie a variável de ambiente `DATABASE_URL` com a string de conexão do banco de dados PostgreSQL onde o sistema irá armazenar os dados. Caso não defina a variável, o sistema irá tentar se conectar ao banco de dados usando a string de conexão padrão `postgresql://dev:dev@localhost:5432/sistema_estoque_c`.

Rode as migrações que estão na pasta `migrations` para criar a tabela necessária para o sistema funcionar.

```bash
psql -U user -d database -f migrations/V1__create-table-product.sql
```

Com o programa compilado será gerado um arquivo `sistema-de-estoque` que você pode executar para iniciar o sistema.
