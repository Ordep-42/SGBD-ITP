#ifndef TABLEOPERATIONS_H
#define TABLEOPERATIONS_H

#include <stdio.h>
#include <string.h>

#include "database.h"
#include "fileOperations.h"

Tabela criarTabela();
void checarNomePK(Tabela*);
void checarTipoPK(Tabela*);
void listarTabelas();
void apagarTabela(Tabela*);

#endif