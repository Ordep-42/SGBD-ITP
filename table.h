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
        char string[MAX_NAME_SIZE];
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
    Datatype tipo;
    char nome[MAX_NAME_SIZE];
} Coluna;

typedef struct table {
    char nome[MAX_NAME_SIZE];
    Coluna colunas[10];
    char coluna_PK[MAX_NAME_SIZE];
    unsigned int num_colunas;
    Linha linhas[10];
    unsigned int num_linhas;
} Tabela;

Tabela criar_tabela();
void checar_nome_PK(Tabela*);
void checar_tipo_PK(Tabela*);
void listar_tabelas();
void apagar_tabela(Tabela*);
void listar_dados(Tabela*);
void adicionar_linha(Tabela*);

#endif