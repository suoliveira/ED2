#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int dado;
    struct No *esquerdo;
    struct No *direito;
    int altura;
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
No* inserirDado(No*, int);
void emOrdem(No*);
void posOrdem(No*);
void preOrdem(No*);


//AVL
int maior(int, int);
int alturaDoNo(No*);
int fatorDeBalanceamento(No*);
No* ll(No*);
No* rr(No*);
No* lr(No*);
No* rl(No*);
No* balancear(No*);


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
        no->altura = 0;
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
    if (dado > no->dado){
        buscaElementoABB(no->direito, dado);
    }else if (dado < no->dado){
        buscaElementoABB(no->esquerdo, dado);
    }else{
        printf("\nNodo com valor '%i' encontrado\n", no->dado);
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
            free(raiz);
            return temp;
        }
        No* temp = menorValor(raiz->direito);
        raiz->dado = temp->dado;
        raiz->direito = removeElementoABB(raiz->direito, temp->dado);
    }

    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;
    raiz = balancear(raiz);
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
    if (abb != NULL){
        abb->raiz = inserirDado(abb->raiz, valor);
    }
}

No* inserirDado(No* no, int dado){
    if (no == NULL){
        return criaNo(dado);
    }
    
    if (dado > no->dado){
        no->direito = inserirDado(no->direito, dado);
    }else {
        no->esquerdo = inserirDado(no->esquerdo, dado);
    }

    no->altura = maior(alturaDoNo(no->esquerdo), alturaDoNo(no->direito)) + 1;
    no = balancear(no);

    return no;
}

void emOrdem(No* raiz) {
    if (raiz != NULL){
        emOrdem(raiz->esquerdo);
        printf("%i, ", raiz->dado);
        emOrdem(raiz->direito);
    }
}

void posOrdem(No* raiz){
    if (raiz != NULL){
        posOrdem(raiz->esquerdo);
        posOrdem(raiz->direito);
        printf("%i, ", raiz->dado);
    }
}

void preOrdem(No* raiz){
    if(raiz != NULL){
        printf("%i, ", raiz->dado);
        preOrdem(raiz->esquerdo);
        preOrdem(raiz->direito);
    }
}

int maior(int a, int b){
    if(a > b){
        return a;
    }else{
        return b;
    }
}

int alturaDoNo(No* no){
    if (no == NULL){
        return -1;
    }else{
        return no->altura;
    } 
}

int fatorDeBalanceamento(No* no){
    if (no != NULL){
        return (alturaDoNo(no->esquerdo) - alturaDoNo(no->direito));
    }else{
        return 0;
    }  
}

No* ll(No* raiz){
    No* subArvore = raiz->direito;
    No* filho = subArvore->esquerdo;

    subArvore->esquerdo = raiz;
    raiz->direito = filho;

    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;
    subArvore->altura = maior(alturaDoNo(subArvore->esquerdo), alturaDoNo(subArvore->direito)) + 1;
    
    return subArvore;
 }

 No* rr(No* raiz){
    No* subArvore = raiz->esquerdo;
    No* filho = subArvore->direito;

    subArvore->direito = raiz;
    raiz->esquerdo = filho;

    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;
    subArvore->altura = maior(alturaDoNo(subArvore->esquerdo), alturaDoNo(subArvore->direito)) + 1;
    
    return subArvore;
 }

No* lr(No* raiz){
    raiz->esquerdo = ll(raiz->esquerdo);
    return rr(raiz);
}
 
 
No* rl(No* raiz){
    raiz->direito = rr(raiz->direito);
    return ll(raiz);
}

No* balancear(No* raiz){
    int fator = fatorDeBalanceamento(raiz);

    if (fator < -1 && fatorDeBalanceamento(raiz->direito) <= 0){
       raiz = ll(raiz);
    }else if (fator > 1 && fatorDeBalanceamento(raiz->esquerdo) >= 0){
        raiz = rr(raiz);
    }else if (fator > 1 && fatorDeBalanceamento(raiz->esquerdo) < 0){
        raiz = lr(raiz);
    }else if (fator < -1 && fatorDeBalanceamento(raiz->direito) > 0){
        raiz = rl(raiz);

    }
    
    return raiz;
}



int main(){
    ABB* abb;
    abb = criaABB();

    insereNaABB(abb, 10);
    insereNaABB(abb, 7);
    insereNaABB(abb, 6);
    insereNaABB(abb, 8);
    insereNaABB(abb, 12);
    insereNaABB(abb, 11);
    insereNaABB(abb, 13);
    insereNaABB(abb, 20);
    insereNaABB(abb, 15);

    preOrdem(abb->raiz);
    printf("\n");
    emOrdem(abb->raiz);
    printf("\n");
    posOrdem(abb->raiz);

    removeABB(abb);
    return 0;
    
}