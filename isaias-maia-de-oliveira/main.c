#include <stdio.h>
#include <stdlib.h>

#define TAM_MEMORIA (16 * 1024)

static unsigned char memoria[TAM_MEMORIA];

typedef struct No {
    int valor;
    struct No *anterior;
    struct No *proximo;
} No;

typedef struct Bloco {
    size_t tamanho;
    int livre;
    struct Bloco *proximo;
} Bloco;

void inicializaMemoria() {

    Bloco *primeiro = (Bloco *)memoria;

    primeiro->tamanho = TAM_MEMORIA - sizeof(Bloco);
    primeiro->livre = 1;
    primeiro->proximo = NULL;
}

void *aloca(size_t tamanho) {

    Bloco *bloco = (Bloco *)memoria;

    while (bloco != NULL) {

        if (bloco->livre && bloco->tamanho >= tamanho) {

            if (bloco->tamanho >= tamanho + sizeof(Bloco) + 1) {

                Bloco *novoBloco =
                    (Bloco *)((unsigned char *)(bloco + 1) + tamanho);

                novoBloco->livre = 1;
                novoBloco->proximo = bloco->proximo;

                bloco->tamanho = tamanho;
                bloco->proximo = novoBloco;
            }

            bloco->livre = 0;

            return (void *)(bloco + 1);
        }

        bloco = bloco->proximo;
    }

    return NULL;
}  // ← ESSA CHAVE ESTAVA FALTANDO

void libera(void *p) {

    if (p == NULL)
        return;

    Bloco *bloco = ((Bloco *)p) - 1;

    bloco->livre = 1;
}
