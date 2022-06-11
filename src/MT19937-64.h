#ifndef __MT_64_H
#define __MT_64_H

// 64 bit Mersenne Twister
typedef struct MT19937_64 {
    unsigned long long state[N_64];
    unsigned int index;
} MT19937_64;

// Generate 64 bit Natrual Numbers
unsigned long long GenNat_64(MT19937_64* mt);
// seed the Mersenne Twister
void Seed_64(unsigned long long seed, MT19937_64* mt);

#endif
