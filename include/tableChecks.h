#ifndef TABLECHECKS_H
#define TABLECHECKS_H

#include "database.h"
#include <string.h>

int checarTabelaExiste(char *nome, Tabela *table);
int checarColunaExiste(char *nome, Tabela *table);
int checarColunaUIntExiste(Tabela *table);
void checarNomePK(Tabela *table);
void checarTipoPK(Tabela *table);

#endif