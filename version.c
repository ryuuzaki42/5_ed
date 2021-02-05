#include<stdio.h>

/*Detecting the compiler versionr
    gcc version.c
    gcc -std=c90 version.c
    gcc -std=c99 version.c
    gcc -std=c11 version.c
    gcc -std=c17 version.c
*/

int main(){
    #ifndef __STDC_VERSION__
        printf("Version: c89. __STDC_VERSION__ is not defined.\n");
    #else
        #if (__STDC_VERSION__ == 199409L)
            printf("Version: C94\n");
        #endif

        #if (__STDC_VERSION__ == 199901L)
            printf("Version: C99\n");
        #endif

        #if (__STDC_VERSION__ == 201112L)
            printf("Version: C11\n");
        #endif

        #if (__STDC_VERSION__ == 201710L)
            printf("Version: C17\n");
        #endif
    #endif

    return 0;
}
