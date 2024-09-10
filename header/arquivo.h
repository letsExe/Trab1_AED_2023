#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    FILE *file_curso;
    FILE *file_prof;
    FILE *file_disc;
    FILE *file_disc_minis;
} arquivos;

typedef struct{
    int pos_cabeca; // Posição (dentro do arq. bin.) do primeiro elemento da lista (cabeça da lista)
    int pos_topo;   // Primeira posição (dentro do arq. bin.) que está vazia, ou seja, em que nada foi escrito ainda
    int pos_livre;  // Posição (dentro do arq. bin.) que tem curso removido, ou seja, é possível reescrever dados nessa posição
} cabecario;

// Escreve o cabeçalho
// Entrada: Arquivo binário e o cabeçalho
// Retorno: Nenhum
// Pré-condição: O arquvo  serem diferente de nulo
// Pós-condição: O cabeçalho é escrito
void write_cab(FILE* arq, cabecario* cab);

// Lê a o cabeçalho
// Entrada: Arquivo binário
// Retorno: Retorna o cabeçaçho lido
// Pré-condição: O arquivo binário tem que ser diferente de nulo
// Pós-condição: O cabeçalho é lido
cabecario* read_cab(FILE* arq);

// Le o arquivo .txt em lote
// Entrada: Uma string com o nome do arquivo e o arquivo
// Retorno: Nenhum
// Pré-condição: O arquvo e a disciplina ministrada serem diferente de nulo
// Pós-condição: a disciplina ministrada é escrito no arquivo 
arquivos* ler_arquivo(char *arquivo, arquivos *arq);

#endif