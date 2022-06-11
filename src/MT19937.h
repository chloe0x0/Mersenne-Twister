#ifndef __MT_32_H_
#define __MT_32_H_

#define N_32 624

// 32 bit Mersenne Twister
typedef struct MT19937{
    unsigned long state[N_32];
    unsigned int index;
} MT19937;

// Generate 32 bit Natural Numbers
unsigned long MT_GenNat(MT19937*);
// Generate 32 bit floating point numbers in the range [0, 1]
float MT_GenReal(MT19937*);
// Seed the Mersenne Twister 
void SeedMT(unsigned long, MT19937*);

#endif
