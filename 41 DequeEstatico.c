#include<stdio.h>
#include<string.h>

#include "0 os.h" // To use clean_output() and clean_stdin()

#define MAX_TAM 5

typedef struct sAluno {
    char nome[100];
    int idade;
} Aluno;

typedef struct sDeque {
    Aluno info[MAX_TAM];
    int inicio, fim;
} Deque;

void inicializar(Deque* deque) {
    deque->fim = 0;
    deque->inicio = 0;
}

int dequeVazio(Deque *deque) {
    if(deque->fim == deque->inicio)
        return 1;

    return 0;
}

int dequeCheio(Deque* deque) {
    int proxi = (deque->fim + 1) % MAX_TAM;

    if(proxi == deque->inicio)
        return 1;

    return 0;
}

Aluno criarAluno(char nome[], int idade) {
    Aluno e;
    strcpy(e.nome, nome);
    e.idade = idade;
    return e;
}

int inserirNoInicio(Deque* deque, Aluno elemento) {
    if(dequeCheio(deque)) {
        printf("\nErro: Deque cheio\n");
        return 0;
    }

    if(deque->inicio == 0)
        deque->inicio = MAX_TAM - 1;
    else
        deque->inicio--;

    deque->info[deque->inicio] = elemento;
    return 1;
}

int inserirNoFim(Deque *deque, Aluno elemento) {
    if(dequeCheio(deque))
        return 0;

    deque->info[deque->fim] = elemento;
    deque->fim = (deque->fim + 1) % MAX_TAM;
    return 1;
}

Aluno removerNoInicio(Deque *deque) {
    Aluno vazio = criarAluno("",-1);

    if(dequeVazio(deque))
        return vazio;

    vazio = deque->info[deque->inicio];
    deque->inicio = (deque->inicio + 1) % MAX_TAM;
    return vazio;
}

Aluno removerNoFim(Deque *deque) {
    Aluno vazio = criarAluno("",-1);

    if(dequeVazio(deque))
        return vazio;

    vazio = deque->info[deque->fim];
    deque->fim = (MAX_TAM + (deque->fim - 1)) % MAX_TAM;
    return vazio;
}

// IMPRIMIR
void imprimirTodos(Deque *deque) {
    Deque deque2;
    inicializar(&deque2);

    if(dequeVazio(deque)) {
        printf("\nO deque esta vazio\n");
        return;
    }

    Aluno a;

    while(!dequeVazio(deque)) {
        a = removerNoInicio(deque);
        printf("Nome: %s - %d\n", a.nome, a.idade);
        inserirNoFim(&deque2, a);
    }

    while(!dequeVazio(&deque2))
        inserirNoFim(deque, removerNoInicio(&deque2));
}

void Menu() {
    printf("\n::INSERIR\n");
    printf("  [1] - Inserir No Inicio\n");
    printf("  [2] - Inserir No Fim\n");
    printf("\n::REMOVER\n");
    printf("  [3] - Remover No Inicio\n");
    printf("  [4] - Remover No Fim\n");
    printf("\n::MOSTRAR\n");
    printf("  [5] - Imprimir\n\n");
    printf("::SAIR\n");
    printf("  [0] - Sair\n\n");
}

int main() {
    Aluno e;
    Deque deque;
    inicializar(&deque);
    int option;

    do {
        Menu();
        printf("Digite uma opcao: ");
        scanf("%d", &option);
        clean_output();
        clean_stdin();

        switch(option) {
            case 0:
                return 0;

            case 1:
                printf("Digite o nome: ");
                scanf("%s", e.nome);
                printf("Digite o idade: ");
                scanf("%d", &e.idade);

                if(inserirNoInicio(&deque, e))
                    printf("\nAluno inserido :)\n");
                else
                    printf("\nOcorreu um erro :(\n");

                break;

            case 2:
                printf("Digite o nome: ");
                scanf("%s", e.nome);
                printf("Digite o idade: ");
                scanf("%d", &e.idade);

                if(inserirNoFim(&deque, e))
                    printf("\nAluno inserido :)\n");
                else
                    printf("\nOcorreu um erro :(\n");

                break;

            case 3:
                e = removerNoInicio(&deque);

                if(e.idade != -1)
                    printf("\nAluno retirado: %s\n",e.nome);
                else
                    printf("\nDeque Vazio :(\n");

                imprimirTodos(&deque);
                break;

            case 4:
                e = removerNoFim(&deque);

                if(e.idade != -1)
                    printf("\nAluno retirado: %s\n",e.nome);
                else
                    printf("\nDeque Vazio :(\n");

                imprimirTodos(&deque);
                break;

            case 5:
                imprimirTodos(&deque);
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

        printf("\n");
    } while(1);

    return 0;
}
