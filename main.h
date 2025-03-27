#ifndef MAIN_H
#define MAIN_H

#define MAX_NOME 50
#define MAX_EVENTOS 10
#define MAX_CIDADES 7

typedef struct {
    char nome[MAX_NOME];
    float avaliacao;
} Evento;

typedef struct NoCidade {
    char nome[MAX_NOME];
    Evento eventos[MAX_EVENTOS];
    int numEventos;
    float avaliacaoMedia;
    struct NoCidade* pai;
    struct NoCidade* esquerda;
    struct NoCidade* direita;
} NoCidade;

NoCidade* criarNoCidade(const char* nome);
void gerarEventosAuto(NoCidade* cidade);
void gerarNomeAleatorioCidade(char* nome);
void inserirCidade(NoCidade** raiz, NoCidade* novaCidade);
void percorrerEmOrdem(NoCidade* raiz);
void percorrerPreOrdem(NoCidade* raiz);
void percorrerPoOrdem(NoCidade* raiz);
NoCidade* buscarCidade(NoCidade* raiz, const char* nome);
void encontrarRota(NoCidade* raiz, NoCidade* origem, NoCidade* destino);
void ordenarEventosCidade(NoCidade* raiz, const char* nome_cidade);
void buscarPorAvaliacao(NoCidade* raiz, float avaliacaoMinima);

#endif 