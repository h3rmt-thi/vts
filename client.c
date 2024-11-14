#include "math.h"

void main(int argc, char **argv) {
    const char *servername = argv[1];
    CLIENT *cl = clnt_create(servername, MATHPROG, MATHVERS, "tcp");
    printf("Client Connected\n");
    intpair numbers;
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <servername> <num1> <num2>\n", argv[0]);
        exit(1);
    }
    numbers.a = atoi(argv[2]);
    numbers.b = atoi(argv[3]);
    printf("%d + %d\n", numbers.a, numbers.b);
    const int *res = add_1(&numbers, cl);
    printf("%d\n", *res);
}
