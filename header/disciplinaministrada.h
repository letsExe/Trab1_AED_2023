#ifndef DISCIPLINAMINISTRADA_H
#define DISCIPLINAMINISTRADA_H

#include "arquivo.h"
#include "disciplinaministrada.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int cod_disc;
    int ano_letivo;
    int cod_prof;
    int pos_prox;   // Posição (dentro do arquivo binário) do próximo contato
}DisciplinaMinstrada;

// Lê a disciplina ministrada do arquivo binário
// Entrada: Arquivo binário e a posição no arquivo
// Retorno: Retorna a disciplina ministrada lida
// Pré-condição: O aruivo binário tem que ser diferente de nulo
// Pós-condição: a disciplina é lido
DisciplinaMinstrada* read_DisciplinaMinstrada(FILE* arq, int pos);

// Escreve a disciplina ministrada no arquivo binário
// Entrada: Arquivo binário, a disciplina e a posição no arquivo
// Retorno: Nenhum
// Pré-condição: O arquvo e a disciplina ministrada serem diferente de nulo
// Pós-condição: a disciplina ministrada é escrito no arquivo 
void write_DisciplinaMinstrada(FILE* arq, DisciplinaMinstrada* cont, int pos);

// Busca a posição disponível dentro do arquivo binário
// Entrada: Arquivo binário e o cabeçalho
// Retorno: Retorna a próxima posição disponível para escrever um nova disciplina
// Pré-condição: O arquvo existir
// Pós-condição: A posição é retornada para fazer a inserção
int buscar_pos_disDistribucao(FILE* arq, cabecario* cab);

// Cria uma disciplina ministrada na estrutura das disciplina ministrada
// Entrada: O codigo da disciplina, o ano letivo e o codigo do professor
// Retorno: Retorna a disciplina ministrada
// Pré-condição: Nenhuma
// Pós-condição: Cria a disciplina ministrada para fazer a inserção
DisciplinaMinstrada* criar_DisciplinaMinstrada(int cod_disc, int ano_letivo, int cod_prof);

// Abre o arquivo o arquivo binário ou cria o arquivo se ele não existe
// Entrada: Nome do arquivo binário
// Retorno: Arquivo binário
// Pré-condição: O nome deve ser próprio para um arquivo binário
// Pós-condição: O arquivo binário é criado ou lido
FILE* open_ArqDiscM(char* str);

// Adiciona um nova disciplina ministrada em ordem de codigo da disciplina
// Entrada: Arquivo da disciplina ministrada e a struct disciplina ministrada
// Retorno: Nenhum
// Pré-condição: O arquivo binário deve ser próprio para manipular a disciplina ministrada
// Pós-condição: O contato com as informações fornecidas será adicionado na disciplina ministrada
void adicionar_DisciplinaMinstrada(FILE* arq, DisciplinaMinstrada *discM);

// Remove uma disciplina ministrada pelo codigo da disciplina e o ano letivo
// Entrada: Arquivo da disciplina ministrada, o codigo da disciplina e o ano letivo
// Retorno: Nenhum
// Pré-condição: O arquivo binário existir
// Pós-condição: Uma disciplina ministrada é removida
void remover_DisciplinaMinstrada(FILE *arq, int cod_disc, int ano_letivo);

// Cadastra uma disciplina ministrada com os dados do teclado 
// Entrada: A struct dos arquivos
// Retorno: Nenhum
// Pré-condição: A estrutura do arquvo tem existir
// Pós-condição: Adicionar a disciplina no arquivo binário
void cadastrar_disciplinaMinistrada(arquivos* arq);

// Imprime as disciplinas ministrada por ordem de codigo
// Entrada: Arquivo dos disciplina
// Retorno: Nenhum
// Pré-condição: O arquivo binário existir
// Pós-condição: As disciplinas seram impresso na tela
void imprimir_DisciplinaMinstrada(FILE* arq);

#endif