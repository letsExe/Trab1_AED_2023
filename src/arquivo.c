#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arquivo.h"
#include "curso.h"
#include "disciplina.h"
#include "professor.h"
#include "disciplinaministrada.h"


void write_cab(FILE* arq, cabecario* cab){
    fseek(arq, 0, SEEK_SET);
    fwrite(cab, sizeof(cabecario), 1, arq);
}

cabecario* read_cab(FILE* arq){
    cabecario* cab = (cabecario*) malloc(sizeof(cabecario));
    fseek(arq, 0, SEEK_SET);
    fread(cab, sizeof(cabecario), 1, arq);
    return cab;
}

arquivos* ler_arquivo(char *arquivo, arquivos *arq){
    char ch, nome[50], area[2];
    int cod, codCurso, serie, ano_letivo, cod_prof, i = 0;

    FILE *file = fopen(arquivo, "r");

    if(file == NULL){
        printf("Arquivo não encontrando\n");
        return arq;
    }
    else 
        printf("Arquivo encontrando.\n\n");

     while(fscanf(file,"%c%*c", &ch) != EOF){
        if(ch == 'C' || ch == 'c'){
            arq->file_curso = open_arq("curso.bin");  //C;1;Ciencia da Computacao;E
            fscanf(file, "%d%*c", &cod);  
            fscanf(file, "%[^;]%*c", nome); 
            fscanf(file, "%[^\n]%*c", area);

            Curso *c = criar_Curso(cod, nome, area);
            adicionar_Curso(arq->file_curso, c);
            fclose(arq->file_curso);
        }
        else
            if(ch == 'D' || ch == 'd'){
                arq->file_disc = open_arq_disc("Disciplina.bin");  //D;1;Algoritmos e Estrutura de Dados;1;2
                fscanf(file, "%d%*c", &cod); 
                fscanf(file, "%[^;]%*c", nome); 
                fscanf(file, "%d%*c", &codCurso);
                fscanf(file, "%d%*c", &serie); 

                Disciplina *d = criar_Disciplina(cod, nome, codCurso, serie);
                adicionar_Disciplina(arq->file_disc, d);
                fclose(arq->file_disc);
        }
        else 
            if(ch == 'P' || ch == 'p'){
                arq->file_prof = open_arqProf("Professor.bin");  //P;1;Joao da Silva
                fscanf(file, "%d%*c", &cod); 
                fscanf(file, "%[^\n]%*c", nome);
                
                Professor *p = criar_Professor(cod, nome);
                adicionar_Professor(arq->file_prof, p);
                fclose(arq->file_prof);
        }
        else
            if(ch == 'M' || ch == 'm'){
                arq->file_disc_minis = open_ArqDiscM("DisciplinaMinstrada.bin");  //M;1;2023;8
                fscanf(file, "%d%*c", &cod); 
                fscanf(file, "%d%*c", &ano_letivo); 
                fscanf(file, "%d%*c", &cod_prof); 

                DisciplinaMinstrada *dm = criar_DisciplinaMinstrada(cod, ano_letivo, cod_prof);
                adicionar_DisciplinaMinstrada(arq->file_disc_minis, dm);
                fclose(arq->file_disc_minis);
        }
        else 
            fscanf(file,"%*[^\n]%*c");
    }
    return arq;
}