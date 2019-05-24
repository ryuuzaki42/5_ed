#include<stdio.h>

#include "0 os.h" // To use clean_output() and clean_stdin()

typedef struct sAluno {
    char nome[100];
    int idade;
} Aluno;

typedef struct sCelula {
    Aluno info;
    struct sCelula *next;
} Lista;

void inicializar(Lista** lista) {
    (*lista) = NULL;
}

int listaVazia(Lista* lista) {
    if(lista == NULL)
        return 1;

    return 0;
}

Lista* getnode() {
    return (Lista*) malloc(sizeof(Lista));
}

// INSERIR
int inserirNoInicio(Lista** lista, Aluno novo) {
    Lista* nova = getnode();
    nova->info = novo;
    nova->next = NULL;

    if(listaVazia((*lista))) {
        (*lista) = nova;
        return 1;
    }

    nova->next = (*lista);
    (*lista) = nova;
    return 1;
}

int inserirNoFim(Lista** lista, Aluno novo) {
    Lista* nova = getnode();
    nova->info = novo;
    nova->next = NULL;

    if(listaVazia((*lista))) {
        (*lista) = nova;
        return 1;
    }

    Lista* aux = (*lista);

    while(aux->next != NULL)
        aux = aux->next;

    aux->next = nova;
    return 1;
}

void inserirPosicaoK(Lista** lista, Aluno novo, int k) {
    if(k < 1)
        printf("posicao k: %d nao e valida", k);
    else {
        Lista *aux, *ant, *q;
        aux = (*lista);
        int sizeLista = 0, i=1;

        while(aux != NULL) {
            sizeLista++;
            aux = aux->next;
        }

        if(k == 1)
            inserirNoInicio(lista, novo);
        else if(k == (sizeLista +1))
            inserirNoFim(lista, novo);
        else {
            if(k > (sizeLista + 1)) // Posicao (sizeLista + 1) deve aceita
                printf("posicao k: %d nao e valida", k);
            else {
                aux = (*lista);

                while(i < k) {
                    ant = aux;
                    aux = aux->next;
                    i++;
                }

                q = getnode();
                q->info = novo;
                ant->next = q;
                q->next = aux;
            }
        }
    }
}

// REMOVER
void removerNoInicio(Lista** lista) {
    if(listaVazia((*lista)))
        printf("\nLista Vazia :(\n");
    else {
        Aluno removido;
        Lista* aux = (*lista);
        (*lista) = (*lista)->next;
        removido = aux->info;
        free(aux);
        printf("ELEMENTO REMOVIDO: %s\n", removido.nome);
        printf("\nTudo certo :)\n");
    }
}

void removerNoFim(Lista** lista) {
    if(listaVazia((*lista)))
        printf("\nLista Vazia :(\n");
    else {
        Aluno removido;
        Lista* ant = NULL;
        Lista* aux = (*lista);

        while(aux->next != NULL) {
            ant = aux;
            aux = aux->next;
        }

        ant->next = NULL;
        removido = aux->info;
        free(aux);
        printf("ELEMENTO REMOVIDO: %s\n", removido.nome);
        printf("\nTudo certo :)\n");
    }
}

// EXTRA
void liberarLista(Lista** lista) {
    if(listaVazia(*lista))
        printf("\nLista Vazia!\n");
    else {
        Lista *removida;

        while((*lista) != NULL) {
            removida = (*lista);
            (*lista) = (*lista)->next;
            free(removida);
        }
    }
}

// IMPRIMIR
void imprimirLista(Lista** lista) {
    printf("\nImprimir Lista\n");

    if(listaVazia(*lista))
        printf("\nLista Vazia!\n");
    else {
        Lista *aux = (*lista);
        int i = 1;
        printf("id - nome - idade\n");

        while(aux != NULL) {
            printf("%d - %s - %d\n",i,aux->info.nome,aux->info.idade);
            i++;
            aux = aux->next;
        }

        printf("\n");
    }
}

void Menu() {
    printf("\n::INSERIR\n");
    printf("  [1] - Inserir no Inicio\n");
    printf("  [2] - Inserir na posicao K\n");
    printf("  [3] - Inserir no Final\n");
    printf("::REMOVER\n");
    printf("  [4] - Remover no Inicio\n");
    printf("  [5] - Remover no Final\n");
    printf("::MOSTRAR\n");
    printf("  [6] - Liberar Lista\n");
    printf("  [7] - Mostrar Lista\n\n");
    printf("::SAIR\n");
    printf("  [0] - Sair\n");
}

int main() {
    Lista* lista;
    Aluno a;
    int k, option;
    inicializar(&lista);

    do {
        Menu();
        printf("\nDigite uma opcao valida: ");
        scanf("%d", &option);
        clean_output();
        clean_stdin();

        switch(option) {
            case 0:
                liberarLista(&lista);
                return 0;

            case 1: // Inserir no Inicio
                printf("Digite o nome do aluno: ");
                scanf("%s", a.nome);
                printf("Digite a idade do aluno: ");
                scanf("%d", &a.idade);

                if(inserirNoInicio(&lista, a))
                    printf("\nTudo certo :)\n");
                else
                    printf("\nOcorreu um erro :(\n");

                break;

            case 2: // Inserir na posicao k
                printf("Digite o nome do aluno: ");
                scanf("%s", a.nome);
                printf("Digite a idade do aluno: ");
                scanf("%d", &a.idade);
                clean_stdin();
                printf("Digite a posicao para inserir: ");
                scanf("%d", &k);
                inserirPosicaoK(&lista, a, k);
                break;

            case 3: // Inserir no final
                printf("Digite o nome do aluno: ");
                scanf("%s", a.nome);
                printf("Digite a idade do aluno: ");
                scanf("%d", &a.idade);

                if(inserirNoFim(&lista, a))
                    printf("\nTudo certo :)\n");
                else
                    printf("\nOcorreu um erro :(\n");

                break;

            case 4: // Remover no inicio
                removerNoInicio(&lista);
                break;

            case 5: // Remover no final
                removerNoFim(&lista);
                break;

            case 6:
                liberarLista(&lista);
                break;

            case 7: // Mostrar Lista
                imprimirLista(&lista);
                break;

            default:
                printf("\nOpcao invalida\n");
                break;
        }
    } while(1);

    return 0;
}
