#ifndef __MT_32_H_
#define __MT_32_H_

#define N_32 624

// 32 bit Mersenne Twister
typedef struct MT19937{
    unsigned long state[N_32];
    unsigned int index;
} MT19937;

// Generate 32 bit Natural Numbers
unsigned long GenNat_32(MT19937* mt);
// Generate 32 bit floating point numbers in the range [0, 1]
float GenReal_32(MT19937* mt);
// Seed the Mersenne Twister 
void Seed_32(unsigned long seed, MT19937* mt);

#endif
