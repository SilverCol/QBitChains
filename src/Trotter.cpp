//
// Created by mitja on 24.3.2019.
//

#include "Trotter.h"

Trotter::Trotter(std::complex<double> z):
Propagator(z)
{
    // qbit gate matrix elements (1 matrix, 3 unique elements)
    m_gate.push_back(std::exp(z));
    m_gate.push_back(std::exp(-z) * std::cosh(2.0 * z));
    m_gate.push_back(std::exp(-z) * std::sinh(2.0 * z));
}

void Trotter::step(QState& state, size_t N)
{
    auto gate = m_gate.begin();

    Propagator::update(state, gate, 0, N);
    Propagator::update(state, gate, 1, N);
}
