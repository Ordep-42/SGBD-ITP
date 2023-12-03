#ifndef TABLEOPERATIONS_H
#define TABLEOPERATIONS_H

#include <stdio.h>
#include <string.h>

#include "database.h"
#include "fileOperations.h"

Tabela criarTabela();
int checarTabelaExiste(char* nome, Tabela* table);
int checarColunaExiste(char* nome, Tabela* table);
void checarNomePK(Tabela* table);
void checarTipoPK(Tabela* table);
void listarTabelas();
void apagarTabela(Tabela* table);

#endif