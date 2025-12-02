#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

/*
 * criarSala()
 * Cria dinamicamente uma sala (nó da árvore binária) com o nome informado.
 * Inicializa os ponteiros esquerda e direita como NULL.
 */
Sala* criarSala(const char *nome) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

/*
 * explorarSalas()
 * Função responsável por permitir que o jogador navegue pelo mapa da mansão.
 * A cada sala visitada, o jogador escolhe ir para a esquerda (e), direita (d)
 * ou sair (s). A exploração termina ao chegar a um nó-folha.
 */
void explorarSalas(Sala *atual) {
    char escolha;

    while (atual != NULL) {
        printf("\nVocê está em: %s\n", atual->nome);

        // Verifica se é nó-folha
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Você chegou a um cômodo sem saídas. Exploração encerrada!\n");
            return;
        }

        printf("Escolha um caminho:\n");
        if (atual->esquerda != NULL) printf("  (e) Ir para a esquerda -> %s\n", atual->esquerda->nome);
        if (atual->direita != NULL)  printf("  (d) Ir para a direita  -> %s\n", atual->direita->nome);
        printf("  (s) Sair da exploração\n");

        printf("Digite sua escolha: ");
        scanf(" %c", &escolha);

        if (escolha == 'e' || escolha == 'E') {
            if (atual->esquerda != NULL)
                atual = atual->esquerda;
            else
                printf("Caminho inexistente!\n");

        } else if (escolha == 'd' || escolha == 'D') {
            if (atual->direita != NULL)
                atual = atual->direita;
            else
                printf("Caminho inexistente!\n");

        } else if (escolha == 's' || escolha == 'S') {
            printf("Saindo da exploração...\n");
            return;

        } else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}

/*
 * main()
 * Monta o mapa fixo da mansão através de uma árvore binária
 * e inicia o processo de exploração.
 */
int main() {
    // Criando o mapa da mansão
    Sala *hall        = criarSala("Hall de Entrada");
    Sala *salaEstar   = criarSala("Sala de Estar");
    Sala *cozinha     = criarSala("Cozinha");
    Sala *biblioteca  = criarSala("Biblioteca");
    Sala *escritorio  = criarSala("Escritório");
    Sala *jardim      = criarSala("Jardim");
    Sala *porao       = criarSala("Porão");

    /*
            Hall
           /    \
     SalaEstar  Cozinha
        /   \      \
  Biblioteca Escritório
                    \
                   Porão
    */

    hall->esquerda = salaEstar;
    hall->direita  = cozinha;

    salaEstar->esquerda = biblioteca;
    salaEstar->direita  = escritorio;

    cozinha->direita = jardim;

    escritorio->direita = porao;

    printf("=== Detective Quest: Exploração da Mansão ===\n");
    explorarSalas(hall);

    return 0;
}
