#ifndef TABLE_H
#define TABLE_H

#include "ANSI-codes.h"

#define MAX_NAME_SIZE 50
#define separador "====================================\n"

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
} Tabela;

#endif