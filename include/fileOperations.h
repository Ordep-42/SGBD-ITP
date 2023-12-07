#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define caminhoDados "./data/"
#define extensao ".txt"

int salvarEmArquivo(char *nomeArquivo, char *conteudo, char *modo);
char* lerArquivo(char *nomeArquivo);
char* gerarCaminhoDeArquivo(char* nome);
void apagarLinhaEmArquivo(char* nomeArquivo, int linha);

#endif