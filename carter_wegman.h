#ifndef CARTER_WEGMAN_H
#define CARTER_WEGMAN_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    long long unsigned int a;  //
    long long unsigned int b;  //
    long long unsigned int p;  // Prime number used by hash.
    long long unsigned int n;  // The universe size.
    long long unsigned int k;  // The size of the range.
} carter_wegman_hash;

void carter_wegman_init(carter_wegman_hash * const hash) {
  memset(hash, 0, sizeof(carter_wegman_hash));
}

void carter_wegman_set(carter_wegman_hash * const hash,
                        const long long unsigned int n_,
                        const long long unsigned int k_) {


  if (n_ != hash->n) {
    long long unsigned int is_prime = 0;
    if (n_ <= 1) {
      hash->p = 2;
      is_prime = 1;
    }

    long long unsigned int candidate = n_;
    long long unsigned int i;
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

long long unsigned int carter_wegman_h(const carter_wegman_hash * const hash,
                                       const long long unsigned int i) {
  return ((hash->a * i + hash->b) % hash->p) % hash->k;
}

#endif
