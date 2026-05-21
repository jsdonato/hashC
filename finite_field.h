#ifndef FINITE_FIELD_H
#define FINITE_FIELD_H

typedef struct {
    long long unsigned int a;  //
    long long unsigned int b;  //
    long long unsigned int p;  // Irreducible polynomial used by the hash.
} finite_field_hash;

#endif
