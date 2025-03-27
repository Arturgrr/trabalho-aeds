#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "main.h"
#include "ordenacao.h"

#define MAX_NOME 50
#define MAX_EVENTOS 10
#define MAX_CIDADES 7 

const char* MENSAGENS[] = {
    "Dica: Eventos bem avaliados são sempre uma ótima escolha!",
    "Recomendação do Neymar: Esse evento é brabo, pai!",
    "Sugestão: Convide amigos para curtir esse evento incrível!",
    "Dica: Eventos com boa avaliação são garantia de diversão!",
    "Aviso: Esse evento promete ser sensacional!",
    "Nota: Experiências únicas acontecem em eventos especiais!",
    "Destaque: Momentos inesquecíveis te aguardam!",
    "Importante: Não perca essa oportunidade incrível!",
    "Divulgação: Show imperdível chegando!",
    "Dica: Os melhores eventos têm as melhores avaliações!"
};

const char* PREFIXOS[] = {
    "São", "Nova", "Minas", "Porto", "Coronel", "Vale", "Rio", "Casa",
    "Ponte", "João", "Praia", "Porto", "Monte", "Costa", "Minas"
};

const char* SUFIXOS[] = {
    "Verde", "Nova", "Alta", "Bela", "Grande", "Linda", "Portugal", "Sul",
    "Era", "Leste", "Oeste", "Fabriciano", "Monlevade", "Gerais", "Piracicaba"
};

const char* NOMES_EVENTOS[] = {
    "Festival do Japa",
    "Festa Junina",
    "Carnaval",
    "Calourada",
    "Campeonato de Kart",
    "Feira de Fruta",
    "Festa na Piscina",
    "Show do Zeca Pagodinho",
    "Curso de Gastronomia",
    "Baile preto e branco",
    "Festival de chopp"
};

NoCidade* criarNoCidade(const char* nome) {
    NoCidade* auxNovoNo = (NoCidade*)malloc(sizeof(NoCidade));
    if (auxNovoNo == NULL) {
        return NULL;
    }
    
    strcpy(auxNovoNo->nome, nome);
    auxNovoNo->numEventos = 0;
    auxNovoNo->avaliacaoMedia = 0.0;
    auxNovoNo->esquerda = NULL;
    auxNovoNo->direita = NULL;
    auxNovoNo->pai = NULL;
    
    return auxNovoNo;
}

void gerarEventosAuto(NoCidade* cidade) {
    int numEventos = rand() % 5 + 5;
    cidade->numEventos = numEventos;
    float totalAvaliacao = 0.0;
    
    for (int i = 0; i < numEventos; i++) {
        int indiceEvento = rand() % 11;
        strcpy(cidade->eventos[i].nome, NOMES_EVENTOS[indiceEvento]);
        
        // Chance do evento ser cancelado
        if (rand() % 100 < 20) {
            char temp[MAX_NOME];
            sprintf(temp, "C%s", cidade->eventos[i].nome);
            strcpy(cidade->eventos[i].nome, temp);
        }
        
        cidade->eventos[i].avaliacao = (float)rand() / RAND_MAX * 10.0;
        totalAvaliacao += cidade->eventos[i].avaliacao;
    }
    
    cidade->avaliacaoMedia = totalAvaliacao / numEventos;
}

void gerarNomeAleatorioCidade(char* nome) {
    int prefixoIndex = rand() % 15;
    int sufixoIndex = rand() % 15;
    sprintf(nome, "%s %s", PREFIXOS[prefixoIndex], SUFIXOS[sufixoIndex]);
}

void inserirCidade(NoCidade** raiz, NoCidade* novaCidade) {
    if (*raiz == NULL) {
        *raiz = novaCidade;
        return;
    }
    
    if (novaCidade->avaliacaoMedia < (*raiz)->avaliacaoMedia) {
        inserirCidade(&(*raiz)->esquerda, novaCidade);
    } else {
        inserirCidade(&(*raiz)->direita, novaCidade);
    }
    novaCidade->pai = *raiz;
}

void percorrerEmOrdem(NoCidade* raiz) {
    if (raiz != NULL) {
        percorrerEmOrdem(raiz->esquerda);
        printf("%s (Avaliação: %.2f)\n", raiz->nome, raiz->avaliacaoMedia);
        percorrerEmOrdem(raiz->direita);
    }
}

