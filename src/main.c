#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#include "curso.h"
#include "disciplina.h"
#include "professor.h"
#include "disciplinaministrada.h"
#include "menu.h"
#include "arquivo.h"



int main (){
    arquivos *arq = (arquivos*) malloc (sizeof(arquivos));
    arq->file_curso = NULL;
    arq->file_disc = NULL;
    arq->file_prof = NULL;
    arq->file_disc_minis = NULL;

    int op, op1, cod, ano;
    char str[50], resp;

    setlocale(LC_ALL,"");

    welcome();
    desenvolvedores();

    do{        
        print_opcoes();
        scanf("%d%*c", &op);
        system("cls");

        switch (op){

       case 1:
            do{
                print_cadastro();
                scanf("%d", &op1);
                system("cls");
                if(op1 == 1){
                    do{
                        cadastrar_curso(arq);
                        fclose(arq->file_curso); // muda pra funcao
                        printf("Deseja cadastrar outro curso?(S/N) ");
                        scanf("%c", &resp);  
                        system("cls");
                    }while(resp == 's' || resp == 'S');
                }
                
                else if(op1 == 2){
                    do{
                        arq = cadastrar_Disiciplina(arq);
                        fclose(arq->file_disc);
                        printf("Deseja cadastrar outra disciplina?(S/N) ");
                        scanf("%c", &resp); 
                        system("cls");
                    }while(resp == 's' || resp == 'S');
                }
                
                else if (op1 == 3){
                    do{
                        cadastrar_Professor(arq);
                        fclose(arq->file_prof);
                        printf("Deseja cadastrar outro/a professor(a)?(S/N) ");
                        scanf("%c", &resp);
                        system("cls"); 
                
                    }while(resp == 's' || resp == 'S');
                }
                else if(op1 == 4){
                    do{
                        cadastrar_disciplinaMinistrada(arq);
                        fclose(arq->file_disc_minis);
                        printf("Deseja cadastrar novamente?(S/N) ");
                        scanf("%c", &resp);
                        system("cls"); 
                    }while(resp == 's' || resp == 'S');
                }
            }while(op1 != 0);
            system("cls");
            break;

        case 2: 
            do{
                printar();
                scanf("%d", &op1);
                printf("\n\n");
                system("cls");
                if(op1 == 1){
                    imprimir_Cursos(arq->file_curso);
                    printf("\n\n");
                }   
                
                else if(op1 == 2){
                    imprimir_Disciplinas(arq->file_disc);
                    printf("\n\n");
                }
                
                else if (op1 == 3){
                    imprimir_Professor(arq->file_prof);
                    printf("\n\n");
                }
                else if(op1 == 4){
                    imprimir_DisciplinaMinstrada(arq->file_disc_minis);
                    printf("\n\n");
                }
            } while(op1 != 0);
            system("cls");
            break;

        case 3:
            printf("Digite o Codigo da disciplina que deseja remover: ");
            scanf("%d", &cod);
            printf("Digite o ano letivo: ");
            scanf("%d", &ano);
            remover_DisciplinaMinstrada(arq->file_disc_minis, cod, ano);
            printf("Removido com sucesso\n");
            break;

        case 4:
            printf("Digite o nome do arquivo: ");
            scanf("%[^\n]%*c", str);
            arq = ler_arquivo(str, arq);
            break;

        default:
            break;
        }
    }while(op != 0);

    return 0;
}