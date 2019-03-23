//
// Created by mitja on 23.3.2019.
//

#include "Suzuki4.h"

Suzuki4::Suzuki4(std::complex<double> z):
Propagator(z)
{
    // S4 exponent coefficients
    std::complex<double> z3 = -1.7024143839193153 * z;
    std::complex<double> z1 = 1.3512071919596578 * z;
    std::complex<double> z0 = .5 * z1;
    std::complex<double> z2 = .5 * (z3 + z1);

    // qbit gate matrix elements (3 of them are unique)
    m_gate.push_back(std::exp(z0));
    m_gate.push_back(std::exp(-z0) * std::cosh(2.0 * z0));
    m_gate.push_back(std::exp(-z0) * std::sinh(2.0 * z0));

    m_gate.push_back(std::exp(z1));
    m_gate.push_back(std::exp(-z1) * std::cosh(2.0 * z1));
    m_gate.push_back(std::exp(-z1) * std::sinh(2.0 * z1));

    m_gate.push_back(std::exp(z2));
    m_gate.push_back(std::exp(-z2) * std::cosh(2.0 * z2));
    m_gate.push_back(std::exp(-z2) * std::sinh(2.0 * z2));

    m_gate.push_back(std::exp(z3));
    m_gate.push_back(std::exp(-z3) * std::cosh(2.0 * z3));
    m_gate.push_back(std::exp(-z3) * std::sinh(2.0 * z3));
}

void Suzuki4::step(qState& state, size_t N)
{
    auto gate = m_gate.begin();

    update(state, gate, 0, N);
    update(state, gate + 3, 1, N);
    update(state, gate + 6, 0, N);
    update(state, gate + 9, 1, N);
    update(state, gate + 6, 0, N);
    update(state, gate + 3, 1, N);
    update(state, gate, 0, N);
}

void Suzuki4::update(qState& state, qState::iterator gate, size_t start, size_t N)
{
    for (size_t j = start; j < N; j += 2)
    {
        size_t j1 = 0;
        if (j != N-1) j1 = j + 1;

        for (size_t n = 0; n < state.size(); ++n)
        {
            if ((n >> j)&1 == (n >> j1)&1)
            {
                // 0000 or 1111
                state[n] *= *gate;
            }
            else
            {
                // 0110 or 1001 or 0101 or 1010
                state[n] *= *(gate + 1);
                size_t m = n ^ (1 << j);
                m ^= 1 << j1;
                state[n] += *(gate + 2) * state[m];
            }
        }
    }
}
