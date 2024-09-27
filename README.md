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
- `file-storage.c` -> funções relacionadas a manupilação de arquivos para o armazenamento do sistema

## Compilação

O projeto foi desenvolvido no Windows e o arquivo `compile.bat` pode ser executado para compilar o programa. Para isso é apenas necessário ter instalado o compilador GCC.

```bash
compile.bat
```

## Execução

Com o programa compilado será gerado um arquivo `sistema-de-estoque.exe` que você pode executar para iniciar o sistema.
