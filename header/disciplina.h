#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include "arquivo.h"

#define MAX 50

typedef struct{
    int cod_disc;
    char nome_disc[MAX];
    int cod_curso;
    int serie;
    int pos_prox;   // Posição (dentro do arquivo binário) do próximo contato
}Disciplina;

// Lê a disciplina do arquivo binário
// Entrada: Arquivo binário e a posição no arquivo
// Retorno: Retorna a disciplina lido
// Pré-condição: O aruivo binário tem que ser diferente de nulo
// Pós-condição: a disciplina é lido
Disciplina* read_Disciplina(FILE* arq, int pos);

// Escreve a disciplina no arquivo binário
// Entrada: Arquivo binário, a disciplina e a posição no arquivo
// Retorno: Nenhum
// Pré-condição: O arquvo e a disciplina serem diferente de nulo
// Pós-condição: a disciplina é escrito no arquivo 
void write_Disciplina(FILE* arq, Disciplina* cont, int pos);

// Busca a posição disponível dentro do arquivo binário
// Entrada: Arquivo binário e o cabeçalho
// Retorno: Retorna a próxima posição disponível para escrever um nova disciplina
// Pré-condição: O arquvo existir
// Pós-condição: A posição é retornada para fazer a inserção
int buscar_pos_dis_disc(FILE* arq, cabecario* cab);

// Cria uma disciplina na estrutura das disciplina
// Entrada: O codigo da disciplina, o nome da disciplina, o codigo da disciplina e a serie
// Retorno: Retorna a disciplina
// Pré-condição: Nenhuma
// Pós-condição: Cria a disciplina para fazer a inserção
Disciplina* criar_Disciplina(int codDisciplina, char* noome_disc, int codCurso, int serie);

// Abre o arquivo o arquivo binário ou cria o arquivo se ele não existe
// Entrada: Nome do arquivo binário
// Retorno: Arquivo binário
// Pré-condição: O nome deve ser próprio para um arquivo binário
// Pós-condição: O arquivo binário é criado ou lido
FILE* open_arq_disc(char* str);

// Adiciona um nova disciplina em ordem de codigo da disciplina
// Entrada: Arquivo da disciplina e a struct disciplina
// Retorno: Nenhum
// Pré-condição: O arquivo binário deve ser próprio para manipular a disciplina
// Pós-condição: O contato com as informações fornecidas será adicionado na disciplina
void adicionar_Disciplina(FILE* arq, Disciplina *Disc);

// Cadastra uma disciplina com os dados do teclado 
// Entrada: A struct dos arquivos
// Retorno: Nenhum
// Pré-condição: A estrutura do arquvo tem existir
// Pós-condição: Adicionar a disciplina no arquivo binário
arquivos* cadastrar_Disiciplina(arquivos* arq);

// Imprime as disciplinas existentes
// Entrada: Arquivo dos disciplina
// Retorno: Nenhum
// Pré-condição: O arquivo binário existir
// Pós-condição: As disciplinas seram impresso na tela
void imprimir_Disciplinas(FILE* arq);

#endif