//
// Created by mitja on 23.3.2019.
//

#include "Propagator.h"

Propagator::Propagator(const std::complex<double> z):
m_z(z)
{}

void Propagator::propagate(qState& state, size_t steps)
{
    for (size_t i = 0; i < steps; ++i)
    {
        step(state);
    }
}
