#ifndef TABLE_H
#define TABLE_H

#define MAX_NAME_SIZE 50

typedef struct cell {
    union {
        unsigned int unsigned_int;
        int int_;
        float float_;
        double double_;
        char char_;
        char *string;
    } valor;
} Celula;

typedef struct row {
    Celula *celulas;
    unsigned int num_celulas;
} Linha;

typedef enum types {
    UNSIGNED_INT,
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    STRING
} Datatype;

typedef struct col {
    char nome[MAX_NAME_SIZE];
    Datatype tipo;
} Coluna;

typedef struct table {
    char nome[MAX_NAME_SIZE];
    Coluna colunas[10];
    char coluna_PK[MAX_NAME_SIZE];
    unsigned int num_colunas;
    Linha *linhas;
    unsigned int num_linhas;
} Tabela;

int initDatabase();

#endif