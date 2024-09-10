#include "disciplina.h"
#include "arquivo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Disciplina* read_Disciplina(FILE* arq, int pos){
    Disciplina* cont = (Disciplina*) malloc(sizeof(Disciplina));
    fseek(arq, sizeof(cabecario)+sizeof(Disciplina)*pos, SEEK_SET);
    fread(cont, sizeof(Disciplina), 1, arq);
    return cont;
}

void write_Disciplina(FILE* arq, Disciplina* cont, int pos){
    fseek(arq, sizeof(cabecario)+sizeof(Disciplina)*pos, SEEK_SET);
    fwrite(cont, sizeof(Disciplina), 1, arq);
}

int buscar_pos_dis_disc(FILE* arq, cabecario* cab){ 
    int pos;               
    if(cab->pos_livre!=-1){              
        pos = cab->pos_livre;                      
        Disciplina* aux = read_Disciplina(arq, pos);
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

Disciplina* criar_Disciplina(int codDisciplina, char* noome_disc, int codCurso, int serie){
    Disciplina* aux = (Disciplina*) malloc(sizeof(Disciplina));
    aux->cod_disc = codDisciplina;
    strcpy(aux->nome_disc, noome_disc); 
    aux->cod_curso = codCurso;
    aux->serie = serie;
    aux->pos_prox = -1;
    return aux;
}

FILE* open_arq_disc(char* str){
    FILE* arq = fopen(str, "r+b");
    if(arq==NULL){
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

void adicionar_Disciplina(FILE* arq, Disciplina *Disc){
    arq = open_arq_disc("Disciplina.bin");
    Disciplina* disciplina = criar_Disciplina(Disc->cod_disc, Disc->nome_disc, Disc->cod_curso, Disc->serie), *aux, *ant;
    cabecario* cab = read_cab(arq);
    int pos_ant, pos_atual, pos_prox;

    pos_atual = buscar_pos_dis_disc(arq, cab);

    if(cab->pos_cabeca == -1)           
        cab->pos_cabeca = pos_atual;

    else{                         
        pos_ant = -1;
        pos_prox = cab->pos_cabeca;

        while(pos_prox!=-1){
            aux = read_Disciplina(arq, pos_prox);
            if(disciplina->cod_disc < aux->cod_disc){
                free(aux);
                aux = NULL;
                break;
            } 
            pos_ant = pos_prox;
            pos_prox = aux->pos_prox;
            free(aux);
            aux = NULL;
        } 
    
        disciplina->pos_prox = pos_prox;

        if(pos_ant!=-1){               
            ant = read_Disciplina(arq, pos_ant);
            ant->pos_prox = pos_atual;  
            write_Disciplina(arq, ant, pos_ant);
            free(ant);
        }
        else                            
            cab->pos_cabeca = pos_atual;
    }

    write_Disciplina(arq, disciplina, pos_atual);
    free(disciplina);

    write_cab(arq, cab);
    free(cab);
    fclose(arq);
}

arquivos* cadastrar_Disiciplina(arquivos* arq){
    Disciplina* disc = (Disciplina*) malloc (sizeof(Disciplina));
    printf("=========CADASTRO DE DISCIPLINAS=========\n");
    printf("Digite o codigo da disciplina: ");   //D;1;Algoritmos e Estrutura de Dados;1;2
    scanf("%d%*c", &disc->cod_disc); 

    printf("Digite o nome da disciplina: ");
    scanf("%[^\n]%*c", disc->nome_disc); 


    printf("Digite o codigo do curso que a disciplina pertence: ");
    scanf("%d%*c", &disc->cod_curso); 

    printf("Digite a serie da disciplina: ");
    scanf("%d%*c", &disc->serie); 

    system("cls");
    
    adicionar_Disciplina(arq->file_disc, disc);
    
    free(disc);
    return arq;
}

void imprimir_Disciplinas(FILE* arq){
    arq = open_arq_disc("Disciplina.bin");
    cabecario* cab = read_cab(arq);
    int pos_prox = cab->pos_cabeca;
    Disciplina* aux = (Disciplina*) malloc(sizeof(Disciplina));

    while(pos_prox!=-1){
        aux = read_Disciplina(arq, pos_prox);
        printf("Codigo da Disciplina: %d\nNome do Disciplina: %s\n",aux->cod_disc, aux->nome_disc);
        printf("Codigo do Curso: %d\nSerie: %d\n", aux->cod_curso, aux->serie);
        printf ("\n");
        pos_prox = aux->pos_prox;
        free(aux);
        aux = NULL;
    }
    fclose(arq);
    free(cab);
}
