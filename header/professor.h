#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "arquivo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct no{
    int cod_prof;
    char nome_prof[MAX];
    int pos_prox;   // Posição (dentro do arquivo binário) do próximo contato
}Professor;

// Lê o professor do arquivo binário
// Entrada: Arquivo binário e a posição no arquivo
// Retorno: Retorna o professor lido
// Pré-condição: O aruivo binário tem que ser diferente de nulo
// Pós-condição: o professor é lido
Professor* read_Professor(FILE* arq, int pos);

// Escreve o professor no arquivo binário
// Entrada: Arquivo binário, o professor e a posição no arquivo
// Retorno: Nenhum
// Pré-condição: O arquvo e o professor serem diferente de nulo
// Pós-condição: o professor é escrito no arquivo 
void write_Professor(FILE* arq, Professor* cont, int pos);

// Busca a posição disponível dentro do arquivo binário
// Entrada: Arquivo binário e o cabeçalho
// Retorno: Retorna a próxima posição disponível para escrever um novo professor
// Pré-condição: O arquvo existir
// Pós-condição: A posição é retornada para fazer a inserção
int buscar_pos_disProf(FILE* arq, cabecario* cab);

// Cria um curso na estrutura de curso
// Entrada: O codigo do professor e o nome do professor
// Retorno: Retorna o professor
// Pré-condição: Nenhuma
// Pós-condição: Cria o professor para fazer a inserção
Professor* criar_Professor(int codProfessor, char* nomeProfessor);

// Abre o arquivo o arquivo binário ou cria o arquivo se ele não existe
// Entrada: Nome do arquivo binário
// Retorno: Arquivo binário
// Pré-condição: O nome deve ser próprio para um arquivo binário
// Pós-condição: O arquivo binário é criado ou lido
FILE* open_arqProf(char* str);

// Adiciona um novo professor em ordem de codigo do professor
// Entrada: Arquivo do professor e a struct professor
// Retorno: Nenhum
// Pré-condição: O arquivo binário deve ser próprio para manipular o professor
// Pós-condição: O contato com as informações fornecidas será adicionado no professor
void adicionar_Professor(FILE* arq, Professor *prof);

// Cadastra umo professor com os dados do teclado 
// Entrada: A struct dos arquivos
// Retorno: Nenhum
// Pré-condição: A estrutura do arquvo tem existir
// Pós-condição: Adicionar o professor no arquivo binário
void cadastrar_Professor(arquivos* arq);

// Imprime as professor existentes
// Entrada: Arquivo dos professor
// Retorno: Nenhum
// Pré-condição: O arquivo binário existir
// Pós-condição: As professors seram impresso na tela
void imprimir_Professor(FILE* arq);

#endif