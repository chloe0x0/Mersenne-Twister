#include <stdio.h>
#include "MT19937-64.h"

#define M        156
#define F        0x5851f42d4c957f2dULL
#define W        64

#define A        0xB5026F5AA96619E9ULL // constant coefficients of the twist matrix

#define U_MASK   0xFFFFFFFF80000000ULL // upper w-r bits 
#define L_MASK   0x7FFFFFFFULL         // lower r bits

/* Tempering */
#define T_MASK_B 0x71D67FFFEDA60000ULL
#define T_MASK_C 0xFFF7EEE000000000ULL
#define T_MASK_D 0x5555555555555555ULL

// If the MT struct is not seeded, this sed will be used (taken from the original paper's C implementation)
#define CONSTANT_SEED 4357ULL

void Seed_64(unsigned long long seed, MT19937_64* mt){
    mt->state[0] = seed;
    for (mt->index = 1; mt->index < N_64; mt->index++){
        mt->state[mt->index] = F * (mt->state[mt->index - 1] ^ (mt->state[mt->index - 1] >> 62)) + mt->index;
    }
}

unsigned long long GenNat_64(MT19937_64* mt){
    unsigned long long y;
    const unsigned long long mag[2] = {0x0, A};
    
    if (mt->index >= N_64){
        // Check for seed
        // If not seeded, seed with some constant (The original paper uses the seed: 4357)
        if (mt->index == N_64 + 1){ Seed_64(CONSTANT_SEED, mt); }
        
        int kk = 0;
        
        for (; kk < N_64 - M; kk++){
            y = (mt->state[kk] & U_MASK) | (mt->state[kk + 1] & L_MASK);
            mt->state[kk] = mt->state[kk + M] ^ (y >> 1) ^ mag[y & 0x1];
        }

        for (; kk < N_64 - 1; kk++){
            y = (mt->state[kk] & U_MASK) | (mt->state[kk + 1] & L_MASK);
            mt->state[kk] = mt->state[kk + (M - N_64)] ^ (y >> 1) ^ mag[y & 0x1];
        }

        y = (mt->state[N_64 - 1] & U_MASK) | (mt->state[0] & L_MASK);
        mt->state[N_64 - 1] = mt->state[M - 1] ^ (y >> 1) ^ mag[y & 0x1ULL];

        mt->index = 0;
    }

    y = mt->state[mt->index++];
    y ^= (y >> 29 ) & T_MASK_D;
    y ^= (y << 17 ) & T_MASK_B;
    y ^= (y << 37 ) & T_MASK_C;
    y ^= (y >> 43 );

    return y;
}

double GenReal_64(MT19937_64* mt){
    return (double)(GenNat_64(mt) >> 11) *(1.0/9007199254740991.0) ;
}
int main(void){}
