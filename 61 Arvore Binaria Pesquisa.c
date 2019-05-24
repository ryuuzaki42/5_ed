#include<stdio.h>
#include<stdlib.h>

typedef struct sNo {
    int info;
    struct sNo *esq;
    struct sNo *dir;
} No;

void inicializarArvore(No **ptRaiz) {
    *ptRaiz = NULL;
}

void insereComRecursao(No **ptRaiz, int info2) { // Inserção com recursão
    if(*ptRaiz == NULL) {
        *ptRaiz=(No *)malloc(sizeof(No));

        if(*ptRaiz == NULL) {
            printf("\nErro.Memoria nao alocada");
            return;
        }

        (*ptRaiz)->esq=NULL;
        (*ptRaiz)->dir=NULL;
        (*ptRaiz)->info=info2;
    } else {
        if(info2 < ((*ptRaiz)->info))
            insereComRecursao(&((*ptRaiz)->esq), info2);
        else
            insereComRecursao(&((*ptRaiz)->dir), info2);
    }
}

void insereSemRecursao(No** ptRaiz, int info2) { // Inserção com recursão
    No* aux = *ptRaiz;
    No* aux2 = NULL;
    No* novo = (No *)malloc(sizeof(No));

    if(novo == NULL) {
        printf("\nErro: Memoria nao alocada");
        return;
    }

    novo->info = info2;
    novo->esq = NULL;
    novo->dir = NULL;

    while(aux != NULL) {
        aux2 = aux;

        if(info2 < aux->info)
            aux = aux->esq;
        else
            aux = aux->dir;
    }

    if(aux2 == NULL)
        *ptRaiz = novo;
    else {
        if(info2 < aux2->info)
            (aux2)->esq = novo;
        else
            (aux2)->dir = novo;
    }
}

void maiorValor(No* ptRaiz) {
    if((ptRaiz->dir != NULL) && (ptRaiz->dir->info > ptRaiz->info))
        maiorValor(ptRaiz->dir);
    else
        printf("Maior Valor: %d\n", ptRaiz->info);
}

void menorValor(No* ptRaiz) {
    if((ptRaiz->esq != NULL) && (ptRaiz->esq->info < ptRaiz->info))
        menorValor(ptRaiz->esq);
    else
        printf("Menor Valor: %d\n", ptRaiz->info);
}

No *MaiorDireita(No **no) { // Remoção
    if((*no)->dir != NULL)
        return MaiorDireita(&(*no)->dir);
    else {
        No *aux = *no;

        if((*no)->esq != NULL) // Se nao houver essa verificacao, esse nó vai perder todos os seus filhos da esq!
            *no = (*no)->esq;
        else {
            *no = NULL;
            return aux;
        }
    }

    return *no;
}

No *MenorEsquerda(No **no) {
    if((*no)->esq != NULL)
        return MenorEsquerda(&(*no)->esq);
    else {
        No *aux = *no;

        if((*no)->dir != NULL) // se nao houver essa verificacao, esse nó vai perder todos os seus filhos da dir!
            *no = (*no)->dir;
        else
            *no = NULL;

        return aux;
    }
}

