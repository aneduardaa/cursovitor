
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#define MAX_ALUNOS 100

typedef struct {
    char nome[50]; 
    char telefone[15]; 
    char curso[50]; 
    float nota1;
    float nota2;
    float media;
    char resultado[15];
} Aluno;

//calculando media do aluno/

float calcularMedia(float nota1, float nota2) {
    return (nota1 + nota2) / 2;
}
#include<stdio.h>
//situacao final do aluno diacordo com sua media/

void situacaoFinal(Aluno *aluno) {
    aluno->media = calcularMedia(aluno->nota1, aluno->nota2);
    if (aluno->media >= 7) {
        strcpy(aluno->resultado, "Aprovado");
    } else {
        strcpy(aluno->resultado, "Reprovado");
    }
}

//abrindo e lendo os dados dos alunos/

void lerDados(Aluno alunos[], int *Alunos) {
    FILE *arquivo_csv;
    char linha[100];
    arquivo_csv = fopen("dadosEntrada.csv", "r");
    if (arquivo_csv == NULL) {
        printf("\nErro ao abrir o arquivo");
        return; 
    }

    *Alunos = 0;
    while (fgets(linha, sizeof(linha), arquivo_csv)) {
        fscanf(linha, "%s,%s,%s,%f,%f", alunos[*Alunos].nome, alunos[*Alunos].telefone, alunos[*Alunos].curso, &alunos[*Alunos].nota1, &alunos[*Alunos].nota2);
        (*Alunos)++;
    }
    fclose(arquivo_csv);
}

//gerando o arquivo do resultado final/

void resultadoFinal(Aluno alunos[], int Alunos) {
    FILE *arquivo_csv;
    int i;

    arquivo_csv = fopen("resultadoFinal.csv", "w");
    if (arquivo_csv == NULL) {
        printf("\nNao foi possivel criar o arquivo de saida");
        return; 
    }

    for (i = 0; i < Alunos; i++) {
        situacaoFinal(&alunos[i]);
        fprintf(arquivo_csv, "%s, %.2f, %s\n", alunos[i].nome, alunos[i].media, alunos[i].resultado);
    }
    fclose(arquivo_csv);
}

