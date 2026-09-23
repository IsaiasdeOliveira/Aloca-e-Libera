#include <stdio.h>
#include <stdlib.h>

#define TAM_MEMORIA(16 * 1024)

static unsigned char
memoria[TAM_MEMORIA];

typedef struct No {
    int valor;
    struct No *anterior;
    struct No *proximo;
} No;

typedef struct Bloco {
   size_t tamanho;
   int livre;
   struct Bloco *proximo;
}Bloco;

void inicializaMemoria(){

   Bloco*primeiro= (Bloco *) memoria;
   primeiro->tamanho = TAM_MEMORIA - sizeof(Bloco);
   primeiro->livre = 1;
   primeiro->proximo = NULL;

}

void*aloca(size_t tamanho) {

Bloco *bloco = (Bloco *) memoria;
 
while(bloco != NULL) {

  if(bloco->livre && bloco->tamanho >= tamanho){

    if(bloco->tamanho >= tamanho + sizeof(Bloco) + 1){

     Bloco *novoBloco = (Bloco *)((unsigned char*)(bloco + 1) + tamanho);
     
     novoBloco->livre = 1;
     novoBloco->proximo = bloco-> proximo;

     bloco->tamanho = tamanho;
     bloco->proximo = novoBloco;
    }
    
   bloco-> livre = 0;

   return(void*)(bloco + 1);
  }
   bloco= bloco->proximo;
  }
 return NULL; 


void*libera(void*p){
  
  if(p == NULL) return;

   Bloco *bloco = ((Bloco *)p) - 1;
  
  bloco->livre = 1;
}


No *criarNo(int valor) {
    No *novo = (No *) aloca(sizeof(No));

    if (novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    novo->valor = valor;
    novo->anterior = NULL;
    novo->proximo = NULL;

    return novo;
}

void inserirFinal(No **inicio, int valor) {
    No *novo = criarNo(valor);

    if (*inicio == NULL) {
        *inicio = novo;
        return;
    }

    No *atual = *inicio;

    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }

    atual->proximo = novo;
    novo->anterior = atual;
}

void imprimirLista(No *inicio) {
    No *atual = inicio;

    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }

    printf("\n");
}

void liberarLista(No *inicio) {
    No *atual = inicio;

    while (atual != NULL) {
        No *proximo = atual->proximo;
        libera(atual);
        atual = proximo;
    }
}

int main() {
    No *inicio = NULL;

    inicializaMemoria();
    inserirFinal(&inicio, 10);
    inserirFinal(&inicio, 20);
    inserirFinal(&inicio, 30);

    printf("Lista: ");
    imprimirLista(inicio);

    liberarLista(inicio);

    return 0;
}