void remover(No **ptRaiz, int info2) {
    if(*ptRaiz == NULL) { // Esta verificacao serve para caso o info nao exista na arvore.
        printf("Numero nao existe na arvore!");
        return;
    }

    if(info2 < (*ptRaiz)->info)
        remover(&(*ptRaiz)->esq, info2);
    else {
        if(info2 > (*ptRaiz)->info)
            remover(&(*ptRaiz)->dir, info2);
        else { // se nao eh menor nem maior, logo, eh o info que estou procurando! :)
            No *pAux = *ptRaiz; // quem programar no Embarcadero vai ter que declarar o pAux no inicio do void! :[

            if(((*ptRaiz)->esq == NULL) && ((*ptRaiz)->dir == NULL)) { // se nao houver filhos...
                free(pAux);
                (*ptRaiz) = NULL;
            } else { // so tem o filho da dir
                if((*ptRaiz)->esq == NULL) {
                    (*ptRaiz) = (*ptRaiz)->dir;
                    pAux->dir = NULL;
                    free(pAux);
                    pAux = NULL;
                } else { // so tem filho da esq
                    if((*ptRaiz)->dir == NULL) {
                        (*ptRaiz) = (*ptRaiz)->esq;
                        pAux->esq = NULL;
                        free(pAux);
                        pAux = NULL;
                    } else { // Escolhi fazer o maior filho direito da subarvore esq.
                        pAux = MaiorDireita(&(*ptRaiz)->esq); //se vc quiser usar o Menor da esq, so o que mudaria seria isso:
                        pAux->esq = (*ptRaiz)->esq; // pAux = MenorEsquerda(&(*ptRaiz)->dir);
                        pAux->dir = (*ptRaiz)->dir;
                        (*ptRaiz)->esq = (*ptRaiz)->dir = NULL;
                        free((*ptRaiz));
                        *ptRaiz = pAux;
                        pAux = NULL;
                    }
                }
            }
        }
    }
}

void printTrace(int level) {
    for(int i=0; i<level; i++)
        printf("-");
}

void imprimirArvore(No* ptRaiz, int level) {
    if(ptRaiz == NULL) {
        printTrace(level);
        printf("*\n");
        return;
    }

    imprimirArvore(ptRaiz->dir, level+1);
    printTrace(level);
    printf("%d\n", ptRaiz->info);
    imprimirArvore(ptRaiz->esq, level+1);
}

void visita(No *ptRaiz) {
    printf("%d\n",ptRaiz->info);
}

void exibirEmOrdem(No *ptRaiz) { // Em ordem
    if(ptRaiz != NULL) {
        exibirEmOrdem(ptRaiz->esq);
        visita(ptRaiz);
        exibirEmOrdem(ptRaiz->dir);
    }
}

void exibirPreOrdem(No *ptRaiz) { // Pré-ordem
    if(ptRaiz != NULL) {
        visita(ptRaiz);
        exibirPreOrdem(ptRaiz->esq);
        exibirPreOrdem(ptRaiz->dir);
    }
}

void exibirPosOrdem(No *ptRaiz) { // Pós-ordem
    if(ptRaiz != NULL) {
        exibirPosOrdem(ptRaiz->esq);
        exibirPosOrdem(ptRaiz->dir);
        visita(ptRaiz);
    }
}

int contarNos(No *ptRaiz) { // Contar nós
    if(ptRaiz == NULL)
        return 0;
    else
        return 1 + contarNos(ptRaiz->esq) + contarNos(ptRaiz->dir);
}

int contarFolhas(No *ptRaiz) { // Contar folhas
    if(ptRaiz == NULL)
        return 0;

    if(ptRaiz->esq == NULL && ptRaiz->dir == NULL)
        return 1;

    return contarFolhas(ptRaiz->esq) + contarFolhas(ptRaiz->dir);
}

int maior(int a, int b) {
    if(a > b)
        return a;
    else
        return b;
}

int alturaArvore(No *ptRaiz) { // Altura da árvore
    if((ptRaiz == NULL) || (ptRaiz->esq == NULL && ptRaiz->dir == NULL))
        return 0;
    else
        return 1 + maior(alturaArvore(ptRaiz->esq), alturaArvore(ptRaiz->dir));
}

