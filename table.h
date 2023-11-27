#ifndef TABLE_H
#define TABLE_H

#define MAX_NAME_SIZE 50

typedef enum {
    UNSIGNED_INT,
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    STRING
} Datatype;

typedef struct {
    Datatype tipo;
    char nome[MAX_NAME_SIZE];
} Coluna;

typedef struct {
    char nome[MAX_NAME_SIZE];
    Coluna colunas[10];
    char coluna_PK[MAX_NAME_SIZE];
    unsigned int num_colunas;
} Tabela;

Tabela criar_tabela();
void listar_tabelas();
void apagar_tabela(Tabela *);
void listar_dados(Tabela *);

#endif