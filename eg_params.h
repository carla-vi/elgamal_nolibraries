#ifndef RSA_PARAMS_H
#define RSA_PARAMS_H

#include <stdint.h>

// Declare the arrays as extern to allow for their use across different source files
extern uint64_t p[20];
extern uint64_t g[20];
extern uint64_t x[20];
extern uint64_t y[20];
extern uint64_t m[20];
extern uint64_t k[20];
extern uint64_t a[20];
extern uint64_t b[20];
extern uint64_t aux[20];
extern uint64_t s[20];
extern uint64_t res[20];


#endif // RSA_PARAMS_H
