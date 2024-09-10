#include "professor.h"
#include "arquivo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Professor* read_Professor(FILE* arq, int pos){
    Professor* prof = (Professor*) malloc(sizeof(Professor));
    fseek(arq, sizeof(cabecario)+sizeof(Professor)*pos, SEEK_SET);
    fread(prof, sizeof(Professor), 1, arq);
    return prof;
}

void write_Professor(FILE* arq, Professor* prof, int pos){
    fseek(arq, sizeof(cabecario)+sizeof(Professor)*pos, SEEK_SET);
    fwrite(prof, sizeof(Professor), 1, arq);
}

int buscar_pos_disProf(FILE* arq, cabecario* cab){ 
    int pos;                                   
    if(cab->pos_livre != -1){                     
        pos = cab->pos_livre;                      
        Professor* aux = read_Professor(arq, pos);
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

Professor* criar_Professor(int codProfessor, char* nomeProfessor){
    Professor* prof = (Professor*) malloc(sizeof(Professor));
    prof->cod_prof = codProfessor;
    strcpy(prof->nome_prof, nomeProfessor); 
    prof->pos_prox = -1;
    return prof;
}

FILE* open_arqProf(char* str){
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

void adicionar_Professor(FILE* arq, Professor *prof){
    arq = open_arqProf("Professor.bin");
    Professor* professor = criar_Professor(prof->cod_prof, prof->nome_prof), *aux, *ant;
    cabecario* cab = read_cab(arq);
    int pos_ant, pos_atual, pos_prox;

    pos_atual = buscar_pos_disProf(arq, cab);

    if(cab->pos_cabeca == -1)             
        cab->pos_cabeca = pos_atual;

    else{                        
        pos_ant = -1;
        pos_prox = cab->pos_cabeca;

        while(pos_prox != -1){
            aux = read_Professor(arq, pos_prox);
            if(professor->cod_prof < aux->cod_prof){
                free(aux);
                aux = NULL;
                break;
            } 
            pos_ant = pos_prox;
            pos_prox = aux->pos_prox;
            free(aux);
            aux = NULL;
        } 

        professor->pos_prox = pos_prox;

        if(pos_ant != -1){         
            ant = read_Professor(arq, pos_ant);
            ant->pos_prox = pos_atual; 
            write_Professor(arq, ant, pos_ant);
            free(ant);
        }
        else                            
            cab->pos_cabeca = pos_atual;
    }

    write_Professor(arq, professor, pos_atual);
    free(professor);

    write_cab(arq, cab);
    free(cab);
    fclose(arq);
}

void cadastrar_Professor(arquivos* arq){
    Professor* prof = (Professor*) malloc (sizeof(Professor));
    printf("=========CADASTRO DE Professor=========\n");
    printf("Digite o codigo da Professor: ");//P;7;Einstein
    scanf("%d%*c", &prof->cod_prof); 

    printf("Digite o nome da Professor: ");
    scanf("%[^\n]%*c", prof->nome_prof); 

    system("cls");
    
    adicionar_Professor(arq->file_prof, prof);
    
    free(prof);
}

void imprimir_Professor(FILE* arq){
    arq = open_arqProf("Professor.bin");
    cabecario* cab = read_cab(arq);
    int pos_prox = cab->pos_cabeca;

    Professor* aux = (Professor*) malloc(sizeof(Professor));

    while(pos_prox != -1){
        aux = read_Professor(arq, pos_prox);
        printf("Codigo do Professor: %d\nNome do Professor: %s\n\n", aux->cod_prof, aux->nome_prof);
        pos_prox = aux->pos_prox;

        free(aux);
        aux = NULL;
    }
    fclose(arq);
    free(cab);
}