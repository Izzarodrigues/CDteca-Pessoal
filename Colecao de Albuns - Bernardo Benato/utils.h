// Arquivo: utils.h | Autor: Bernardo Rodrigues Benato
// Funcoes auxiliares da versao independente do modulo de albuns.
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>

#define MAX 50

// Le um numero inteiro, repetindo quando o usuario digita texto invalido.
int lerInt(const char mensagem[]) {
    int valor;
    int resultado;
    int c;
    do {
        printf("%s", mensagem);
        resultado = scanf("%d", &valor);
        while ((c = getchar()) != '\n' && c != EOF) {
            // Limpa o restante da linha.
        }
        if (resultado != 1) printf("Digite um numero inteiro valido.\n");
    } while (resultado != 1);
    return valor;
}

// Le um texto com espacos e retira a quebra de linha final.
void lerTexto(const char mensagem[], char destino[], int tamanho) {
    int c;
    do {
        printf("%s", mensagem);
        if (fgets(destino, tamanho, stdin) == NULL) {
            destino[0] = '\0';
            return;
        }
        if (strchr(destino, '\n') == NULL) {
            while ((c = getchar()) != '\n' && c != EOF) {
                // Descarta caracteres que nao cabem no vetor.
            }
        }
        destino[strcspn(destino, "\n")] = '\0';
        if (destino[0] == '\0') printf("O texto nao pode ficar vazio.\n");
    } while (destino[0] == '\0');
}

#endif
