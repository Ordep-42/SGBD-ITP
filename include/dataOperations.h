#ifndef DATAOPERATIONS_H
#define DATAOPERATIONS_H

#include "fileOperations.h"

void salvarNoHeader(char* tableNome);
void salvarMetadados(Tabela* table);
void apagarTabelaDoHeader(char* nomeTabela);

#endif