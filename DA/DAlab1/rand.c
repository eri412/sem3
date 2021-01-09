#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("bad arguments\n");
        return 1;
    }
    srand(time(0));
    FILE *fp = fopen(argv[2], "w");
    for (int i = 0; i < atoi(argv[1]); ++i) {
        fprintf(fp, "%d %c%c%c %c%c\t%d\n", rand()%10, rand()%26 + 'A', rand()%26 + 'A', rand()%26 + 'A', rand()%10 + '0', rand()%10 + '0', rand());
    }
    fclose(fp);

    return 0;
}