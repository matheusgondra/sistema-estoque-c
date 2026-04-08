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

Create the `DATABASE_URL` environment variable with the PostgreSQL database connection string where the system will store its data. If you do not define this variable, the system will attempt to connect to the database using the default connection string `postgresql://dev:dev@localhost:5432/sistema_estoque_c`.

Run the migrations located in the `migrations` folder to create the necessary tables for the system to function.

```bash
psql -U user -d database -f migrations/V1__create-table-product.sql
```

Once the program is compiled, a `sistema-de-estoque` executable file will be generated, which you can run to start the system.

## Future Features

The following features will be integrated into the project in the future. If you have any feature suggestions, please open an issue in the repository telling us about it.

- Graphical interface.
