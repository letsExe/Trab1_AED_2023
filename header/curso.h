#ifndef CURSO_H
#define CURSO_H

#define MAX 50

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arquivo.h"

typedef struct{
    int cod_curso;
    char nome_curso[MAX];
    char area_curso[MAX];
    int pos_prox;   // Posição (dentro do arquivo binário) do próximo contato
}Curso;


// Lê o curso do arquivo binário
// Entrada: Arquivo binário e a posição no arquivo
// Retorno: Retorna o curso lido
// Pré-condição: O aruivo binário tem que ser diferente de nulo
// Pós-condição: O curso é lido
Curso* read_Curso(FILE *arq, int pos);

// Escreve o curso no arquivo binário
// Entrada: Arquivo binário, o curso e a posição no arquivo
// Retorno: Nenhum
// Pré-condição: O arquvo e o curso serem diferente de nulo
// Pós-condição: O curso é escrito no arquivo 
void write_Curso(FILE* arq, Curso* cont, int pos);

// Busca a posição disponível dentro do arquivo binário
// Entrada: Arquivo binário e o cabeçalho
// Retorno: Retorna a próxima posição disponível para escrever um novo Curso
// Pré-condição: O arquvo existir
// Pós-condição: A posição é retornada para fazer a inserção
int buscar_pos_disp(FILE* arq, cabecario* cab);

// Cria um curso na estrutura de curso
// Entrada: O codigo do curso, o nome do curso e a aréa do curso
// Retorno: Retorna o curso
// Pré-condição: Nenhuma
// Pós-condição:    Cria o curso para fazer a inserção
Curso* criar_Curso(int codCurso, char* nomeCurso, char* area_curso);

// Abre o arquivo o arquivo binário ou cria o arquivo se ele não existe
// Entrada: Nome do arquivo binário
// Retorno: Arquivo binário
// Pré-condição: O nome deve ser próprio para um arquivo binário
// Pós-condição: O arquivo binário é criado ou lido
FILE* open_arq(char* str);

// Adiciona um novo curso em ordem de codigo do curso
// Entrada: Arquivo do curso e a struct curso
// Retorno: Nenhum
// Pré-condição: O arquivo binário deve ser próprio para manipular o curso
// Pós-condição: O contato com as informações fornecidas será adicionado no curso
void adicionar_Curso(FILE* arq, Curso *curso);

// Cadastra um curso com os dados do teclado 
// Entrada: A struct dos arquivos
// Retorno: Nenhum
// Pré-condição: A estrutura do arquvo tem existir
// Pós-condição: Adicionar o curso no arquivo binário
void cadastrar_curso(arquivos* arq);

// Imprime os cursos existentes
// Entrada: Arquivo dos curso
// Retorno: Nenhum
// Pré-condição: O arquivo binário existir
// Pós-condição: Os cursos seram impresso na tela
void imprimir_Cursos(FILE* arq);

#endif
