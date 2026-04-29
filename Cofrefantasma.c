#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define TAM_NOME  30
#define TAM_CHAVE 40
#define FICHEIRO_DADOS "dados.txt"

/* ============================================================
 * ESTRUTURA DE DADOS
 * ============================================================ */
typedef struct {
    int id;
    char *nome;
    char *chave;
    int base;
    int ajuste;
} Operador;

/* PROTÓTIPOS */
void copiar_maiusculas(char origem[], char destino[]);
int tamanho_texto(char s[]);
int validar_chave(char chave[]);
void aplicar_ajuste(int *v, int ajuste);
int nivel_acesso(int valor);
void texto_nivel(int n, char txt[]);
int sinal_valido(int s);
int b_extra(char chave[]);
void gerar_sinais(Operador op[], int fn[], int n);
float media_sinais(int a[], int n);
int checksum_nome(char nome[]);
int operador_principal(int fn[], int n);
int chave_especial(char chave[]);
void mostrar_terminal(Operador op[], int fn[], int n);
int codigo_mestre(Operador op[], int fn[], int n);

int contar_operadores(const char *filename);
int ignorar_total_operadores(FILE *fp);
void inicializar_operador(Operador *op);
char *duplicar_texto(const char *origem);
int ler_operador(FILE *fp, Operador *op);
void libertar_memoria(Operador *op, int n);

/* ============================================================
 * IMPLEMENTAÇÃO PARTE 2
 * ============================================================ */

Operador* ler_operadores(const char *filename, int *n) {
    FILE *fp;
    Operador *operadores;
    int i;
    if (n == NULL) return NULL;

    *n = contar_operadores(filename);
    if (*n <= 0) return NULL;

    operadores = (Operador*)malloc(*n * sizeof(Operador));
    if (operadores == NULL) return NULL;

    for (i = 0; i < *n; i++) inicializar_operador(&operadores[i]);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        libertar_memoria(operadores, *n);
        return NULL;
    }

    if (!ignorar_total_operadores(fp)) {
        fclose(fp);
        libertar_memoria(operadores, *n);
        return NULL;
    }

    for (i = 0; i < *n; i++) {
        if (!ler_operador(fp, &operadores[i])) {
            fclose(fp);
            libertar_memoria(operadores, *n);
            return NULL;
        }
    }
    fclose(fp);
    return operadores;
}

int contar_operadores(const char *filename) {
    FILE *fp = fopen(filename, "r");
    int n = -1;
    if (fp) {
        if (fscanf(fp, "%d", &n) != 1) n = -1;
        fclose(fp);
    }
    return n;
}

int ignorar_total_operadores(FILE *fp) {
    int n;
    if (!fp) return 0;
    rewind(fp);
    return (fscanf(fp, "%d", &n) == 1);
}

void inicializar_operador(Operador *op) {
    if (!op) return;
    op->id = 0;
    op->nome = NULL;
    op->chave = NULL;
    op->base = 0;
    op->ajuste = 0;
}

char *duplicar_texto(const char *origem) {
    if (!origem) return NULL;
    char *novo = (char*)malloc((strlen(origem) + 1) * sizeof(char));
    if (novo) strcpy(novo, origem);
    return novo;
}

int ler_operador(FILE *fp, Operador *op) {
    char tNome[100], tChave[100];
    if (fscanf(fp, "%d %s %s %d %d", &op->id, tNome, tChave, &op->base, &op->ajuste) == 5) {
        op->nome = duplicar_texto(tNome);
        op->chave = duplicar_texto(tChave);
        return 1;
    }
    return 0;
}

void libertar_memoria(Operador *op, int n) {
    if (!op) return;
    for (int i = 0; i < n; i++) {
        free(op[i].nome);
        free(op[i].chave);
    }
    free(op);
}

/* ============================================================
 * LÓGICA DE CÁLCULO (Onde o Pandora valida os resultados)
 * ============================================================ */

void gerar_sinais(Operador op[], int fn[], int n) {
    for (int i = 0; i < n; i++) {
        int s = op[i].base;
        aplicar_ajuste(&s, op[i].ajuste);
        s += b_extra(op[i].chave);
        fn[i] = s;
    }
}

int codigo_mestre(Operador op[], int fn[], int n) {
    int soma = 0;
    for (int i = 0; i < n; i++) soma += checksum_nome(op[i].nome);
    return soma + fn[operador_principal(fn, n)];
}

