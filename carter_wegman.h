#ifndef CARTER_WEGMAN_H
#define CARTER_WEGMAN_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    unsigned int a;  //
    unsigned int b;  //
    unsigned int p;  // Prime number used by hash.
    unsigned int n;  // The universe size.
    unsigned int k;  // The size of the range.
} carter_wegman_hash;

void carter_wegman_init(carter_wegman_hash * const hash) {
  memset(hash, 0, sizeof(carter_wegman_hash));
}

void carter_wegman_set(carter_wegman_hash * const hash,
                        const unsigned int n_,
                        const unsigned int k_) {


  if (n_ != hash->n) {
    unsigned int is_prime = 0;
    if (n_ <= 1) {
      hash->p = 2;
      is_prime = 1;
    }

    unsigned int candidate = n_;
    unsigned int i;
    while (!is_prime) {
      i = 2;
      is_prime = 1;
      ++candidate;
      while (i * i <= candidate) {
        if (candidate % i == 0) {
          is_prime = 0;
        }
        ++i;
      }
      hash->p = candidate;
    }
  }

  hash->n = n_;
  hash->k = k_;
  hash->a = (rand() % (hash->p - 1)) + 1;
  hash->b = (rand() % hash->p);
}

unsigned int carter_wegman_h(const carter_wegman_hash * const hash,
                             const unsigned int i) {
  return ((hash->a * i + hash->b) % hash->p) % hash->k;
}

#endif