void percorrerPreOrdem(NoCidade* raiz) {
    if (raiz != NULL) {
        printf("%s (Avaliação: %.2f)\n", raiz->nome, raiz->avaliacaoMedia);
        percorrerPreOrdem(raiz->esquerda);
        percorrerPreOrdem(raiz->direita);
    }
}

void percorrerPoOrdem(NoCidade* raiz) {
    if (raiz != NULL) {
        percorrerPoOrdem(raiz->esquerda);
        percorrerPoOrdem(raiz->direita);
        printf("%s (Avaliação: %.2f)\n", raiz->nome, raiz->avaliacaoMedia);
    }
}

NoCidade* buscarCidade(NoCidade* raiz, const char* nome) {
    if (raiz == NULL) {
        return NULL;
    }
    
    if (strcmp(raiz->nome, nome) == 0) {
        return raiz;
    }
    
    NoCidade* resultadoEsquerda = buscarCidade(raiz->esquerda, nome);
    if (resultadoEsquerda != NULL) {
        return resultadoEsquerda;
    }
    
    return buscarCidade(raiz->direita, nome);
}

void encontrarRota(NoCidade* raiz, NoCidade* origem, NoCidade* destino) {
    if (raiz == NULL || origem == NULL || destino == NULL) {
        printf("Rota inválida!\n");
        return;
    }

    printf("Rota sugerida:\n");

    NoCidade* atual = origem;
    NoCidade* caminho[MAX_CIDADES];
    int numCaminho = 0;
    
    caminho[numCaminho++] = origem;
    
    while (atual != destino) {
        if (atual->avaliacaoMedia < destino->avaliacaoMedia) {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else if (atual->pai != NULL) {
                atual = atual->pai;
            } else {
                printf("Não foi possível encontrar uma rota válida!\n");
                return;
            }
        }
        
        else if (atual->avaliacaoMedia > destino->avaliacaoMedia) {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else if (atual->pai != NULL) {
                atual = atual->pai;
            } else {
                printf("Não foi possível encontrar uma rota válida!\n");
                return;
            }
        }
        
        else {
            if (atual->pai != NULL) {
                atual = atual->pai;
            } else {
                printf("Não foi possível encontrar uma rota válida!\n");
                return;
            }
        }
        
        caminho[numCaminho++] = atual;
    }

    printf("\nMelhor caminho em %d cidades:\n", numCaminho - 1);
    for (int i = 0; i < numCaminho; i++) {
        printf("%s", caminho[i]->nome);
        if (i < numCaminho - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void ordenarEventosCidade(NoCidade* raiz, const char* nome_cidade) {
    NoCidade* cidade = buscarCidade(raiz, nome_cidade);
    if (cidade == NULL) {
        printf("Cidade não encontrada!\n");
        return;
    }
    
    printf("\nEventos de %s ordenados por avaliação:\n", nome_cidade);
    printf("1. Bubble Sort\n");
    printf("2. Selection Sort\n");
    printf("3. Insertion Sort\n");
    printf("4. Shell Sort\n");
    printf("5. Quick Sort\n");
    printf("6. Merge Sort\n");
    printf("7. Heap Sort\n");
    printf("Escolha o método de ordenação (1-7): ");
    
    int escolha;
    scanf("%d", &escolha);
    getchar();
    
    Evento eventos_ordenados[MAX_EVENTOS];
    memcpy(eventos_ordenados, cidade->eventos, sizeof(Evento) * cidade->numEventos);
    
    switch (escolha) {
        case 1:
            bubbleSort(eventos_ordenados, cidade->numEventos);
            break;
        case 2:
            selectionSort(eventos_ordenados, cidade->numEventos);
            break;
        case 3:
            insertionSort(eventos_ordenados, cidade->numEventos);
            break;
        case 4:
            shellSort(eventos_ordenados, cidade->numEventos);
            break;
        case 5:
            quickSort(eventos_ordenados, cidade->numEventos);
            break;
        case 6:
            mergeSort(eventos_ordenados, cidade->numEventos);
            break;
        case 7:
            heapSort(eventos_ordenados, cidade->numEventos);
            break;
        default:
            printf("Opção inválida!\n");
            return;
    }
    
    printf("\nEventos ordenados por avaliação:\n");
    for (int i = 0; i < cidade->numEventos; i++) {
        printf("%d. %s (Avaliação: %.1f)\n", 
               i + 1, 
               eventos_ordenados[i].nome, 
               eventos_ordenados[i].avaliacao);
    }
}

void buscarPorAvaliacao(NoCidade* raiz, float avaliacaoMinima) {
    if (raiz == NULL) {
        return;
    }
    
    if (raiz->avaliacaoMedia >= avaliacaoMinima) {
        printf("\nCidade: %s\n", raiz->nome);
        printf("Avaliação média: %.2f\n", raiz->avaliacaoMedia);
        printf("Eventos:\n");
        for (int i = 0; i < raiz->numEventos; i++) {
            printf("  - %s (Avaliação: %.1f)\n", 
                   raiz->eventos[i].nome, 
                   raiz->eventos[i].avaliacao);
        }
        printf("\n");
    }
    
    buscarPorAvaliacao(raiz->esquerda, avaliacaoMinima);
    buscarPorAvaliacao(raiz->direita, avaliacaoMinima);
}

void mensagensAoUsuario() {
    if (rand() % 100 < 30) {
        int mensagemIndex = rand() % (sizeof(MENSAGENS) / sizeof(MENSAGENS[0]));
        printf("\n%s\n", MENSAGENS[mensagemIndex]);
    }
}

int main() {
    srand(time(NULL));
    NoCidade* raiz = NULL;
    int escolha;
    char nomeCidade[MAX_NOME];
    
    for (int i = 0; i < MAX_CIDADES; i++) {
        char nome[MAX_NOME];
        gerarNomeAleatorioCidade(nome);
        NoCidade* novaCidade = criarNoCidade(nome);
        gerarEventosAuto(novaCidade);
        inserirCidade(&raiz, novaCidade);
    }
    
    do {
        printf("\n===========================================\n");
        printf("    Roteiro Turistico Inteligente\n");
        printf("===========================================\n\n");
        
        printf("1. Visualizar Arvore de Cidades\n");
        printf("2. Buscar Cidade\n");
        printf("3. Ordenar Eventos\n");
        printf("4. Encontrar Rota\n");
        printf("5. Sair\n\n");
        
        printf("Use as teclas numéricas para navegar\n");
        printf("Pressione 'q' para sair\n");
        
        escolha = getchar();
        system("clear");
        
        switch (escolha) {
            case '1':
                printf("\nEscolha o tipo de percurso:\n");
                printf("1. Percurso Em Ordem\n");
                printf("2. Percurso Pré-Ordem\n"); 
                printf("3. Percurso Pós-Ordem\n");
                printf("4. Todos os percursos\n");
                
                getchar();
                char opcao = getchar();
                
                switch(opcao) {
                    case '1':
                        printf("\nPercurso Em Ordem:\n");
                        percorrerEmOrdem(raiz);
                        mensagensAoUsuario();
                        break;
                    case '2':
                        printf("\nPercurso Pré-Ordem:\n");
                        percorrerPreOrdem(raiz);
                        mensagensAoUsuario();
                        break;
                    case '3':
                        printf("\nPercurso Pós-Ordem:\n");
                        percorrerPoOrdem(raiz);
                        mensagensAoUsuario();
                        break;
                    case '4':
                        printf("\nPercurso Em Ordem:\n");
                        percorrerEmOrdem(raiz);
                        mensagensAoUsuario();
                        printf("\nPercurso Pré-Ordem:\n");
                        percorrerPreOrdem(raiz);
                        mensagensAoUsuario();
                        printf("\nPercurso Pós-Ordem:\n");
                        percorrerPoOrdem(raiz);
                        mensagensAoUsuario();
                        break;
                    default:
                        printf("\nOpção inválida!\n");
                }
                break;
                
            case '2':
                printf("\nEscolha o tipo de busca:\n");
                printf("1. Buscar por nome\n");
                printf("2. Buscar por avaliação média\n");
                printf("3. Buscar cidades próximas\n");
                printf("Escolha uma opção (1-3): ");
                
                getchar(); 
                char tipoBusca = getchar();
                getchar(); 
                
                switch(tipoBusca) {
                    case '1':
                        printf("\nDigite o nome da cidade para buscar: ");
                        fgets(nomeCidade, MAX_NOME, stdin);
                        nomeCidade[strcspn(nomeCidade, "\n")] = 0;
                        NoCidade* encontrada = buscarCidade(raiz, nomeCidade);
                        if (encontrada) {
                            printf("\nCidade encontrada!\n");
                            printf("\nEventos em %s:\n", encontrada->nome);
                            printf("Avaliação média da cidade: %.2f\n\n", encontrada->avaliacaoMedia);
                            for (int i = 0; i < encontrada->numEventos; i++) {
                                printf("%d. %s (Avaliação: %.1f)\n", 
                                    i + 1,
                                    encontrada->eventos[i].nome,
                                    encontrada->eventos[i].avaliacao);
                            }
                            mensagensAoUsuario();
                        } else {
                            printf("Cidade não encontrada!\n");
                        }
                        break;
                        
                    case '2':
                        printf("\nDigite a avaliação média mínima (0-10): ");
                        float avaliacaoMinima;
                        scanf("%f", &avaliacaoMinima);
                        getchar(); 
                        
                        printf("\nCidades encontradas com avaliação média >= %.2f:\n", avaliacaoMinima);
                        buscarPorAvaliacao(raiz, avaliacaoMinima);
                        mensagensAoUsuario();
                        break;
                        
                    case '3':
                        printf("\nDigite o nome da cidade atual: ");
                        fgets(nomeCidade, MAX_NOME, stdin);
                        nomeCidade[strcspn(nomeCidade, "\n")] = 0;
                        NoCidade* cidadeAtual = buscarCidade(raiz, nomeCidade);
                        
                        if (cidadeAtual) {
                            printf("\nCidades próximas a %s:\n", cidadeAtual->nome);
                            if (cidadeAtual->pai) {
                                printf("Cidade acima: %s (Avaliação: %.2f)\n", 
                                    cidadeAtual->pai->nome, 
                                    cidadeAtual->pai->avaliacaoMedia);
                            }
                            if (cidadeAtual->esquerda) {
                                printf("Cidade à esquerda: %s (Avaliação: %.2f)\n", 
                                    cidadeAtual->esquerda->nome, 
                                    cidadeAtual->esquerda->avaliacaoMedia);
                            }
                            if (cidadeAtual->direita) {
                                printf("Cidade à direita: %s (Avaliação: %.2f)\n", 
                                    cidadeAtual->direita->nome, 
                                    cidadeAtual->direita->avaliacaoMedia);
                            }
                            mensagensAoUsuario();
                        } else {
                            printf("Cidade não encontrada!\n");
                        }
                        break;
                        
                    default:
                        printf("Opção inválida!\n");
                }
                break;
                
            case '3':
                printf("Digite o nome da cidade: ");
                getchar();
                fgets(nomeCidade, MAX_NOME, stdin);
                nomeCidade[strcspn(nomeCidade, "\n")] = 0;
                ordenarEventosCidade(raiz, nomeCidade);
                mensagensAoUsuario();
                break;
                
            case '4':
                printf("Digite o nome da cidade origem: ");
                getchar();
                fgets(nomeCidade, MAX_NOME, stdin);
                nomeCidade[strcspn(nomeCidade, "\n")] = 0;
                NoCidade* origem = buscarCidade(raiz, nomeCidade);
                
                if (origem) {
                    printf("Digite o nome da cidade destino: ");
                    fgets(nomeCidade, MAX_NOME, stdin);
                    nomeCidade[strcspn(nomeCidade, "\n")] = 0;
                    NoCidade* destino = buscarCidade(raiz, nomeCidade);
                    
                    if (destino) {
                        encontrarRota(raiz, origem, destino);
                        mensagensAoUsuario();
                    } else {
                        printf("Cidade destino não encontrada!\n");
                    }
                } else {
                    printf("Cidade origem não encontrada!\n");
                }
                break;
                
            case '5':
                break;
        }
        
        printf("\nEnter - Para voltar ao menu");
        getchar();
        getchar(); 
        system("clear");
    } while (escolha != '5');
    
    return 0;
}