int procuraElementoSemRecursao(No *ptRaiz, int info2) { // Procura o elemento na árvore // O(log n)
    No* temp = ptRaiz;
    int parar=0;

    if(ptRaiz==NULL)
        return 0;
    else if(temp->esq== NULL && temp->dir==NULL) {
        if(temp->info == info2)
            return 1;
        else
            return 0;
    } else if(temp->info==info2)
        return 1;
    else {
        while(parar==0) {
            if(temp->info < info2) {
                if(temp->esq == NULL) {
                    parar++;

                    if(temp->info==info2) {
                        break;
                        return 1;
                    } else
                        return 0;
                } else {
                    temp=temp->esq;

                    if(temp->info== info2) {
                        return 1;
                        break;
                    }
                }
            } else if(temp->info > info2) {
                if(temp->dir== NULL) {
                    parar++;

                    if(temp->info==info2) {
                        return 1;
                        break;
                    } else
                        return 0;
                } else {
                    temp=temp->dir;

                    if(temp->info== info2) {
                        return 1;
                        break;
                    }
                }
            }
        }
    }

    return 0;
}

No* procuraElementoComRecursao(No *ptRaiz, int info2) { // Procura o elemento na árvore // O(log n)
    No* aux;
    aux = ptRaiz;

    if(aux == NULL)
        return NULL;
    else if(info2 < aux->info)
        return procuraElementoComRecursao(aux->esq, info2);
    else if(info2 > aux->info)
        return procuraElementoComRecursao(aux->dir, info2);
    else
        return aux;
}

int main() {
    int info2, opcao;
    No *ptRaiz;
    inicializarArvore(&ptRaiz);

    while(1) {
        printf("\nArvore Binaria de Pesquisada");
        printf("\n 1 insere sem recursao");
        printf("\n 2 insere com recursao");
        printf("\n 3 remover");
        printf("\n 4 exibirPreOrdem");
        printf("\n 5 exibirEmOrdem");
        printf("\n 6 exibirPosOrdem");
        printf("\n 7 contarFolhas");
        printf("\n 8 contarNos");
        printf("\n 9 alturaArvore");
        printf("\n10 procuraElementoSemRecursao");
        printf("\n11 procuraElementoComRecursao");
        printf("\n12 Mostrar a arvore lateralmente");
        printf("\n13 maior valor");
        printf("\n14 menor valor");
        printf("\n 0 Para sair do programa");
        printf("\nDigite a opcao desejada: ");
        scanf("%d", &opcao);
        printf("\n");

        switch(opcao) {
            case 1:
                printf("Numero a ser inserido: ");
                scanf("%d", &info2);
                insereComRecursao(&ptRaiz, info2);
                break;

            case 2:
                printf("Numero a ser inserido: ");
                scanf("%d", &info2);
                insereSemRecursao(&ptRaiz, info2);
                break;

            case 3:
                printf("Numero a ser remvido: ");
                scanf("%d", &info2);
                remover(&ptRaiz, info2);
                break;

            case 4:
                exibirPreOrdem(ptRaiz);
                break;

            case 5:
                exibirEmOrdem(ptRaiz);
                break;

            case 6:
                exibirPosOrdem(ptRaiz);
                break;

            case 7:
                printf("Quantidade de folhas: %d", contarFolhas(ptRaiz));
                break;

            case 8:
                printf("Quantidade de nos: %d", contarNos(ptRaiz));
                break;

            case 9:
                printf("Altura da arvore: %d", alturaArvore(ptRaiz));
                break;

            case 10:
                printf("Numero a ser pesquisado: ");
                scanf("%d", &info2);

                if(procuraElementoSemRecursao(ptRaiz, info2) == 1)
                    printf("\n\nElemento %d encontrado", info2);
                else
                    printf("\n\nElemento nao %d encontrado", info2);

                break;

            case 11:
                printf("Numero a ser pesquisado: ");
                scanf("%d", &info2);

                if(procuraElementoComRecursao(ptRaiz, info2) != NULL)
                    printf("\n\nElemento %d encontrado", info2);
                else
                    printf("\n\nElemento nao %d encontrado", info2);

                break;

            case 12:
                imprimirArvore(ptRaiz, 0);
                break;

            case 13:
                maiorValor(ptRaiz);
                break;

            case 14:
                menorValor(ptRaiz);
                break;

            case 0:
                exit(0);
                break;

            default:
                printf("A opcao: %d e invalida", opcao);
                break;
        }
    }
}