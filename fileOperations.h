#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int salvarEmArquivo(char *nomeArquivo, char *conteudo, char *modo);
char* lerArquivo(char *nomeArquivo);

#endif