#include "math.h"

int *add_1_svc(intpair *intpair, struct svc_req *req) {
    int *p = malloc(sizeof(int));
    *p = intpair->a + intpair->b;
    return p;
}

int *multiply_1_svc(intpair *intpair, struct svc_req *req) {
    int *p = malloc(sizeof(int));
    *p = intpair->a * intpair->b;
    return p;
}

int *cube_1_svc(int *nr, struct svc_req *req) {
    int *p = malloc(sizeof(int));
    *p = *nr * *nr * *nr;
    return p;
}
