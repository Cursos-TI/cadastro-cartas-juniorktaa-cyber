// ...existing code...
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_COD 5
#define MAX_NOME 100
#define NUM_CARTAS 2
#define BUF_SIZE 128

typedef struct {
    char estado;                 // A-H
    char codigo[MAX_COD];        // ex: A01
    char nomeCidade[MAX_NOME];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
} Carta;

static void trim_newline(char *s) {
    size_t l = strlen(s);
    if (l && s[l-1] == '\n') s[l-1] = '\0';
}

static void read_line(const char *prompt, char *out, size_t len) {
    char buf[BUF_SIZE];
    while (1) {
        printf("%s", prompt);
        if (!fgets(buf, sizeof(buf), stdin)) {
            out[0] = '\0';
            return;
        }
        trim_newline(buf);
        if (strlen(buf) < len) {
            strncpy(out, buf, len);
            out[len-1] = '\0';
            return;
        }
        printf("Entrada muito longa. Tente novamente.\n");
    }
}

static char read_estado(const char *prompt) {
    char buf[BUF_SIZE];
    while (1) {
        read_line(prompt, buf, sizeof(buf));
        if (strlen(buf) == 1) {
            char c = toupper((unsigned char)buf[0]);
            if (c >= 'A' && c <= 'H') return c;
        }
        printf("Estado inválido. Digite uma letra de A a H.\n");
    }
}

static int read_int(const char *prompt) {
    char buf[BUF_SIZE];
    int v;
    while (1) {
        read_line(prompt, buf, sizeof(buf));
        if (sscanf(buf, "%d", &v) == 1) return v;
        printf("Número inteiro inválido. Tente novamente.\n");
    }
}

static float read_float(const char *prompt) {
    char buf[BUF_SIZE];
    float f;
    while (1) {
        read_line(prompt, buf, sizeof(buf));
        if (sscanf(buf, "%f", &f) == 1) return f;
        printf("Número inválido. Tente novamente.\n");
    }
}

int main(void) {
    Carta cartas[NUM_CARTAS];

    for (int i = 0; i < NUM_CARTAS; ++i) {
        printf("=== Cadastro da Carta %d ===\n", i + 1);
        cartas[i].estado = read_estado("Digite o estado (A-H): ");
        read_line("Digite o código da carta (ex: A01): ", cartas[i].codigo, MAX_COD);
        read_line("Digite o nome da cidade: ", cartas[i].nomeCidade, MAX_NOME);
        cartas[i].populacao = read_int("Digite a população: ");
        cartas[i].area = read_float("Digite a área (em km²): ");
        cartas[i].pib = read_float("Digite o PIB (em bilhões de reais): ");
        cartas[i].pontosTuristicos = read_int("Digite o número de pontos turísticos: ");
        printf("\n");
    }

    for (int i = 0; i < NUM_CARTAS; ++i) {
        printf("=== Carta %d ===\n", i + 1);
        printf("Estado: %c\n", cartas[i].estado);
        printf("Código: %s\n", cartas[i].codigo);
        printf("Nome da Cidade: %s\n", cartas[i].nomeCidade);
        printf("População: %d habitantes\n", cartas[i].populacao);
        printf("Área: %.2f km²\n", cartas[i].area);
        printf("PIB: %.2f bilhões de reais\n", cartas[i].pib);
        printf("Número de Pontos Turísticos: %d\n\n", cartas[i].pontosTuristicos);
    }

    return 0;
}