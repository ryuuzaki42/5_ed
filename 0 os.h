#include<stdlib.h>

// Verifica o Sistema Operacional
#if defined(_WIN32) || defined(_WIN64)
    const int os = 1; // Windows
#else
    #ifdef __linux
        const int os = 2; // Linux
    #else
        const int os = 0; //U nknown
    #endif
#endif

// Limpa buffer do teclado para Windows e GNU/Linux
void clean_stdin() {
    int c;

    while((c = getchar()) != '\n' && c != EOF);
}

// Limpa o terminal para Windows e GNU/Linux
void clean_output() {
    if(os == 1)
        system("cls");
    else if(os == 2)
        system("clear");
}
