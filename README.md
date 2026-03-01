# Sistem de Estoque C

Este é um sistema de estoque simples para Windows desenvolvido na linguagem C.

As funcionalidade atuais do sistema incluem:

- Cadastro de itens
- Listagem de itens
- Busca de item
- Entrada de itens no estoque
- Saída de itens do estoque

## Estrutura do projeto

O projeto foi dividido em vários arquivo para ser mais escalavel e de fácil manutênção

- `main.c` -> fluxo principal da aplicação
- `product.c` -> funções relacionadas a manipulação de produtos
- `terminal-ui.c` -> funções relacionadas a interface de usuário no terminal
- `postgres-storage.c` -> funções relacionadas ao PostgreSQL para o armazenamento do sistema
- `utils.c` -> funções utilitárias para o sistema

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
