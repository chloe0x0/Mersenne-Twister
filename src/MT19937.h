#ifndef __MT_H_
#define __MT_H_

#define N_32 624
#define N_64 624

// 32 bit Mersenne Twister
typedef struct MT19937_32 {
    unsigned long state[N_32];
    unsigned int index;
} MT19937_32;

// Generate 32 bit Natural Numbers
unsigned long GenNat_32(MT19937_32* mt);
// Generate 32 bit floating point numbers in the range [0, 1]
float GenReal_32(MT19937_32* mt);
// Seed the Mersenne Twister 
void Seed_32(unsigned long seed, MT19937_32* mt);

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
