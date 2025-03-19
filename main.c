#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.c"

int main() {
    int Soma = 0;
    int NumTeste = 0;
    FILE *Resposta = fopen("Resultado.txt", "w");

    Estrada *T = getEstrada("Teste01.txt");
    if (T) {
        double D = calcularMenorVizinhanca("Teste01.txt");
        char *C = cidadeMenorVizinhanca("Teste01.txt");

        if (T->T == 10) Soma++;
        NumTeste++;
        if (T->N == 2) Soma++;
        NumTeste++;
        if (D == 3.5) Soma++;
        NumTeste++;
        if (strcmp(C, "Birnin Zana") == 0) Soma++;
        NumTeste++;

        fprintf(Resposta, "\n\nTeste com o arquivo Teste01.txt:\n");
        fprintf(Resposta, "ATENÇÃO: Você acertou %d de %d itens. Logo, em 2.00 pontos, sua nota foi %.2f.\n",
                Soma, NumTeste, 2.0 * (float)Soma / (float)NumTeste);
        
        free(C);
        free(T->C);
        free(T);
    } else {
        fprintf(Resposta, "Erro ao inicializar a estrada com o arquivo: Teste01.txt\n");
    }

    fclose(Resposta);
    return 0;
}
