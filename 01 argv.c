#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int x;
    printf("argc: %d\n", argc);

    for(x = 0; x < argc; x++) {
        printf("argv[%d]: %s\n",x, argv[x]);

        if(!strcmp(argv[x], "-h"))
            puts("help");
    }

    return 0;
}
