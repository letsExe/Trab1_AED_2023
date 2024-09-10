#include "disciplinaministrada.h"
#include "arquivo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DisciplinaMinstrada* read_DisciplinaMinstrada(FILE* arq, int pos){
    DisciplinaMinstrada* cont = (DisciplinaMinstrada*) malloc(sizeof(DisciplinaMinstrada));
    fseek(arq, sizeof(cabecario)+sizeof(DisciplinaMinstrada)*pos, SEEK_SET);
    fread(cont, sizeof(DisciplinaMinstrada), 1, arq);
    return cont;
}

void write_DisciplinaMinstrada(FILE* arq, DisciplinaMinstrada* cont, int pos){
    fseek(arq, sizeof(cabecario)+sizeof(DisciplinaMinstrada)*pos, SEEK_SET);
    fwrite(cont, sizeof(DisciplinaMinstrada), 1, arq);
}

int buscar_pos_disDistribucao(FILE* arq, cabecario* cab){ 
    int pos;                                        
    if(cab->pos_livre != -1){                         
        pos = cab->pos_livre;                   
        DisciplinaMinstrada* aux = read_DisciplinaMinstrada(arq, pos);
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

DisciplinaMinstrada* criar_DisciplinaMinstrada(int cod_disc, int ano_letivo, int cod_prof){
    DisciplinaMinstrada* cont = (DisciplinaMinstrada*) malloc(sizeof(DisciplinaMinstrada));
    cont->cod_disc = cod_disc;
    cont->ano_letivo = ano_letivo;
    cont->cod_prof = cod_prof;
    cont->pos_prox = -1;
    return cont;
}

FILE* open_ArqDiscM(char* str){
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

void adicionar_DisciplinaMinstrada(FILE* arq, DisciplinaMinstrada *discM){
    arq = open_ArqDiscM("DisciplinaMinstrada.bin");
    DisciplinaMinstrada* cont = criar_DisciplinaMinstrada(discM->cod_disc, discM->ano_letivo, discM->cod_prof), *aux, *ant;
    cabecario* cab = read_cab(arq);
    int pos_ant, pos_atual, pos_prox;

    pos_atual = buscar_pos_disDistribucao(arq, cab);

    if(cab->pos_cabeca == -1)          
        cab->pos_cabeca = pos_atual;

    else{                       
        pos_ant = -1;
        pos_prox = cab->pos_cabeca;

        while(pos_prox != -1){
            aux = read_DisciplinaMinstrada(arq, pos_prox);
            if(cont->cod_disc < aux->cod_disc){
                free(aux);
                aux = NULL;
                break;
            } 
            pos_ant = pos_prox;
            pos_prox = aux->pos_prox;
            free(aux);
            aux = NULL;
        } 

        cont->pos_prox = pos_prox;

        if(pos_ant != -1){         
            ant = read_DisciplinaMinstrada(arq, pos_ant);
            ant->pos_prox = pos_atual; 
            write_DisciplinaMinstrada(arq, ant, pos_ant);
            free(ant);
        }
        else                            
            cab->pos_cabeca = pos_atual;
    }

    write_DisciplinaMinstrada(arq, cont, pos_atual);
    free(cont);

    write_cab(arq, cab);
    free(cab);

    fclose(arq);
} 

void remover_DisciplinaMinstrada(FILE* arq, int cod_disc, int ano_letivo){
    arq = open_ArqDiscM("DisciplinaMinstrada.bin");
    cabecario* cab = read_cab(arq);
    DisciplinaMinstrada* aux, *ant;
    int pos_ant, pos_atual, pos_prox;

    pos_ant = -1;
    pos_atual = cab->pos_cabeca;

    while(pos_atual != -1){
        aux = read_DisciplinaMinstrada(arq, pos_atual);
        if(aux == NULL || (aux->cod_disc == cod_disc && aux->ano_letivo == ano_letivo)){
            free(aux);
            aux = NULL;
            break;
        }
        pos_ant = pos_atual;
        pos_atual = aux->pos_prox;
        free(aux);
        aux = NULL;
    }

    if(pos_atual != -1){                 
        aux = read_DisciplinaMinstrada(arq, pos_atual);
        pos_prox = aux->pos_prox;
        if(pos_ant != -1){                
            ant = read_DisciplinaMinstrada(arq, pos_ant);
            ant->pos_prox = pos_prox;   
            write_DisciplinaMinstrada(arq, ant, pos_ant);
            free(ant);
        }
        else
            cab->pos_cabeca = pos_prox; 
        
        aux->pos_prox = cab->pos_livre; 
        cab->pos_livre = pos_atual;     
        write_DisciplinaMinstrada(arq, aux, pos_atual);
        free(aux);
    }
    
    write_cab(arq, cab);
    free(cab);
    fclose(arq);
}

void cadastrar_disciplinaMinistrada(arquivos* arq){
    DisciplinaMinstrada* dm = (DisciplinaMinstrada*) malloc (sizeof(DisciplinaMinstrada));
    printf("=========CADASTRO DE DISCIPLINA MINISTRADA=========\n");
    printf("Digite o codigo da Disciplia: ");
    scanf("%d%*c", &dm->cod_disc); 

    printf("Digite o Ano Letivo: ");
    scanf("%d%*c", &dm->ano_letivo); 

    printf("Digite o codigo do professor que ministra a disciplina: ");
    scanf("%d%*c", &dm->cod_prof);  

    system("cls");
    
    adicionar_DisciplinaMinstrada(arq->file_disc_minis, dm);
    
    free(dm);
}

void imprimir_DisciplinaMinstrada(FILE* arq){
    arq = open_ArqDiscM("DisciplinaMinstrada.bin");
    cabecario* cab = read_cab(arq);
    int pos_prox = cab->pos_cabeca;
    DisciplinaMinstrada* aux = (DisciplinaMinstrada*) malloc(sizeof(DisciplinaMinstrada));

    while(pos_prox != -1){ 
        aux = read_DisciplinaMinstrada(arq, pos_prox);
        printf("Codigo da Disciplina Minstrada: %d\nAno Letivo: %d\n", aux->cod_disc, aux->ano_letivo);
        printf("Codigo do Professor: %d\n\n", aux->cod_prof);
        pos_prox = aux->pos_prox;

        free(aux);
        aux = NULL;
    }
    fclose(arq);
    free(cab);
}