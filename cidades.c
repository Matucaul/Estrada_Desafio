#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cidades.h"

Estrada *getEstrada(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    int T, N;
    if (fscanf(file, "%d", &T) != 1 || T < 3 || T > 1000000) {
        fclose(file);
        return NULL;
    }

    if (fscanf(file, "%d", &N) != 1 || N < 2 || N > 10000) {
        fclose(file);
        return NULL;
    }

    Cidade *cidades = malloc(N * sizeof(Cidade));
    if (!cidades) {
        fclose(file);
        return NULL;
    }

    // Lê as cidades
    for (int i = 0; i < N; i++) {
        if (fscanf(file, "%d %255[^\n]", &cidades[i].Posicao, cidades[i].Nome) != 2) {
            free(cidades);
            fclose(file);
            return NULL;
        }
    }

    fclose(file);

    Estrada *estrada = malloc(sizeof(Estrada));
    if (!estrada) {
        free(cidades);
        return NULL;
    }

    estrada->N = N;
    estrada->T = T;
    estrada->C = cidades;

    return estrada;
}

double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) {
        return -1;
    }

    double menorVizinhanca = (double)(estrada->T);
    double vizinhancas[estrada->N];

    for (int i = 0; i < estrada->N; i++) {
        int posAtual = estrada->C[i].Posicao;

        double distanciaEsquerda = (i > 0) ? (posAtual - estrada->C[i - 1].Posicao) / 2.0 : (posAtual - 0.0) / 2.0;
        
        double distanciaDireita = (i < estrada->N - 1) ? (estrada->C[i + 1].Posicao - posAtual) / 2.0 : (estrada->T - posAtual) / 2.0;

        vizinhancas[i] = fmin(distanciaEsquerda, distanciaDireita);
        if (vizinhancas[i] < menorVizinhanca) {
            menorVizinhanca = vizinhancas[i];
        }
    }

    free(estrada->C);
    free(estrada);

    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) {
        return NULL;
    }

    double menorVizinhanca = (double)(estrada->T);
    int indiceCidade = -1;

    for (int i = 0; i < estrada->N; i++) {
        int posAtual = estrada->C[i].Posicao;

        double distanciaEsquerda = (i > 0) ? (posAtual - estrada->C[i - 1].Posicao) / 2.0 : (posAtual - 0.0) / 2.0;
        double distanciaDireita = (i < estrada->N - 1) ? (estrada->C[i + 1].Posicao - posAtual) / 2.0 : (estrada->T - posAtual) / 2.0;

        double vizinhancaAtual = fmin(distanciaEsquerda, distanciaDireita);
        if (vizinhancaAtual < menorVizinhanca) {
            menorVizinhanca = vizinhancaAtual;
            indiceCidade = i;
        }
    }

    char *resultado = NULL;
    if (indiceCidade != -1) {
        resultado = malloc(strlen(estrada->C[indiceCidade].Nome) + 1);
        if (resultado) {
            strcpy(resultado, estrada->C[indiceCidade].Nome);
        }
    }

    free(estrada->C);
    free(estrada);

    return resultado;
}
