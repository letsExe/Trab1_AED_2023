#include<stdio.h>
#include<stdlib.h>

#include "menu.h"
 
void welcome(){
	
	printf(" __   __  __    _  ______   _______  ___________  _______  _______  ___      _______ \n");
	printf("|  | |  ||  |  | ||      | |       ||    ___    ||       ||   _   ||   |    |       |\n");
	printf("|  | |  ||   |_| ||  _    ||    ___||   |   |   ||_     _||  |_|  ||   |    |    ___|\n");
	printf("|  |_|  ||       || | |   ||   |___ |   |___|   |  |   |  |       ||   |    |   |___ \n");
	printf("|       ||  _    || |_|   ||    ___||     __   _|  |   |  |       ||   |___ |    ___|\n");
	printf("|       || | |   ||       ||   |___ |    |  |  |_  |   |  |   _   ||       ||   |___ \n");
	printf("|_______||_|  |__||______| |_______||____|  |____| |___|  |__| |__||_______||_______|\n");
	printf("\n\n");
}

void desenvolvedores(){
	printf("O trabalho desenvolvido por:\n");
	printf(" ->  Leticia Zanellatto de Oliveira\n");
}

void print_opcoes(){
    printf("========Menu de Opcoes======\n\n");
	printf("1 - Cadastrar               \n");
	printf("2 - Imprimir                \n");
	printf("3 - Remover Distribuicao    \n");
	printf("4 - Ler Arquivo em lote     \n");
	printf("0 - Sair                    \n\n");
	printf("Digite uma Opcao: ");

}

void print_cadastro(){
    printf("==============Menu de Opcoes=============\n\n");
	printf("1 - Cadastrar Curso                      \n");
	printf("2 - Cadastrar Disciplina                 \n");
	printf("3 - Cadastrar Professor                  \n");
    printf("4 - Cadastrar Disciplinas Ministradas    \n");
	printf("0 - Sair                                 \n\n");
	printf("Digite uma Opcao: ");
    
}
void printar(){
	printf("==============Menu de Opcoes=========\n\n");
	printf("1 - Imprimir Curso                   \n");
	printf("2 - Imprimir Disciplina              \n");
	printf("3 - Imprimir Professor               \n");
        printf("4 - Imprimir Disciplinas Ministradas \n");
	printf("0 - Sair                             \n\n");
	printf("Digite uma Opcao: ");
    
}
