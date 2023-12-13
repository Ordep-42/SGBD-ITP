#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define caminhoDados "./data/"
#define extensao ".txt"

int salvarEmArquivo(char *nomeArquivo, char *conteudo, char *modo);
char *lerArquivo(char *nomeArquivo);
char *gerarCaminhoDeArquivo(char *nome);
char **separarString(char *string);
void apagarLinhaPorConteudo(char *nomeArquivo, char *conteudoLinha);
int contarLinhas(char *conteudo);
int contarVirgulas(char *conteudo);

#endif