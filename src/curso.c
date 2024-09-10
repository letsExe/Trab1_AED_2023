#include "curso.h"
#include "arquivo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Curso* read_Curso(FILE* arq, int pos){
    Curso* curso = (Curso*) malloc(sizeof(Curso));
    fseek(arq, sizeof(cabecario) + sizeof(Curso)*pos, SEEK_SET);
    fread(curso, sizeof(Curso), 1, arq);
    return curso;
}

void write_Curso(FILE* arq, Curso* curso, int pos){
    fseek(arq, sizeof(cabecario) + sizeof(Curso)*pos, SEEK_SET);
    fwrite(curso, sizeof(Curso), 1, arq);
}

int buscar_pos_disp(FILE* arq, cabecario* cab){ 
    int pos; // Retorna a próxima posição disponível para escrever um novo Curso (dando preferência à posição livre)
    if(cab->pos_livre!=-1){   // atualizando os nós necessários e o cabeçalho
        pos = cab->pos_livre; 
        Curso* aux = read_Curso(arq, pos);
        cab->pos_livre = aux->pos_prox;
        free(aux);
        aux = NULL;
    }
    else {
        pos = cab->pos_topo;
        cab->pos_topo++;
    }

    return pos;
}

Curso* criar_Curso(int codCurso, char* nomeCurso, char* area_curso){
    Curso* curso = (Curso*) malloc(sizeof(Curso));
    curso->cod_curso = codCurso;
    strcpy(curso->nome_curso, nomeCurso); 
    strcpy(curso->area_curso, area_curso);
    curso->pos_prox = -1;
    return curso;
}

// Realiza a incialização do cabeçalho do arquivo
// Entrada: Arquivo binário
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: arquivo binário incializado
FILE* open_arq(char* str){
    FILE* arq = fopen(str, "r+b");
    if(arq == NULL){
        arq = fopen(str, "w+b");
        cabecario* cab = (cabecario*) malloc(sizeof(cabecario));
        cab->pos_cabeca = -1;
        cab->pos_livre = -1;
        cab->pos_topo = 0;
        write_cab(arq, cab);
        free(cab);
    }
    return arq;
}

void adicionar_Curso(FILE* arq, Curso *curso){
    arq = open_arq("curso.bin");
    Curso* c = criar_Curso(curso->cod_curso, curso->nome_curso, curso->area_curso), *aux, *ant;
    cabecario* cab = read_cab(arq);
    int pos_ant, pos_atual, pos_prox;

    pos_atual = buscar_pos_disp(arq, cab);

    if(cab->pos_cabeca == -1) // se não há nenhum Curso na lista
        cab->pos_cabeca = pos_atual;

    else{// se há pelo menos um Curso na lista, será necessário verificar em que posição o novo Curso deverá ficar
        pos_ant = -1;
        pos_prox = cab->pos_cabeca;

        while(pos_prox!=-1){
            aux = read_Curso(arq, pos_prox);
            if(c->cod_curso < aux->cod_curso){
                free(aux);
                aux = NULL;
                break;
            } 
            pos_ant = pos_prox;
            pos_prox = aux->pos_prox;
            free(aux);
            aux = NULL;
        } 
        // Ao final do loop:
        //  1. pos_ant terá a posição do Curso que deve estar imediatamente antes do novo Curso a ser inserido
        //  2. pos_prox terá a posição do Curso que deve estar imediatamente após o novo Curso a ser inserido

        c->pos_prox = pos_prox;

        if(pos_ant != -1){// Se houver algum Curso antes (novo Curso não é o primeiro)
            ant = read_Curso(arq, pos_ant);
            ant->pos_prox = pos_atual;// A posição do próximo do Curso anterior será a posição onde o novo Curso será escrito
            write_Curso(arq, ant, pos_ant);
            free(ant);
        }
        else                            
            cab->pos_cabeca = pos_atual;// O novo Curso será o primeiro na lista, ou seja, a nova cabeça
    }

    write_Curso(arq, c, pos_atual);
    free(c);

    write_cab(arq, cab);
    free(cab);
    fclose(arq);
}

void cadastrar_curso(arquivos* arq){
    Curso* curso = (Curso*) malloc (sizeof(Curso));

    printf("=========CADASTRO DE CURSO=========\n");
    printf("Digite o codigo do curso: ");
    scanf("%d%*c", &curso->cod_curso); 

    printf("Digite o nome do curso: ");
    scanf("%[^\n]%*c", curso->nome_curso); 

    printf("Digite a area do curso (E - Exatas, H - Humanas, B - Biologicas): ");
    scanf("%s%*c", curso->area_curso);  

    system("cls");
    
    adicionar_Curso(arq->file_curso, curso);
    
    free(curso);
}

void imprimir_Cursos(FILE* arq){
    arq = open_arq("curso.bin");
    cabecario* cab = read_cab(arq);
    int pos_prox = cab->pos_cabeca;
    Curso* aux = (Curso*) malloc(sizeof(Curso));
    
    while(pos_prox != -1){
        aux = read_Curso(arq, pos_prox);
        printf("Codigo do Curso: %d\nNome do Curso: %s\nArea: %s\n\n", aux->cod_curso, aux->nome_curso, aux->area_curso);
        pos_prox = aux->pos_prox;
        free(aux);
        aux = NULL;
    }
    fclose(arq);
    free(cab);
}