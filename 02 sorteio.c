#include<stdio.h>
#include<stdlib.h>

int main() {
    int seed = 1;
    int countEquipes = 13;
    int countSorteios = 20;
    srand(seed);

    for(int i = 1; i <= countSorteios; i++) {
        printf("\nOrdem: %d - Equipe: %d", i, (rand() % countEquipes) + 1);
    }

    printf("\n");
    return 0;
}
