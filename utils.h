// Arquivo: utils.h | Funcoes compartilhadas por todos os modulos
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 50                 // limite de registros por modulo
#define MAX_AUDICOES 200       // o historico de audicoes cresce mais rapido
#define USOS_PARA_DESGASTE 20  // a cada 20 usos o CD perde um nivel de conservacao

const char *NOMES_DIAS[7] = {"Dom", "Seg", "Ter", "Qua", "Qui", "Sex", "Sab"};
const char *NIVEIS_CONSERVACAO[4] = {"Novo", "Bom", "Regular", "Desgastado"};

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Descarta o que sobrou na linha digitada (ex.: o ENTER do scanf)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

// Le um inteiro com validacao (repete ate o usuario digitar um numero)
int lerInt(const char *msg) {
    int valor, r;
    printf("%s", msg);
    while ((r = scanf("%d", &valor)) != 1) {
        if (r == EOF) exit(0);
        limparBuffer();
        printf("Valor invalido! Digite um numero: ");
    }
    limparBuffer();
    return valor;
}

// Le texto com espacos. Troca ';' por ',' para nao quebrar o formato CSV
void lerTexto(const char *msg, char *dest, int tam) {
    char buf[100];
    int i;
    printf("%s", msg);
    if (scanf(" %99[^\n]", buf) != 1) exit(0);
    limparBuffer();
    for (i = 0; buf[i] != '\0'; i++) {
        if (buf[i] == ';') buf[i] = ',';
    }
    strncpy(dest, buf, tam - 1);
    dest[tam - 1] = '\0';
}

int confirmar(const char *msg) {
    char c;
    printf("%s (s/n): ", msg);
    if (scanf(" %c", &c) != 1) exit(0);
    limparBuffer();
    return (c == 's' || c == 'S');
}

void paraMinusculo(const char *origem, char *destino) {
    int i;
    for (i = 0; origem[i] != '\0'; i++)
        destino[i] = (char)tolower((unsigned char)origem[i]);
    destino[i] = '\0';
}

// Busca textual SEM diferenciar maiusculas de minusculas (usa strstr)
int contemTexto(const char *texto, const char *termo) {
    char a[200], b[200];
    paraMinusculo(texto, a);
    paraMinusculo(termo, b);
    return strstr(a, b) != NULL;
}

void imprimirTempo(int segundos) {
    printf("%dh %02dmin %02ds", segundos / 3600, (segundos % 3600) / 60, segundos % 60);
}

#endif
