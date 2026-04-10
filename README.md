*![English](https://flagcdn.com/20x15/us.png) [EN](README.md)* |  *![Português](https://flagcdn.com/20x15/br.png) [PT-BR](README.pt.md)*

--- 

# C Stock Management System

This is a simple stock management system developed in C.

The system's current features include:

- Item registration
- Item listing
- Item search
- Stock entry (Inbound)
- Stock exit (Outbound)

## Project Structure

The project was divided into several files to be more scalable and easier to maintain.

### Headers

The `include` folder contains the project's header files, which define the interfaces for the different parts of the system and the data structures used:

- `product.h` -> definition of the product data structure and related functions
- `ui.h` -> definition of user interface related functions
- `storage.h` -> definition of data storage related functions
- `utils.h` -> definition of utility functions for the system

### Sources

The `src` folder contains the project's source code files, which implement the features defined in the headers:

- `main.c` -> main application flow
- `product.c` -> implementation of the `product.h` header
- `terminal-ui.c` -> implementation of the `ui.h` header for a terminal interface
- `postgres-storage.c` -> implementation of the `storage.h` header for PostgreSQL database storage
- `file-storage.c` -> implementation of the `storage.h` header for file storage (Currently not used)
- `utils.c` -> implementation of the `utils.h` header

## Compilation

The `makefile` can be executed to compile the project. To do this, you only need to have the **GCC** compiler and the **make** utility installed.

```bash
make
```

## Execution

Create the `DATABASE_URL` environment variable with the PostgreSQL database connection string where the system will store its data. If you do not define this variable, the system will attempt to connect to the database using the default connection string `postgresql://dev:dev@localhost:5432/sistema_estoque_c`. The necessary tables will be created automatically when the system runs.

Once the program is compiled, a `sistema-de-estoque` executable file will be generated, which you can run to start the system.

## CI/CD

The project has a CI/CD workflow in GitHub Actions at `.github/workflows/build.yml`.

The pipeline runs on:

- `push` to the `main` branch
- `pull_request` targeting the `main` branch
- `push` of tags matching `v*` (e.g. `v1.0.0`)

Executed steps:

- Linux build (`ubuntu-latest`) with `gcc`, `make`, and `libpq-dev`
- Windows build (`windows-latest` with MSYS2)
- Artifact upload:
	- `sistema-estoque-linux` (`sistema-de-estoque`)
	- `sistema-estoque-windows` (`sistema-de-estoque.exe`)

When a `v*` tag is published, the release job automatically creates a GitHub Release and attaches both Linux and Windows executables.

## Future Features

The following features will be integrated into the project in the future. If you have any feature suggestions, please open an issue in the repository telling us about it.

- Graphical interface.
