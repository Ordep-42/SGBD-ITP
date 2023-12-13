#ifndef TABLE_H
#define TABLE_H

#define MAX_NAME_SIZE 50

#define separador "====================================\n"

typedef struct cell {
    union {
        unsigned int unsignedInt;
        int int_;
        float float_;
        double double_;
        char char_;
        char *string;
    } valor;
} Celula;

typedef struct row {
    Celula *celulas;
    unsigned int numCelulas;
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
    char colunaPK[MAX_NAME_SIZE];
    unsigned int numColunas;
    Linha *linhas;
    unsigned int numLinhas;
} Tabela;

#endif