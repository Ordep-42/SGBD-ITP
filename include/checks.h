#ifndef CHECKS_H
#define CHECKS_H

#include "fileOperations.h"

int checarTabelaExiste(char *nome);
int checarColunaExiste(char *nome, Tabela *table);
int checarColunaUIntExiste(Tabela *table);
int checarPKExiste(char *nome, unsigned int valor, unsigned int colunaPK);
void checarNomePK(Tabela *table);
void checarTipoPK(Tabela *table);

#endif