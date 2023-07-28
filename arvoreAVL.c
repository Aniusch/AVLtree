#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int valor;
    struct nodo *esq;
    struct nodo *dir;
    struct nodo *pai;
    int h;
} Nodo;

Nodo* criarNodo(int v);
Nodo* buscar(Nodo *raiz, int v);
void mostraArvore(Nodo *p, int nivel);
Nodo* inserirNodo(Nodo *raiz, int v);
Nodo* excluir(Nodo *raiz, int v);
int fb(Nodo *p);
Nodo* rotEsq(Nodo *raiz);
Nodo* rotDir(Nodo *raiz);
Nodo* rotEsqDir(Nodo *raiz);
Nodo* rotDirEsq(Nodo *raiz);
Nodo* balancear(Nodo *raiz);

Nodo* criarNodo(int v){
    Nodo *p = (Nodo*)malloc(sizeof(Nodo));
    p->valor = v;
    p->esq = NULL;
    p->dir = NULL;
    p->pai = NULL;
    p->h = 0;
    return p;
}

int fb(Nodo *p){ // funcao de balanceamento
    int temp;
    if(p){
        if(!p->esq && !p->dir){
            temp = 0;
            p->h = 1;
            return temp;
            }
        else if(!p->esq){temp = 0 - p->dir->h;}
        else if(!p->dir){temp = p->esq->h;}
        else{temp = p->esq->h - p->dir->h;}

        if(temp > 0){p->h = p->esq->h + 1;}
        else if(temp < 0){p->h = p->dir->h + 1;}
        else{p->h = p->esq->h + 1;}
        return temp;
    }
    else {return 0;}
}

Nodo* rotDir(Nodo* raiz) {
    Nodo* q = raiz->esq;
    Nodo* temp = q->dir;
    q->dir = raiz;
    raiz->esq = temp;
    int b = fb(q->dir);
    b = fb(q);
    return q;
}

Nodo* rotEsq(Nodo* raiz) {
    Nodo* q = raiz->dir;
    Nodo* temp = q->esq;
    q->esq = raiz;
    raiz->dir = temp;
    int b = fb(q->esq);
    b = fb(q);
    return q;
}

Nodo* rotEsqDir(Nodo* raiz) {
    raiz->esq = rotEsq(raiz->esq);
    return rotDir(raiz);
}

Nodo* rotDirEsq(Nodo* raiz) {
    raiz->dir = rotDir(raiz->dir);
    return rotEsq(raiz);
}

Nodo* balancear(Nodo* raiz) {
    if (raiz == NULL)
        return NULL;
    
    int q = fb(raiz);
    if (q > 1) {
        if (fb(raiz->esq) < 0){
            raiz = rotEsqDir(raiz);}
        else{
            raiz = rotDir(raiz);}
    } else if (q < -1) {
        if (fb(raiz->dir) > 0)
            raiz = rotDirEsq(raiz);
        else{
            raiz = rotEsq(raiz);}
    }
    q = fb(raiz);
    return raiz;
}

void mostraArvore(Nodo *p, int nivel){
    int i;
    if(p){
        mostraArvore(p->dir,nivel+1);
        printf("\n");
        for(i=0;i<nivel;i++)
            printf("\t");
        printf("%i [%i|%i]\n",p->valor,p->h,fb(p));
        mostraArvore(p->esq,nivel+1);
    }
}

Nodo* inserirNodo(Nodo *raiz, int v){
    if(!raiz){
        raiz = criarNodo(v);
    }else{
        if(v <= raiz->valor){
            raiz->esq = inserirNodo(raiz->esq,v);
            raiz->esq->pai = raiz;
        }else{
            raiz->dir = inserirNodo(raiz->dir,v);
            raiz->dir->pai = raiz;
        }
    }
    raiz = balancear(raiz);
    return raiz;
}

Nodo* buscar(Nodo *raiz, int v){
    if(raiz){
        if(v == raiz->valor){
            return raiz;
        }else if(v < raiz->valor){
            return buscar(raiz->esq, v);
        }else
            return buscar(raiz->dir, v);
    }else
        return NULL;
}

Nodo* excluir(Nodo *p, int v){
    Nodo *f, *t;
    if(!p){
        return NULL;
    } else if(p->valor > v){
        p->esq = excluir(p->esq, v);
    } else if(p->valor < v){
        p->dir = excluir(p->dir, v);
    } else{
        if(!p->dir && !p->esq){
            free(p);
            p = NULL;
            return p;
        } else if(!p->dir){
            t = p;
            p = p->esq;
            free(t);
            return p;
        } else if(!p->esq){
            t = p;
            p = p->dir;
            free(t);
            return p;
        } else{
            f = p->esq;
            while(f->dir){
                f = f->dir;
            }
            p->valor = f->valor;
            p->esq = excluir(p->esq, p->valor);
        }
    }
    if (p) {
        int q = fb(p);
        p = balancear(p);
    }
    return p;
}

int main(){
    Nodo *raiz = NULL, *aux = NULL;
    int op, v;
    do{
        mostraArvore(raiz,0);
        printf("\n--------------------------------------------------\n");
        printf("1 - inserir novo nodo\n");
        printf("2 - excluir nodo\n");
        printf("3 - buscar nodo\n");
        printf("0 - sair\n");
        printf("opcao: ");
        scanf("%d",&op);

        switch(op){
        case 1:
            printf("Informe o valor (int): ");
            scanf("%d",&v);
            raiz = inserirNodo(raiz,v);
            break;
        case 2:
            printf("Informe o valor (int): ");
            scanf("%d",&v);
            raiz = excluir(raiz, v);
            break;
        case 3:
            printf("Informe o valor (int): ");
            scanf("%d",&v);
            if(aux = buscar(raiz,v))
                printf("valor encontrado\n");
            else
                printf("valor nao pertence a arvore\n");
            break;
        case 0:
            printf("saindo...\n");
            break;
        default:
            printf("opcao invalida\n");
        }
        printf("\n\n\n");
    }while(op!=0);

    return 0;
}