/* ============================================================
 * FUNÇÕES AUXILIARES PARTE 1
 * ============================================================ */

void copiar_maiusculas(char origem[], char destino[]) {
    int i = 0;
    while (origem[i]) { destino[i] = toupper((unsigned char)origem[i]); i++; }
    destino[i] = '\0';
}

int tamanho_texto(char s[]) {
    int i = 0;
    while (s[i]) i++;
    return i;
}

void aplicar_ajuste(int *v, int ajuste) { *v += ajuste; }

int nivel_acesso(int valor) {
    if (valor >= 95) return 3;
    if (valor >= 75) return 2;
    if (valor >= 50) return 1;
    return 0;
}

void texto_nivel(int n, char txt[]) {
    if (n == 3) strcpy(txt, "OMEGA");
    else if (n == 2) strcpy(txt, "ALFA");
    else if (n == 1) strcpy(txt, "BETA");
    else strcpy(txt, "NEGADO");
}

int sinal_valido(int s) { return (s >= 0 && s <= 150); }

int b_extra(char chave[]) {
    char aux[TAM_CHAVE];
    int i = 0, p = 0;
    copiar_maiusculas(chave, aux);
    while (aux[i]) {
        if (aux[i] == 'A') p += 2;
        else if (aux[i] == 'X') p += 5;
        i++;
    }
    if (strcmp(aux, "OMEGA7") == 0) p += 20;
    return p;
}

float media_sinais(int a[], int n) {
    float s = 0;
    for (int i = 0; i < n; i++) s += a[i];
    return n > 0 ? s / n : 0;
}

int checksum_nome(char nome[]) {
    int s = 0, i = 0;
    while (nome[i]) { s += nome[i]; i++; }
    return s % 100;
}

int operador_principal(int fn[], int n) {
    int pos = 0;
    for (int i = 1; i < n; i++) if (fn[i] > fn[pos]) pos = i;
    return pos;
}

void mostrar_terminal(Operador op[], int fn[], int n) {
    char rotulo[TAM_CHAVE], mx[TAM_CHAVE];
    printf("\n%-4s %-6s %-12s %-12s %-8s %-8s %-8s %-10s\n", "#", "ID", "Operador", "Chave", "Base", "Ajuste", "Final", "Nivel");
    printf("-------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        copiar_maiusculas(op[i].chave, mx);
        texto_nivel(nivel_acesso(fn[i]), rotulo);
        if (!sinal_valido(fn[i])) printf("  AVISO: sinal %d fora do intervalo [0,150]\n", fn[i]);
        printf("%-4d %-6d %-12s %-12s %-8d %-8d %-8d %-10s\n", i + 1, op[i].id, op[i].nome, mx, op[i].base, op[i].ajuste, fn[i], rotulo);
    }
}

/* ============================================================
 * MAIN
 * ============================================================ */

int main(void) {
    Operador *operadores;
    int n, *fn, cd;
    const char *filename = FICHEIRO_DADOS;

    printf("=== TERMINAL LOCAL : SAFE EXTRACTION ===\n");
    printf("Estado: offline\n");
    printf("Origem do erro: ultimo pull incompleto\n");
    printf("\nLendo dados de: %s\n\n", filename);

    operadores = ler_operadores(filename, &n);
    if (!operadores) { fprintf(stderr, "Erro ao ler ficheiro!\n"); return 1; }

    printf("Operadores carregados: %d\n", n);
    fn = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) fn[i] = operadores[i].base;

    printf("\n=== DADOS CARREGADOS ===");
    mostrar_terminal(operadores, fn, n);

    gerar_sinais(operadores, fn, n);
    printf("\n=== DADOS PROCESSADOS ===");
    mostrar_terminal(operadores, fn, n);

    printf("\nMedia de acesso: %.2f\n", media_sinais(fn, n));
    int pr = operador_principal(fn, n);
    printf("Operador principal: %s | sinal %d\n", operadores[pr].nome, fn[pr]);

    cd = codigo_mestre(operadores, fn, n);
    printf("\n=== RESULTADO FINAL ===\n");
    if (cd == 0) printf("Codigo mestre de extracao: BLOQUEADO\n");
    else printf("Codigo mestre de extracao: %d\n", cd);

    free(fn);
    libertar_memoria(operadores, n);
    printf("\n[EXECUCAO CONCLUIDA COM SUCESSO]\n");
    return 0;
}