#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_EVENTOS 20
#define MAX_NOME 30

// Estrutura para armazenar eventos
typedef struct Evento {
    char nome[50];
    float avaliacao;
} Evento;

// Estrutura para armazenar cidades na árvore binária
typedef struct Cidade {
    char nome[30];
    int nEventos;
    Evento* eventos;
    struct Cidade *esquerda, *direita;
} Cidade;

// Função para criar um novo nó da cidade
Cidade* criarCidade(char* nome) {
    Cidade* novaCidade = (Cidade*)malloc(sizeof(Cidade));
    strcpy(novaCidade->nome, nome);
    novaCidade->esquerda = novaCidade->direita = NULL;
    return novaCidade;
}

// Função para inserir uma cidade na árvore binária
Cidade* inserirCidade(Cidade* raiz, char* nome) {
    if (raiz == NULL)
        return criarCidade(nome);

    if (strcmp(nome, raiz->nome) < 0)
        raiz->esquerda = inserirCidade(raiz->esquerda, nome);
    else
        raiz->direita = inserirCidade(raiz->direita, nome);

    return raiz;
}

// Percurso in-order na árvore binária
void inOrder(Cidade* raiz) {
    if (raiz != NULL) {
        inOrder(raiz->esquerda);
        printf("%s -> ", raiz->nome);
        inOrder(raiz->direita);
    }
}

// Função para gerar eventos aleatórios para uma cidade
void gerarEventos(Evento eventos[], int* nEventos) {
    char* nomesEventos[] = {
             "Festival de Musica", "Feira de Artesanato",  "Exposicao de Arte", "Show ao Vivo",          "Jogo de Futebol",
             "Cavalgada",          "Aniversario da Cidade","Festival de Comida","Campeonato de Capoeira","Zoologico",
             "Visita ao Museu",    "Passeio no Parque",    "Desfile de Moda",   "Show no Circo",         "Centro Historico",
             "Parque Aquatico",    "Trihas",               "Cachoeira",         "Corrida de Kart",       "Feira Livre"
         };
    *nEventos = (rand() % 8) + 3;
    printf("Eventos para cidade = %d \n", *nEventos);
    for (int i = 0; i < *nEventos; i++) {
            printf("a");
        strcpy(eventos[i].nome, nomesEventos[rand()%20]);
        eventos[i].avaliacao = (rand() % 101) / 10.0; // Avaliação entre 0.0 e 10.0
    }
    printf("a");
}

// Função de ordenação Bubble Sort
void bubbleSort(Evento* eventos, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (eventos[j].avaliacao < eventos[j + 1].avaliacao) {
                Evento temp = eventos[j];
                eventos[j] = eventos[j + 1];
                eventos[j + 1] = temp;
            }
        }
    }
}

// Exibir eventos ordenados
void exibirEventos(Evento* eventos, int n) {
    printf("Eventos ordenados por avaliação:\n");
    for (int i = 0; i < n; i++) {
        printf("%s (%.2f)\n", eventos[i].nome, eventos[i].avaliacao);
    }
}

// Buscar uma cidade na árvore binária
Cidade* buscarCidade(Cidade* raiz, char* nome) {
    if (raiz == NULL || strcmp(raiz->nome, nome) == 0)
        return raiz;

    if (strcmp(nome, raiz->nome) < 0)
        return buscarCidade(raiz->esquerda, nome);
    else
        return buscarCidade(raiz->direita, nome);
}

// Função principal
int main() {
    srand(time(NULL));
    Cidade* raiz = NULL;
    int numCidades = 10;
    char nomeCidade[30];

    for(int i=0;i<numCidades;i++){
        snprintf(nomeCidade, 30, "Cidade %d", i);
        raiz = inserirCidade(raiz, nomeCidade);
    }

    // Inserindo cidades na árvore
    /*raiz = inserirCidade(raiz, "Cidade A");
    raiz = inserirCidade(raiz, "Cidade B");
    raiz = inserirCidade(raiz, "Cidade C");
    raiz = inserirCidade(raiz, "Cidade D");*/

    printf("Cidades geradas na árvore (Inorder):\n");
    inOrder(raiz);
    printf("\n\n");

    // Gerando eventos para uma cidade específica
    for(int i=0;i<numCidades;i++){
        snprintf(nomeCidade, 30, "Cidade %d", i);
        Cidade* cidadeSelecionada = buscarCidade(raiz, nomeCidade);
        printf("\n \nExibindo eventos para a %s \n", nomeCidade);
        if (cidadeSelecionada != NULL) {
            gerarEventos(cidadeSelecionada->eventos, &cidadeSelecionada->nEventos);
            bubbleSort(cidadeSelecionada->eventos, cidadeSelecionada->nEventos);
            exibirEventos(cidadeSelecionada->eventos, cidadeSelecionada->nEventos);
        }
    }


    return 0;
}
