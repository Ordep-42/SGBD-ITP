#ifndef TABLEOPERATIONS_H
#define TABLEOPERATIONS_H

#include "checks.h"
#include "dataOperations.h"
#include "fileOperations.h"

Tabela criarTabela();
void listarTabelas();
void apagarTabela();
void printarTabela();
void pesquisar();
void IntermediarioPrintarTabela(char *nomeTabela);
void separadorDeLinha(char *nomeTabela);

#endif