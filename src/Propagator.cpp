//
// Created by mitja on 23.3.2019.
//

#include "Propagator.h"

Propagator::Propagator(const std::complex<double> z):
m_z(z)
{}

void Propagator::propagate(qState& state, size_t N, size_t steps)
{
    for (size_t i = 0; i < steps; ++i)
    {
        step(state, N);
    }
}

void Propagator::update(qState& state, std::vector<std::complex<double> >::iterator gate, size_t start, size_t N)
{
    for (size_t j = start; j < N; j += 2)
    {
        size_t j1 = 0;
        if (j != N-1) j1 = j + 1;

        qState temp(state.size(), 0);
        for (size_t n = 0; n < state.size(); ++n)
        {
            if (((n >> j)&1)^((n >> j1)&1))
            {
                // 0110 or 1001 or 0101 or 1010
                temp[n] = *(gate + 1) * state[n];
                size_t m = n ^ (1 << j);
                m ^= 1 << j1;
                temp[n] += *(gate + 2) * state[m];
            }
            else
            {
                // 0000 or 1111
                temp[n] = *gate * state[n];
            }
        }
        state.swap(temp);
    }
}
