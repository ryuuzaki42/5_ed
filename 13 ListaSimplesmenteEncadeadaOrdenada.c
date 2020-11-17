#include<stdio.h>
#include<string.h>

#include "0 os.h" // To use clean_output() and clean_stdin()

typedef struct sAluno {
    char nome[100];
    int idade;
} Aluno;

typedef struct sCelula {
    Aluno info;
    struct sCelula *next;
    int cont;
} Lista;

void inicializar(Lista** lista) {
    (*lista) = NULL;
}

int listaVazia(Lista* lista) {
    if(lista == NULL)
        return 1;

    return 0;
}

Lista* criarCelula() {
    return (Lista*) malloc(sizeof(Lista));
}

// INSERIR
int inserirNoInicio(Lista** lista, Aluno novo) {
    Lista* nova = criarCelula();
    nova->info = novo;
    nova->next = NULL;
    nova->cont = 0;

    if(listaVazia((*lista))) {
        (*lista) = nova;
        return 1;
    }

    nova->next = (*lista);
    (*lista) = nova;
    return 1;
}

int inserirNoFim(Lista** lista, Aluno novo) {
    Lista* nova = criarCelula();
    nova->info = novo;
    nova->next = NULL;
    nova->cont = 0;

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

int inserirOrdenado(Lista **lista, Lista* inserir) {
    Lista* nova = inserir;

    if(listaVazia((*lista))) {
        (*lista) = nova;
        return 1;
    }

    Lista* ant = NULL;
    Lista* aux = (*lista);

    while(aux != NULL && aux->cont >= nova->cont) {
        ant = aux;
        aux = aux->next;
    }

    if(aux == (*lista)) {
        nova->next = (*lista);
        (*lista) = nova;
        return 1;
    }

    nova->next = aux;
    ant->next = nova;
    return 1;
}

// REMOVER
Aluno removerNoInicio(Lista** lista) {
    Aluno removido;

    if(listaVazia((*lista)))
        return removido;

    Lista* aux = (*lista);
    (*lista) = (*lista)->next;
    removido = aux->info;
    free(aux);
    return removido;
}

Aluno removerNoFim(Lista** lista) {
    Aluno removido;

    if(listaVazia((*lista)))
        return removido;

    Lista* ant = NULL;
    Lista* aux = (*lista);

    while(aux->next != NULL) {
        ant = aux;
        aux = aux->next;
    }

    ant->next = NULL;
    removido = aux->info;
    free(aux);
    return removido;
}

int removerNaPosicao(Lista** lista, Lista* aluno_pesquisado) { // Error
    if(listaVazia((*lista)))
        return 0;

    Lista* ant = NULL;
    Lista* aux = (*lista);

    while(aux != aluno_pesquisado) {
        ant = aux;
        aux = aux->next;
    }

    if((*lista)->next == NULL) {
        (*lista) = NULL;
        return 1;
    }

    ant->next = aux->next;
    return 1;
}

// EXTRAS
Lista* pesquisarElemento(Lista** lista, Aluno pesquisado) {
    if(listaVazia((*lista)))
        return NULL;

    Lista* aux = (*lista);

    while(aux != NULL) {
        if(strcmp(aux->info.nome, pesquisado.nome) == 0) {
            aux->cont++;
            removerNaPosicao(lista, aux);
            inserirOrdenado(lista, aux);
            return aux;
        }

        aux = aux->next;
    }

    return NULL;
}

void liberarLista(Lista** lista) {
    if(listaVazia(*lista)) {
        printf("Lista Vazia!\n");
        return;
    }

    Lista *removida;

    while((*lista) != NULL) {
        removida = (*lista);
        (*lista) = (*lista)->next;
        free(removida);
    }
}

// IMPRIMIR
void imprimirLista(Lista** lista) {
    printf("Imprimir Lista\n");
    Lista *aux = (*lista);
    int i = 1;
    printf("id - nome - idade - cont\n");

    while(aux != NULL) {
        printf("%d - %s - %d - %d\n", i, aux->info.nome, aux->info.idade, aux->cont);
        i++;
        aux = aux->next;
    }

    printf("\n\n");
}

void Menu() {
    printf("\n::INSERIR\n");
    printf("  [1] - Inserir no Inicio\n");
    printf("  [2] - Inserir no Final\n");
    printf("  [3] - Inserir no Ordenado\n\n");
    printf("::REMOVER\n");
    printf("  [4] - Remover no Inicio\n");
    printf("  [5] - Remover no Final\n");
    printf("  [6] - Remover no na Posicao k\n");
    printf("::MOSTRAR\n");
    printf("  [7] - Pesquisar na Lista\n");
    printf("  [8] - Liberar Lista\n\n");
    printf("  [9] - Mostrar Lista\n\n");
    printf("::SAIR\n");
    printf("  [0] - Sair\n");
}

int main() {
    Lista* lista;
    Aluno a;
    int option;
    inicializar(&lista);

    do {
        Menu();
        printf("\nDigite uma opcao valida: ");
        scanf("%d", &option);
        clean_output();
        clean_stdin();

        switch(option) {
            case 0:
                return 0;

            case 1: // Inserir no Inicio
                printf("Digite o nome do aluno: ");
                scanf("%s", a.nome);
                printf("Digite a idade do aluno: ");
                scanf("%d", &a.idade);

                if(inserirNoInicio(&lista, a))
                    printf("Tudo certo :)\n");
                else
                    printf("\n Ocorreu um erro :(\n");

                break;

            case 2: // Inserir no final
                printf("Digite o nome do aluno: ");
                scanf("%s", a.nome);
                printf("Digite a idade do aluno: ");
                scanf("%d", &a.idade);

                if(inserirNoFim(&lista, a))
                    printf("Tudo certo :)");
                else
                    printf("\nOcorreu um erro :(\n");

                break;

            case 3: // Inerir ordenado
                printf("Digite o nome do aluno: ");
                scanf("%s", a.nome);
                printf("Digite a idade do aluno: ");
                scanf("%d", &a.idade);
                Lista* nova = criarCelula();
                nova->info = a;
                nova->next = NULL;
                nova->cont = 0;

                if(inserirOrdenado(&lista, nova))
                    printf("\nTudo certo :)");
                else
                    printf("\n Ocorreu um erro :(\n");

                break;

            case 4: // Remover no inicio
                a = removerNoInicio(&lista);

                if(a.nome) {
                    printf("ELEMENTO REMOVIDO: %s\n", a.nome);
                    printf("\nTudo certo :)\n");
                } else
                    printf("\nLista Vazia :(\n");

                break;

            case 5: // Remover no final
                a = removerNoFim(&lista);

                if(a.nome) {
                    printf("ELEMENTO REMOVIDO: %s\n", a.nome);
                    printf("Tudo certo :)\n");
                } else
                    printf("\nLista Vazia :(\n");

                break;

            case 6: // Remover na posicao K
                imprimirLista(&lista);
                printf("Digite o nome do aluno para remover: ");
                scanf("%s", a.nome);
                Lista* l = pesquisarElemento(&lista, a);

                if(l != NULL) {
                    if(removerNaPosicao(&lista,l))
                        printf("Tudo certo :)");
                    else
                        printf("\nOcorreu um erro :(\n");
                } else
                    printf("\nOcorreu um erro :(\n");

                break;

            case 7:
                imprimirLista(&lista);
                printf("Digite o nome do aluno para pesquisar: ");
                scanf("%s", a.nome);
                Lista* l2 = pesquisarElemento(&lista, a);

                if(l2 != NULL) {
                    printf("ELEMENTO ENCONTRADO: %s - %d\n", l2->info.nome,l2->cont);
                    printf("Tudo certo :)\n");
                } else
                    printf("\nOcorreu um erro :(\n");

                break;

            case 8:
                liberarLista(&lista);
                break;

            case 9: // Mostrar Lista
                imprimirLista(&lista);
                break;

            default:
                printf("\nOpcao invalida\n");
                break;
        }
    } while(1);

    return 0;
}
