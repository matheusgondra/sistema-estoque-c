*![English](https://flagcdn.com/20x15/us.png) [EN](README.md)* |  *![Português](https://flagcdn.com/20x15/br.png) [PT-BR](README.pt.md)*

---

# Sistema de Estoque C

Este é um sistema de estoque simples desenvolvido na linguagem C.

As funcionalidades atuais do sistema incluem:

- Cadastro de itens
- Listagem de itens
- Busca de item
- Entrada de itens no estoque
- Saída de itens do estoque

## Estrutura do projeto

O projeto foi dividido em vários arquivos para ser mais escalável e de fácil manutenção.

### Cabeçalhos

Na pasta `include` estão os arquivos de cabeçalho do projeto, que definem as interfaces para as diferentes partes do sistema e as estruturas de dados utilizadas:

- `product.h` -> definição da estrutura de dados do produto e funções relacionadas
- `ui.h` -> definição das funções relacionadas à interface de usuário
- `storage.h` -> definição das funções relacionadas ao armazenamento dos dados
- `utils.h` -> definição de funções utilitárias para o sistema

### Fontes

Na pasta `src` estão os arquivos de código fonte do projeto, que implementam as funcionalidades definidas nos cabeçalhos:

- `main.c` -> fluxo principal da aplicação
- `product.c` -> implementação do cabeçalho `product.h`
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

Crie a variável de ambiente `DATABASE_URL` com a string de conexão do banco de dados PostgreSQL onde o sistema irá armazenar os dados. Caso não defina a variável, o sistema irá tentar se conectar ao banco de dados usando a string de conexão padrão `postgresql://dev:dev@localhost:5432/sistema_estoque_c`. As tabelas necessárias serão criadas para a execução do sistema.

Com o programa compilado será gerado um arquivo `sistema-de-estoque` que você pode executar para iniciar o sistema.

## CI/CD

O projeto possui um workflow de CI/CD no GitHub Actions em `.github/workflows/build.yml`.

O pipeline é acionado em:

- `push` na branch `main`
- `pull_request` para a branch `main`
- `push` de tags no padrão `v*` (ex.: `v1.0.0`)

Etapas executadas:

- Build no Linux (`ubuntu-latest`) com `gcc`, `make` e `libpq-dev`
- Build no Windows (`windows-latest` com MSYS2)
- Upload dos artefatos:
	- `sistema-estoque-linux` (`sistema-de-estoque`)
	- `sistema-estoque-windows` (`sistema-de-estoque.exe`)

Quando uma tag `v*` é publicada, o job de release cria automaticamente uma Release no GitHub e anexa os executáveis Linux e Windows.

## Funcionalidades Futuras

As seguintes funcionalidades serão integradas no projeto futuramente. Caso tenha sugestões de funcionalidades, abra uma issue no repositório contando sobre ela.

- Interface gráfica.
