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

void Suzuki4::step(qState& state)
{
    auto gate = m_gate.begin();

    update(state, gate, 0);
    update(state, gate + 3, 1);
    update(state, gate + 6, 0);
    update(state, gate + 9, 1);
    update(state, gate + 6, 0);
    update(state, gate + 3, 1);
    update(state, gate, 0);
}

void Suzuki4::update(qState& state, qState::iterator gate, size_t start)
{

}
