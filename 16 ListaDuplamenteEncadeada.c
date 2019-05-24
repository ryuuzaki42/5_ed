#include<stdio.h>

#include "0 os.h" // To use clean_output() and clean_stdin()

typedef struct sAluno {
    char nome[100];
    int idade;
} Aluno;

typedef struct sCelula {
    Aluno info;
    struct sCelula *ant;
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

Lista* criarCelula() {
    return (Lista*) malloc(sizeof(Lista));
}

// INSERIR
int inserirNoInicio(Lista** lista, Aluno inserido) {
    Lista* nova = criarCelula();
    nova->info = inserido;
    nova->ant = NULL;
    nova->next = NULL;

    if(listaVazia((*lista))) {
        (*lista) = nova;
        return 1;
    }

    (*lista)->ant = nova;
    nova->next = (*lista);
    (*lista) = nova;
    return  1;
}

int inserirNoFim(Lista** lista, Aluno novo) {
    Lista* nova = criarCelula();
    nova->info = novo;
    nova->ant = NULL;
    nova->next = NULL;

    if(listaVazia((*lista))) {
        (*lista) = nova;
        return 1;
    }

    Lista* aux = (*lista);

    while(aux->next != NULL)
        aux = aux->next;

    nova->ant = aux;
    aux->next = nova;
    return 1;
}

// REMOVER
Aluno removerNoInicio(Lista** lista) {
    Aluno removido;
    if(listaVazia((*lista)))
        return removido;

    Lista* aux = (*lista);
    (*lista) = (*lista)->next;

    if((*lista) != NULL)
        (*lista)->ant = NULL;

    removido = aux->info;
    free(aux);
    return removido;
}

Aluno removerNoFim(Lista** lista) {
    Aluno removido;
    if(listaVazia((*lista)))
        return removido;

    Lista* aux = (*lista);

    while(aux->next != NULL)
        aux = aux->next;

    aux->ant->next = NULL;
    removido = aux->info;
    free(aux);
    return removido;
}

// EXTRA
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

    if(listaVazia(*lista)) {
        printf("Lista Vazia!\n");
        return;
    }

    Lista *aux = (*lista);
    printf("nome - idade\n");

    while(aux != NULL) {
        printf("%s - %d\n",aux->info.nome,aux->info.idade);
        aux = aux->next;
    }

    printf("\n\n");
}

void Menu() {
    printf("\n::INSERIR\n");
    printf("  [1] - Inserir no Inicio\n");
    printf("  [2] - Inserir no Final\n");
    printf("::REMOVER\n");
    printf("  [3] - Remover no Inicio\n");
    printf("  [4] - Remover no Final\n");
    printf("::MOSTRAR\n");
    printf("  [5] - Liberar Lista\n");
    printf("  [6] - Mostrar Lista\n\n");
    printf("::SAIR\n");
    printf("  [0] - Sair\n");
}

int main() {
    Lista* lista;
    Aluno a;
    int option,posicaoK;
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
                    printf("Tudo certo :)\n");
                else
                    printf("\nOcorreu um erro :(\n");

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

            case 3: // Remover no inicio
                a = removerNoInicio(&lista);

                if(a.nome) {
                    printf("ELEMENTO REMOVIDO: %s\n", a.nome);
                    printf("Tudo certo :)\n");
                } else
                    printf("\nLista Vazia :(\n");

                break;

            case 4: // Remover no final
                a = removerNoFim(&lista);

                if(a.nome) {
                    printf("ELEMENTO REMOVIDO: %s\n", a.nome);
                    printf("Tudo certo :)\n");
                } else
                    printf("\nLista Vazia :(\n");

                break;

            case 5:
                liberarLista(&lista);
                break;

            case 6: // Mostrar Lista
                imprimirLista(&lista);
                break;

            default:
                printf("\nOpcao invalida\n");
                break;
        }
    } while(1);

    return 0;
}
