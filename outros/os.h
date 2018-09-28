// --- Verifica o Sistema Operacional
#if defined(_WIN32) || defined(_WIN64)
    const int os = 2; //Windows
#else
    #ifdef __linux
        const int os = 2; // Linux
    #else
        const int os = 0; //Unknown
    #endif
#endif

//--- Limpa buffer do teclado para Windows e GNU/Linux
void clean_stdin(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
