#ifndef TABLEOPERATIONS_H
#define TABLEOPERATIONS_H

#include <stdio.h>
#include <string.h>

#include "tableChecks.h"
#include "fileOperations.h"
#include "dataOperations.h"

Tabela criarTabela();
void listarTabelas();
void apagarTabela(Tabela *table);

#endif