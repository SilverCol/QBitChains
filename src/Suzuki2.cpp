//
// Created by mitja on 24.3.2019.
//

#include "Suzuki2.h"

Suzuki2::Suzuki2(std::complex<double> z):
Propagator(z)
{
    // S2 exponent coefficients
    std::complex<double> z0 = .5 * z;
    std::complex<double> z1 = z;

    // qbit gate matrix elements (2 matrices, each with 3 unique elements)
    m_gate.push_back(std::exp(z0));
    m_gate.push_back(std::exp(-z0) * std::cosh(2.0 * z0));
    m_gate.push_back(std::exp(-z0) * std::sinh(2.0 * z0));

    m_gate.push_back(std::exp(z1));
    m_gate.push_back(std::exp(-z1) * std::cosh(2.0 * z1));
    m_gate.push_back(std::exp(-z1) * std::sinh(2.0 * z1));
}

void Suzuki2::step(QState& state, size_t N)
{
    auto gate = m_gate.begin();

    Propagator::update(state, gate, 0, N);
    Propagator::update(state, gate + 3, 1, N);
    Propagator::update(state, gate, 0, N);
}
