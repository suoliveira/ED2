#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int dado;
    struct No *esquerdo;
    struct No *direito;
} No;

typedef struct{
    struct No *raiz;
} ABB;

//Protótipo
No* alocaMemoriaNo();
ABB* alocaMemoriaABB();
No* criaNo(int);
ABB* criaABB();
void removeABB(ABB*);
No* buscaElementoABB(No*, int);
No* removeElementoABB(No*, int);
No* menorValor(No*);
void liberaMemoriaABB(No*);
void escreveABB(ABB*);
void insereNaABB(ABB*, int);
No* inserir(No*, int);
void emOrdem(No*);



No* alocaMemoriaNo() {
    return (No*) malloc(sizeof(No));
}

ABB* alocaMemoriaABB(){
    return (ABB*) malloc(sizeof(ABB));
}

No* criaNo(int dado){
    No* no = alocaMemoriaNo();
    
    if (no != NULL){
        no->direito = NULL;
        no->esquerdo = NULL;
        no->dado = dado;
    }
        
    return no;
}

ABB* criaABB(){
    ABB* abb = alocaMemoriaABB();
    
    if (abb != NULL)
        abb->raiz = NULL;

    return abb;
}

void removeABB(ABB* abb){
    if (abb != NULL){
        liberaMemoriaABB(abb->raiz);
        free(abb);
    }
}

No* buscaElementoABB(No* no, int dado) {
    if (no != NULL && no->dado == dado) {
        return no;
    }
    
    if (dado > no->dado){
        no->direito = buscaElementoABB(no->direito, dado);
    }else {
        no->esquerdo = buscaElementoABB(no->esquerdo, dado);
    }
    
}


No* removeElementoABB(No* raiz, int dado) {
    if (raiz == NULL)
        return raiz;
    if (dado < raiz->dado)
        raiz->esquerdo = removeElementoABB(raiz->esquerdo, dado);
    else if (dado > raiz->dado)
        raiz->direito = removeElementoABB(raiz->direito, dado);
    else {
        if(raiz->esquerdo == NULL) {
            No* temp = raiz->direito;
            printf("\napagando: %i\n", raiz->dado);
            free(raiz);
            return temp;
        } else if ( raiz->direito == NULL) {
            No* temp = raiz->esquerdo;
            printf("\napagando: %i\n", raiz->dado);
            free(raiz);
            return temp;
        }
        No* temp = menorValor(raiz->direito);
        raiz->dado = temp->dado;
        raiz->direito = removeElementoABB(raiz->direito, temp->dado);
    }
    return raiz;
}

No* menorValor(No* no){
    No* atual = no;
    while (atual->esquerdo != NULL)
        atual = atual->esquerdo;
    return atual;
}

void liberaMemoriaABB(No* no) {
    if (no != NULL) {
        liberaMemoriaABB(no->esquerdo);
        liberaMemoriaABB(no->direito);
        free(no);
    }
}

void escreveABB(ABB *abb){
    printf("Valores na ABB:\n");
    if (abb != NULL && abb->raiz != NULL)
        emOrdem(abb->raiz);
    else
        printf("Arvore vazia!\n");
}

void insereNaABB(ABB *abb, int valor){
    if (abb != NULL)
        abb->raiz = inserir(abb->raiz, valor);
}


No* inserir(No* no, int dado){
    if (no == NULL){
        return criaNo(dado);
    }
    
    if (dado > no->dado){
        no->direito = inserir(no->direito, dado);
    }else {
        no->esquerdo = inserir(no->esquerdo, dado);
    }

    return no;
}
void emOrdem(No* raiz) {
    if (raiz != NULL){
        emOrdem(raiz->esquerdo);
        printf("%i, ", raiz->dado);
        emOrdem(raiz->direito);
    }
}





int main(){
    ABB* abb;
    abb = criaABB();

    insereNaABB(abb, 7);
    insereNaABB(abb, 8);
    insereNaABB(abb, 6);
    insereNaABB(abb, 12);
    //insereNaABB(abb, 2);
    //insereNaABB(abb, 42);
    //insereNaABB(abb, 3);
    //insereNaABB(abb, 20);
    //insereNaABB(abb, 13);
    //insereNaABB(abb, 4);
    escreveABB(abb);
    removeElementoABB(abb->raiz, 7);
    //printf("\nEncontrado: %i \n", buscaElementoABB(abb->raiz, 12)->dado);
    escreveABB(abb);

    return 0;
}