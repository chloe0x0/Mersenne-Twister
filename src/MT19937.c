#include <stdio.h>
#include "MT19937.h"

#define M        397
#define F        69069

#define A        0x9908b0df // constant coefficients of the twist matrix

#define U_MASK   0x80000000 // upper w-r bits 
#define L_MASK   0x7fffffff // lower r bits

/* Tempering */
#define T_MASK_B 0x9d2c5680
#define T_MASK_C 0xefc60000

// If the MT struct is not seeded, this seed will be used (taken from the original paper's C implementation)
#define CONSTANT_SEED 4357

void SeedMT(unsigned long seed, MT19937* mt){
    mt->state[0] = seed & 0xffffffff;
    for (mt->index = 1; mt->index < N_32; mt->index++){
        mt->state[mt->index] = (F * mt->state[mt->index - 1]) & 0xffffffff;
    }
}

unsigned long MT_GenNat(MT19937* mt){
    unsigned long y;
    const unsigned long mag[2] = {0x0, A};
    
    if (mt->index >= N_32){
        // Check for seed
        // If not seeded, seed with some constant (The original paper uses the seed: 4357)
        if (mt->index == N_32 + 1){ SeedMT(CONSTANT_SEED, mt); }
        
        int kk = 0;
        
        for (; kk < N_32 - M; kk++){
            y = (mt->state[kk] & U_MASK) | (mt->state[kk + 1] & L_MASK);
            mt->state[kk] = mt->state[kk + M] ^ (y >> 1) ^ mag[y & 0x1];
        }

        for (; kk < N_32 - 1; kk++){
            y = (mt->state[kk] & U_MASK) | (mt->state[kk + 1] & L_MASK);
            mt->state[kk] = mt->state[kk + (M - N_32)] ^ (y >> 1) ^ mag[y & 0x1];
        }

        y = (mt->state[N_32 - 1] & U_MASK) | (mt->state[0] & L_MASK);
        mt->state[N_32 - 1] = mt->state[M - 1] ^ (y >> 1) ^ mag[y & 0x1];

        mt->index = 0;
    }

    y = mt->state[mt->index++];
    y ^= (y >> 11 );
    y ^= (y << 7  ) & T_MASK_B;
    y ^= (y << 15 ) & T_MASK_C;
    y ^= (y >> 18 );

    return y;
}

double MT_GenReal(MT19937* mt){
    return (double)(MT_GenNat(mt)) / 0xffffffffUL;
}

